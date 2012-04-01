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
 * Filename:     STX2.h                                                    *
 *                                                                         *
 ***************************************************************************/

#ifndef STX2_H
#define STX2_H

/**
 *  @defgroup external External Peripherals
 *
 *  @{
 */

/**
 *   Manage the Global Star STX2 Radio MODEM.
 */
class STX2
{
public:
    /**
     * Callback to determine if the there is serial data to process from the Radio MODEM.
     *
     * @return true if data is in FIFO; otherwise false
     */
    bool_t HasData();

    /**
     * Callback to read the oldest serial data from the Radio MODEM.
     *
     * @return oldest byte from serial FIFO
     */
    uint8_t ReadData();

    /**
     * Callback to write serial data to the Radio MODEM.
     *
     * @param data 8-bit data to write
     */
    void WriteData(uint8_t data);

    /**
     * Callback to set the RTS (Request To Send) control line.
     *
     * @param state true to set RTS high; otherwise false
     */
    void SetRTS(bool_t state);

    /**
     * Callback to return the state of the CTS (Clear To Send) control line.
     *
     * @return true if CTS is high; otherwise false
     */
    bool_t IsCTS();

    /// Enumeration of available RF Channel selections.
    typedef enum
    {
        /// Channel A - RF center frequency 1611.25MHz
        ChannelA,

        /// Channel B - RF center frequency 1613.75MHz
        ChannelB,

        /// Channel C - RF center frequency 1616.25MHz
        ChannelC,

        /// Channel D - RF center frequency 1618.75MHz
        ChannelD
    } RFChannel;

    static const uint32_t UnknownID = 0xffffffff;

    void Enable();
    uint32_t FirmwareVersion();
    bool_t IsReady();
    void ProcessMessage();
    void TransmitPacket(const uint8_t *data, uint32_t length);
    uint32_t UnitID();
    void Update();

    static STX2 *GetInstance();

private:
    /// Enumeration of the MODEM state.
    typedef enum
    {
        /// Wait 100mS for power on sequence to complete.
        PowerOn,

        /// MODEM in sleep mode waiting for RTS.
        Sleep,

        /// Waiting for assertion of CTS.
        WaitClearToSend
    } MODEMState;

    /// Enumeration of packet decoder state machine.
    typedef enum
    {
        /// Pre-amble character.
        WaitPreamble,

        /// Length of message.
        WaitLength,

        /// Payload bytes and 2-byte CRC-16.
        WaitPayload
    } ParseMessageState;

    void SendMessage (uint32_t command, const uint8_t *data, uint32_t length);

    /// Transmit Packet - Preamble.
    static const uint32_t PacketPreamble = 0xaa;

    /// Transmit Packet - Serial packet format command identifier.
    static const uint32_t PacketTransmit = 0x00;

    /// Request unit ID message - Serial packet format command identifier.
    static const uint32_t RequestUnitID = 0x01;

    /// Request firmware and interface ID - Serial packet format command identifier.
    static const uint32_t RequestFirmwareID = 0x05;

    /// Setup Message ID - Serial packet format command identifier.
    static const uint32_t SetupMessageID = 0x06;

    /// Setup Message ID - Serial packet format command identifier.
    static const uint32_t QuerySetupMessageID = 0x07;

    /// Maximum number of bytes in a serial transmit packet.
    static const uint32_t MaxDataBytes = 144;

    /// Number of milliseconds to wait after power on before sending a command.
    static const uint32_t PowerOnTime = 100;

    /// MODEM state.
    MODEMState modemState;

    /// Time tick of the last change in the MODEM state.
    uint32_t timeStamp;

    /// Currently selected RF channel.
    RFChannel channel;

    /// Transmit message buffer.
    uint8_t txMessage[5 + MaxDataBytes];

    /// Number of bytes in the transmit message buffer.
    uint32_t txMessageLength;

    /// Flag that indicates a transmit is in progress.
    bool_t txMessageFlag;

    /// Message parse state machine.
    ParseMessageState parseMessageState;

    /// Receive message buffer.
    uint8_t rxMessage[5 + MaxDataBytes];

    /// Index into rxMessage buffer when receiving data.
    uint32_t rxMessageIndex;

    /// Length of the received message.
    uint32_t rxMessageLength;

    /// Unit ID from device.
    uint32_t unitID;

    /// Firmware and interface version.
    uint32_t firmwareVersion;

    /// Flag that indicates the Modem unit ID, version, and setup are complete.
    bool_t modemReady;
};

/** @} */

#endif // #ifndef STX2_H
