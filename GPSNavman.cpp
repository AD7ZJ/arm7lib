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
 * Filename:     GPSNavman.cpp                                             *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

/// Reserve memory for singleton object.
static GPSNavman navmanSingletonObject;

/**
 *  Constructor.
 */
GPSNavman::GPSNavman()
{
    this->gpsParseState = GPSStart1;
    this->dataReadyFlag = false;
    this->okToSendFlag = false;
    this->version[0] = 0x00;
}

/**
 *   Pointer to the Navman GPS engine object.
 */
GPSNavman *GPSNavman::GetInstance()
{
    return &navmanSingletonObject;
}

/**
 *   Get a pointer to the GPSData object that contains the latest fix information.
 *
 *   @return pointer to GPSData object
 */
GPSData *GPSNavman::Data()
{
    return &this->data;
}

/**
 * Flag that indicates new GPS data has been receive and is ready.
 *
 * @return true when new data is ready; otherwise false
 */
bool_t GPSNavman::IsDataReady()
{
    if (this->dataReadyFlag)
    {
        this->dataReadyFlag = false;
        return true;
    } //END if

    return false;
}

/**
 * Flag that indicates the OK To Send has been received.
 *
 * @return true when OK To Send is received
 */
bool_t GPSNavman::IsOkToSend()
{
    if (this->okToSendFlag)
    {
        this->okToSendFlag = false;
        return true;
    } //END if

    return false;
}

/**
 *  Using the Message ID, parse the SiRF binary message.
 */
