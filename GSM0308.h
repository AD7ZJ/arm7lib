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
 * Filename:     GSM0308.h                                                 *
 *                                                                         *
 ***************************************************************************/

#ifndef GSM0308_H
#define GSM0308_H

/**
 *  @defgroup external External Peripherals
 *
 *  @{
 */

/**
 *   Manage the Enfora Enabler III GSM/GPRS/EDGE Radio MODEM.
 */
class GSM0308
{
public:
    GSM0308();

    /**
     *   Call back to determine if the there is serial data to process from the Radio MODEM.
     *
     *    @return true if data is in FIFO; otherwise false
     */
    virtual bool_t HasData();

    /**
     *   Call back to read the oldest serial data from the Radio MODEM.
     *
     *   @return oldest byte from serial FIFO
     */
    virtual uint8_t ReadData();

    /**
     *   Call back to write serial data to the Radio MODEM.
     *
     *   @param data 8-bit data to write
     */
    virtual void WriteData(uint8_t data);

    /**
     * Call back to reset the Modem.
     *
     * @param state true to hold device in reset; otherwise false
     */
    virtual void Reset(bool_t state);

    uint32_t CellID();
    bool_t IsModemReset();
    bool_t IsSMSReady();
    bool_t IsRegistered();
    bool_t IsResponseReady();
    uint32_t LastResetTime();
    uint32_t LocationAreaCode();
    void Register();
    const char *Response();
    int32_t RSSI();
    uint32_t RxQual();
    void SendSMS (const char *destinationAddress, const char *message);
    void SendString(const char *text, ...);
    void Update();
    const char *Version();

    static GSM0308 *GetInstance();

private:
    /// Maximum number of characters to record in a MODEM response.
    static const uint32_t MaxATLength = 250;

    /// Number of bytes in the firmware version string.
    static const uint32_t VersionSize = 64;

    /// GSM MODEM message parsing state machine values.
    typedef enum
    {
        /// The Modem is held in reset.
        InReset,

        /// Time period to hold Modem in reset before it is released and booted.
        HoldResetLow,

        /// Wait for the POST (Power On Self Test) message.
        WaitPowerOnSelfTest,

        /// Wait for OK after sending 'AT' command to Modem.
        WaitResetOK,

        /// Wait for OK after sending configuration commands to Modem.
        WaitSetupOK,

        /// Wait for the OK after sending the request for the firmware version.
        WaitVersionOK,

        /// Wait for network registration to complete.
        WaitNetworkRegistered,

        /// The Modem has registered with the network.
        NetworkRegistered,

        /// The Modem is registered and ready for SMS commands.
        NetworkRegisteredReady
    } ParseMessageStateMachine;

    void ClearData();

    /// Buffer to store the MODEM response until receiving the terminating Carriage Return / Line Feed.
    char response[MaxATLength];

    /// Index into response buffer.
    uint32_t responseIndex;

    /// Flag that indicates a complete response is ready.
    bool_t responseReadyFlag;

    /// Flag that indicates the Modem was reset.
    bool_t resetFlag;

    /// 16-bit location area code.
    uint32_t locationAreaCode;

    /// 16-bit cell ID.
    uint32_t cellID;

    /// Scaled RSSI (Receive Signal Strength Indicator) in units of 2dB starting at -113dBm.
    uint32_t rssi;

    /// BER (Bit Error Rate) value in the range 0 to 7 as defined by GSM standard.
    uint32_t rxQual;

    /// Tick count used to determine next timed action in Modem message parsing.
    uint32_t nextResponseTime;

    /// Tick count of last Modem reset.
    uint32_t lastResetTime;

    /// Current state of Modem parse state machine.
    ParseMessageStateMachine parseState;

    /// One shot flag that indicates the Modem is ready for SMS messages.
    bool_t smsReady;

    /// Buffer to store the firmware version.
    char version[VersionSize];
};

/** @} */

#endif // #ifndef GSM0308_H
