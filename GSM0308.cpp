/***************************************************************************
 *                                                                         *
 *  This program is free software; you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation; either version 2 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with this program; if not, write to the Free Software            *
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111 USA    *
 *                                                                         *
 ***************************************************************************
 *                                                                         *
 *               (c) Copyright, 1997-2012, ANSR                            *
 *                                                                         *
 ***************************************************************************
 *                                                                         *
 * Filename:     GPS0308.cpp                                               *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

/// Reserve memory for singleton object.
static GSM0308 gsm0308SingletonObject;

/**
 *  Constructor.
 */
GSM0308::GSM0308()
{
    this->responseIndex = 0;
    this->responseReadyFlag = false;
    this->parseState = InReset;
    this->resetFlag = false;
    this->smsReady = false;
    this->lastResetTime = 0;

    ClearData();
}

/**
 *   Pointer to the Radio MODEM object.
 */
GSM0308 *GSM0308::GetInstance()
{
    return &gsm0308SingletonObject;
}

/**
 * Flag that indicates the Modem has registered with the service provider
 * and is ready to accept SMS data.
 *
 * @return true if registered; otherwise false
 */
bool_t GSM0308::IsRegistered()
{
    return (this->parseState == NetworkRegisteredReady);
}

/**
 * One shot flag that is set when the Modem is ready to process SMS requests.
 */
bool_t GSM0308::IsSMSReady()
{
    if (this->smsReady)
    {
        this->smsReady = false;
        return true;
    } // END if

    return false;
}

/**
 * One-shot flag that indicates the Modem has been reset.
 *
 * @return true if reset occurred; otherwise false
 */
bool_t GSM0308::IsModemReset()
{
    if (this->resetFlag)
    {
        this->resetFlag = false;
        return true;
    }

    return false;
}

/**
 * Flag that indicates MODEM response has been received and is ready.
 *
 * @return true when new response is ready; otherwise false
 */
bool_t GSM0308::IsResponseReady()
{
    return this->responseReadyFlag;
}

/**
 * Get the last response string from the MODEM and clear the response ready flag that is
 * queried with the IsResponseReady method.
 */
const char *GSM0308::Response()
{
    // Reset the buffer pointer.
    this->responseIndex = 0;

    // Clear the flag to indicate we read the message.
    this->responseReadyFlag = false;

    return this->response;
}

/**
 *  Read the serial FIFO and process any pending GSM responses.
 */
void GSM0308::Update()
{
    uint32_t value, count, parm1, parm2, parm3, parm4;
    bool_t cregFlag = false;
    bool_t bootText = false;
    bool_t okPrompt = false;

    // If the response flag is set, it indicates the user application has not processed a pending response.
    if (this->responseReadyFlag)
        return;

    // Read and save each character from the Modem waiting for the line feed to signify the end of message.
    while (HasData() && !this->responseReadyFlag)
    {
        // Get the character value.
        value = ReadData();

        switch (value)
        {
            case 10:
                this->response[this->responseIndex] = 0;
                this->responseReadyFlag = true;
                break;;

            case 13:
                break;

            default:
                this->response[this->responseIndex] = value;

                if (++this->responseIndex == MaxATLength - 1)
                {
                    this->response[this->responseIndex] = 0;
                    this->responseReadyFlag = true;
                } // END if
                break;
        } // END switch
    } // END while

    if (this->responseReadyFlag)
        if (strlen(this->response) == 0)
            this->responseReadyFlag = false;

    // Parse complete strings.
    if (this->responseReadyFlag)
    {
        if (strstr(this->response, "+CREG: "))
        {
            count = sscanf(this->response + 7, "%lx,%lx,%lx,%lx", &parm1, &parm2, &parm3, &parm4);

            // Parse the following common Modem response strings.
            //
            // +CREG: 1, 8790, B00F
            // +CREG: 2, 0
            // +CREG: 2
            // +CREG: 3
            switch (count)
            {
                case 1:
                    if (parm1 == 3)
                        SendString("AT$RESET\015");

                    break;

                case 3:
                    if (parm1 == 1 || parm1 == 5)
                    {
                        cregFlag = true;
                        this->locationAreaCode = parm2;
                        this->cellID = parm3;
                    }
                    break;

                case 4:
                    if (parm1 == 2)
                    {
                        cregFlag = true;
                        this->locationAreaCode = parm3;
                        this->cellID = parm4;
                    }
                    break;
            } // END switch

            if (cregFlag)
                SendString("AT+CSQ\015");

        } // END if

        if (strstr(this->response, "+CSQ:"))
        {
            if (sscanf (this->response + 5, "%ld,%ld", &this->rssi, &this->rxQual) != 2)
            {
                this->rssi = 99;
                this->rxQual = 99;
            }
        } // END if

        if (strstr(this->response, "Command Interpreter"))
        {
            this->parseState =  WaitPowerOnSelfTest;
            bootText = true;
            this->resetFlag = true;
        } // END if

        if (strstr(this->response, "OK"))
            okPrompt = true;
    } // END if responseReadyFlag

    // Process the message parsing state machine.
    switch (this->parseState)
    {
        case InReset:
            break;

        case HoldResetLow:
            if (SystemControl::GetTick() > nextResponseTime)
            {
                // Clear the internal data set.
                ClearData();

                // Release the Reset line so the Modem runs.
                Reset(false);

                // Record the time of the last reset.
                this->lastResetTime = SystemControl::GetTick();

                this->parseState = WaitPowerOnSelfTest;
            } // END if
            break;

        case WaitPowerOnSelfTest:
            if (this->responseReadyFlag)
                if (bootText)
                {
                    SendString ("AT\015");
                    this->parseState = WaitResetOK;
                } // END if
            break;

        case WaitResetOK:
            if (this->responseReadyFlag)
                if (okPrompt)
                {
                    SendString("ATE0Q0V1\015");  // Use to see outgoing commands   ATE1Q0V1
                    this->parseState = WaitSetupOK;
                }
            break;

        case WaitSetupOK:
            if (this->responseReadyFlag)
                if (okPrompt)
                {
                    std::strcpy (this->version, "");
                    SendString("AT+GMM;+GMR\015");
                    this->parseState = WaitVersionOK;
                }
            break;

        case WaitVersionOK:
            if (this->responseReadyFlag)
            {
                if (okPrompt)
                {
                    SendString("AT+CREG=2\015");
                    this->parseState = WaitNetworkRegistered;
                    nextResponseTime = SystemControl::GetTick() + 100;
                } else {
                    if (std::strlen(this->response) > 0)
                    {
                        std::strncat(this->version, this->response, VersionSize - 3);
                        this->version[VersionSize - 3] = 0;

                        std::strcat(this->version, "\r\n");
                    } // END if
                } // END if-else
            } // END if responseReadyFlag
            break;

        case WaitNetworkRegistered:
            if (SystemControl::GetTick() > nextResponseTime)
            {
                nextResponseTime = 0xffffffff;
                SendString("AT+CREG?\015");
            } // END if

            if (this->responseReadyFlag)
                if (cregFlag)
                {
                    this->parseState = NetworkRegistered;
                    nextResponseTime = SystemControl::GetTick() + 10000;
                } // END if
            break;

        case NetworkRegistered:
            if (SystemControl::GetTick() > nextResponseTime)
            {
                this->parseState = NetworkRegisteredReady;
                this->smsReady = true;
            } // END if
            break;

        case NetworkRegisteredReady:
            break;
    } // END switch
}