void GPSNavman::ParseMessage()
{
    uint32_t i, j, index, cNo;

    switch (payload[0])
    {
        // Measured Tracker Data Out - Message ID 4.
        case 4:
            // Offset to the 1st SVID field.
            index = 8;

            // Process 12 receive channels of data.
            for (i = 0; i < 12; ++i)
            {
                // Sum the C/No value.
                cNo = 0;

                for (j = 0; j < 10; ++j)
                    cNo += this->payload[index + j + 5];

                this->data.RxChannel (i, static_cast<uint32_t> (this->payload[index]), static_cast<uint32_t> (this->payload[index + 4]), cNo);

                index += 15;
            } // END for

            // Set a flag to indicate a new data set is complete.
            this->dataReadyFlag = true;
            break;

        // Software Version String (Response to Poll) - Message ID 6
        case 6:
            // Set the write index to the end of the string.
            j = 0;

            while (this->version[j] != 0)
                ++j;

            // Append the payload bytes to the version string.
            for (i = 1; this->payload[i] != 0 && i < this->payloadLength && j < (VersionSize - 1); ++i, ++j)
                this->version[j] = payload[i];

            // NULL terminate after the copy.
            this->version[j] = 0;

            // Put a <LF><CR> between each information string.  The order is critical so Windoze will recognize the string in .NET.
            strcat (this->version, "\r\n");
            break;

        // OkToSend - Message ID 18.
        case 18:
            this->okToSendFlag = true;

            // Query the software version after we've started.
            PollSoftwareVersion();
            break;

        // Geodetic Navigation Data - Message ID 41.
        case 41:
            this->data.navType = (static_cast<uint16_t> (payload[3]) << 8) | static_cast<uint16_t> (payload[4]);

            switch (this->data.navType & 0x0007)
            {
                case 0x0003:
                case 0x0005:
                    this->data.fixType = GPSData::Fix2D;
                    break;

                case 0x0004:
                case 0x0006:
                    this->data.fixType = GPSData::Fix3D;
                    break;

                default:
                    this->data.fixType = GPSData::NoFix;
                    break;
            } // END switch

            this->data.weekNumber = (static_cast<uint32_t> (payload[5]) << 8) | static_cast<uint32_t> (payload[6]);
            this->data.timeOfWeek = (static_cast<uint32_t> (payload[7]) << 24) | (static_cast<uint32_t> (payload[8]) << 16) | (static_cast<uint32_t> (payload[9]) << 8) | static_cast<uint32_t> (payload[10]);

            this->data.year = (static_cast<uint16_t> (payload[11]) << 8) | static_cast<uint16_t> (payload[12]);
            this->data.month = static_cast<uint8_t> (payload[13]);
            this->data.day = static_cast<uint8_t> (payload[14]);

            this->data.hours = static_cast<uint8_t> (payload[15]);
            this->data.minutes = static_cast<uint8_t> (payload[16]);
            this->data.seconds = ((static_cast<uint16_t> (payload[17]) << 8) | static_cast<uint16_t> (payload[18])) / 1000;

            this->data.latitude = (static_cast<int32_t> (payload[23]) << 24) | (static_cast<int32_t> (payload[24]) << 16) | (static_cast<int32_t> (payload[25]) << 8) | static_cast<int32_t> (payload[26]);
            this->data.longitude = (static_cast<int32_t> (payload[27]) << 24) | (static_cast<int32_t> (payload[28]) << 16) | (static_cast<int32_t> (payload[29]) << 8) | static_cast<int32_t> (payload[30]);
            this->data.altitude = (static_cast<int32_t> (payload[35]) << 24) | (static_cast<int32_t> (payload[36]) << 16) | (static_cast<int32_t> (payload[37]) << 8) | static_cast<int32_t> (payload[38]);

            this->data.speed = (static_cast<uint16_t> (payload[40]) << 8) | static_cast<uint16_t> (payload[41]);
            this->data.heading= (static_cast<uint16_t> (payload[42]) << 8) | static_cast<uint16_t> (payload[43]);

            this->data.trackedSats = static_cast<uint32_t> (payload[88]);
            this->data.dop = (10 * static_cast<uint32_t> (payload[89])) / 5;

            break;

        // Messages we will ignore, but can't disable.
        //
        // Command Acknowledgment - Message ID 11.
        // Extended Ephemeris Data - Message ID 56.
        // Development Data - Message ID 255.
        case 11:
        case 56:
        case 255:
            break;

        // Set the following messages to rate 0 so we don't have to process them again.
        //
        // Measure Navigation Data Out - Message ID 2.
        // Response: Clock Status Data - Message ID 7.
        // CPU Throughput - Message ID 9.
        // DGPS Status - Format - Message ID 27.
        case 2:
        case 7:
        case 9:
        case 27:
            DisableMessage (payload[0]);
            break;

        default:
            break;
    }

}

/**
 *   Send message to generate software version.
 */
void GPSNavman::PollSoftwareVersion()
{
    uint8_t message[2] = { 132, 0 };

    // Clear the version string before we request the information.
    this->version[0] = 0x00;

    SendMessage (message, sizeof(message));
}

/**
 *   Send message to disable (set the rate to 0) of the desired message.
 *
 *   @param messageID of the message to disable
 */
void GPSNavman::DisableMessage(uint8_t messageID)
{
    uint8_t message[8] = { 166, 0, messageID, 0, 0, 0, 0, 0 };

    SendMessage (message, 8);
}

/**
 *   Generate a SiRF binary message with the header, length, payload, and
 *   checksum bytes.
 *
 *   @param message pointer to binary buffer holding message.
 *   @param length number of bytes in the message
 */
void GPSNavman::SendMessage(uint8_t *message, uint32_t length)
{
    uint32_t i, checksum;

    WriteData (0xa0);
    WriteData (0xa2);

    WriteData (((length >> 8) & 0x7f));
    WriteData (length & 0xff);

    checksum = 0x0000;

    for (i = 0; i < length; ++i)
    {
        WriteData (message[i]);
        checksum += message[i];
    }

    WriteData (((checksum >> 8) & 0x7f));
    WriteData (checksum & 0xff);

    WriteData (0xb0);
    WriteData (0xb3);
}

/**
 *  Read the serial FIFO and process any pending GPS messages.
 */
