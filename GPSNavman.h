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
 * Filename:     GPSNavman.h                                               *
 *                                                                         *
 ***************************************************************************/

#ifndef GPSNAVMAN_H
#define GPSNAVMAN_H

/**
 *  @defgroup external External Peripherals
 *
 *  @{
 */

/**
 *   Read and process the SiRF Star III Binary messages from the Navman
 *   J30 and J32 GPS engines.
 */
class GPSNavman
{
public:
    /// Enumerated type of the desired initialization data source.
    typedef enum
    {
        /// Cold start.
        ColdStart = 0x46,

        /// Factory Reset: clears all GPS memory including clock drift. Also clears almanac stored in flash memory.
        FactoryReset = 0x08
    } DataSource;

    GPSNavman();

    GPSData *Data();
    void InitializeDataSource (DataSource source);
    bool_t IsDataReady();
    bool_t IsOkToSend();
    void SetBinaryProtocol();
    void Update();
    void WriteToFlash();
    const char *Version();

    /**
     *   Callback to determine if the there is serial data to process from the GPS engine.
     *
     *    @return true if data is in FIFO; otherwise false
     */
    virtual bool_t HasData();

    /**
     *   Callback to read the oldest serial data from the GPS engine.
     *
     *   @return oldest byte from serial FIFO
     */
    virtual uint8_t ReadData();

    /**
     *   Callback to write serial data to the GPS engine.
     *
     *   @param data 8-bit data to write
     */
    virtual void WriteData(uint8_t data);

    static GPSNavman *GetInstance();

private:
    /// Number of bytes in the payload message buffer.
    static const uint32_t PayloadBufferSize = 200;

    /// Number of bytes in the software version string.
    static const uint32_t VersionSize = 64;

    void DisableMessage(uint8_t messageID);
    void ParseMessage();
    void PollSoftwareVersion();
    void SendMessage(uint8_t *payload, uint32_t length);

    /// GPS parse engine state machine values.
    typedef enum
    {
        /// 1st start character 0xa0.
        GPSStart1,

        /// 2nd start character 0xa2.
        GPSStart2,

        /// MSB of payload length.
        GPSLengthMSB,

        /// LSB of payload length.
        GPSLengthLSB,

        /// 0 - xx bytes based on message length.
        GPSPayload,

        /// 8-bit checksum.
        GPSChecksumMSB,

        /// 8-bit checksum.
        GPSChecksumLSB,

        /// 1st end character 0xb0.
        GPSEnd1,

        /// 2nd end character 0xb3.
        GPSEnd2,
    } GPSParseStateMachine;

    /// Object that stores the current GPS fix data.
    GPSData data;

    /// Index into gpsBuffer used to store message data.
    uint32_t payloadIndex;

    /// Number of bytes in the message payload.
    uint32_t payloadLength;

    /// Calculated payload checksum.
    uint32_t payloadChecksum;

    /// State machine used to parse the GPS message stream.
    GPSParseStateMachine gpsParseState;

    /// Buffer to store data as it is read from the GPS engine.
    uint8_t payload[PayloadBufferSize];

    /// Buffer to store the software version.
    char version[VersionSize];

    /// Flag that is set when a data set has been parsed.
    bool_t dataReadyFlag;

    /// Flag that is set when the OK To Send message is received.
    bool_t okToSendFlag;
};

/** @} */

#endif // #ifndef GPSNAVMAN_H