/**
 * Send an SMS message using the specified destination address that is typically
 * that phone number.
 *
 * @param destinationAddress destination address that is typically the phone number
 * @param message NULL terminate ASCII text message
 */
void GSM0308::SendSMS(const char *destinationAddress, const char *message)
{
    // Only allow an SMS if we are registered on the network and the Modem is ready to accept SMS commands.
    if (this->parseState != NetworkRegisteredReady)
        return;

    SendString ("AT+CMGS=\"%s\"\015", destinationAddress);

    SystemControl::Sleep(100);

    SendString(message);
    SendString("\015\032\015");
}

/**
 * Reset the MODEM and register with the network service provider.
 */
void GSM0308::Register()
{
    Reset(true);
    this->parseState = HoldResetLow;
    this->nextResponseTime = SystemControl::GetTick() + 2000;
}

/**
 * RSSI (Receive Signal Strength Indicator) in dBm.  The strength ranges
 * from -113 to -51dBm.  A value of -120 indicates a signal was not detected
 * or is unknown.
 *
 * @return signal strength in dBm
 */
int32_t GSM0308::RSSI()
{
    if (this->rssi > 31)
        return -120;

    return -113 + (static_cast<int32_t> (this->rssi) << 1);
}

/**
 * Receive Quality indicator (Bit Error Rate) in the range 0 to 7 with 0 the best
 * signal quality and 7 the worst.
 *
 * @return 8-bit receive quality
 */
uint32_t GSM0308::RxQual()
{
    return this->rxQual;
}

/**
 * Get the GSM LAC (Location Area Code).  This is <i>not</i> related to the
 * telephone area code.
 *
 * @return 16-bit GSM location area code
 */
uint32_t GSM0308::LocationAreaCode()
{
    return this->locationAreaCode;
}

/**
 * Get the GSM Cell ID number.
 *
 * @return 16-bit GSM cell ID
 */
uint32_t GSM0308::CellID()
{
    return this->cellID;
}

/**
 * Send the NULL terminated string to the MODEM.
 *
 * @param text pointer to NULL terminated string to send
 */
void GSM0308::SendString(const char *text, ...)
{
    va_list argList;
    const char *bufferPnt;
    char buffer[MaxATLength];

    va_start (argList, text);
    vsnprintf (buffer, sizeof(buffer), text, argList);
    va_end (argList);

    bufferPnt = buffer;

    while (*bufferPnt != 0)
        WriteData (*bufferPnt++);
}

/**
 * Modem firmware version information.
 *
 * @return pointer to NULL terminated string
 */
const char *GSM0308::Version()
{
    return this->version;
}

/**
 * Clear the Modem receiver values after a reset.
 */
void GSM0308::ClearData()
{
    this->locationAreaCode = 0x0000;
    this->cellID = 0x0000;
    this->rssi = 99;
    this->rxQual = 99;
    this->version[0] = 0;
}

/**
 * Get the last reset time of the Modem.
 */
uint32_t GSM0308::LastResetTime()
{
    return this->lastResetTime;
}