void GPSNavman::Update()
{
    uint32_t value;

    // State machine handles each byte as it is read from the GPS serial port.
    // We are looking for a SiRF binary message.
    // If we have a complete data set, all the routine to return so the calling thread can process the data set.
    while (HasData() && !this->dataReadyFlag)
    {
        // Get the character value.
        value = ReadData();

        // Process based on the state machine.
        switch (this->gpsParseState)
        {
            case GPSStart1:
                if (value == 0xa0)
                    this->gpsParseState = GPSStart2;
                break;

            case GPSStart2:
                if (value == 0xa2)
                    this->gpsParseState = GPSLengthMSB;
                else
                    this->gpsParseState = GPSStart1;
                break;

            case GPSLengthMSB:
                this->payloadLength = static_cast <uint32_t> (value) << 8;
                this->gpsParseState = GPSLengthLSB;
                break;

            case GPSLengthLSB:
                this->payloadLength |= static_cast <uint32_t> (value);

                if (this->payloadLength == 0)
                    this->gpsParseState = GPSChecksumMSB;
                else
                    this->gpsParseState = GPSPayload;

                    this->payloadChecksum = 0x0000;
                    this->payloadIndex = 0;
                break;

            case GPSPayload:
                this->payloadChecksum += value;

                if (this->payloadIndex < PayloadBufferSize)
                    this->payload[this->payloadIndex] = value;

                if (++this->payloadIndex == this->payloadLength)
                    this->gpsParseState = GPSChecksumMSB;

                break;

            case GPSChecksumMSB:
                if (((this->payloadChecksum >> 8) & 0x7f) == value)
                    this->gpsParseState = GPSChecksumLSB;
                else
                    this->gpsParseState = GPSStart1;
                break;

            case GPSChecksumLSB:
                if ((this->payloadChecksum & 0xff) == value)
                    this->gpsParseState = GPSEnd1;
                else
                    this->gpsParseState = GPSStart1;
                break;

            case GPSEnd1:
                if (value == 0xb0)
                    this->gpsParseState = GPSEnd2;
                else
                    this->gpsParseState = GPSStart1;
                break;

            case GPSEnd2:
                // Once we have the last character, convert the binary message to something usable.
                if (value == 0xb3)
                    ParseMessage();

                this->gpsParseState = GPSStart1;
                break;
        } // END switch
    } // END while
}

/**
 * Change from the NMEA-0183 mode to the SiRF Binary protocol mode at 57,600bps.
 */
void GPSNavman::SetBinaryProtocol()
{
    char *out, buffer[80];

    // Create the NEMA-0183 string that configures the GPS engine for SiRF Binary mode at 57,600 BPS, 8 data bits, No Parity, 1 stop bit.
    strcpy (buffer, "$PSRF100,0,57600,8,1,0");
    NMEA::AppendChecksum(buffer);
    strcat (buffer, "\015\012");

    // Write each character of the string.
    out = buffer;

    while (*out != 0)
        WriteData (*out++);
}

/**
 * Initialize the GPS engine using the select data source.
 *
 * @param source enumerated type of the desired data source
 */
void GPSNavman::InitializeDataSource (DataSource source)
{
    uint8_t payload[25];

    // Most of the payload is 0, so clear everything.
    memset (payload, 0, sizeof(payload));

    // Message ID and data source values.
    payload[0] = 128;
    payload[24] = static_cast<uint8_t> (source);

    SendMessage (payload, sizeof(payload));
}

/**
 * Write the current configuration settings to flash so they are retained during the next power cycle.
 */
void GPSNavman::WriteToFlash()
{
    uint8_t payload[1];

    payload[0] = 198;

    SendMessage (payload, sizeof(payload));
}

/**
 * GPS engine version information.
 *
 * @return pointer to NULL terminated string
 */
const char *GPSNavman::Version()
{
    return this->version;
}


