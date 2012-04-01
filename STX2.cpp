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
 * Filename:     STX2.cpp                                                  *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

/// Reserve memory for singleton object.
static STX2 stx2SingletonObject;

/**
 *  Pointer to the Radio MODEM object.
 */
STX2 *STX2::GetInstance()
{
    return &stx2SingletonObject;
}

/**
 * Set the state machine and control lines to place the MODEM in the sleep state.
 */
void STX2::Enable()
{
    // Set the RTS high to enter sleep mode after power on
    SetRTS(true);

    // Initial MODEM state machine.
    this->modemState = PowerOn;

    // Time the unit was powered on.
    this->timeStamp = SystemControl::GetTick() + PowerOnTime;

    // Default MODEM channel.
    this->channel = ChannelA;

    // Clear flag that indicates a message is in progress.
    this->txMessageFlag = false;

    // Set the receive message state machine.
    this->parseMessageState = WaitPreamble;

    // Unknown unit ID.
    this->unitID = UnknownID;
    this->firmwareVersion = UnknownID;

    // Set the flag to indicate the Modem isn't ready.
    this->modemReady = false;
}

/**
 * Get the unit ID.
 *
 * @return 27-bit unit ID (ESN - Electronic Serial Number)
 */
uint32_t STX2::UnitID()
{
    return this->unitID;
}

/**
 * Get the firmware ID.
 *
 * @return major and minor firmware version
 */
uint32_t STX2::FirmwareVersion()
{
    return this->firmwareVersion;
}

/**
 * Transmit a packet using the Air Interface Message.
 *
 * @param data pointer to data to transmit
 * @param length number of bytes in message
 */
void STX2::TransmitPacket(const uint8_t *data, uint32_t length)
{
    // We'll just ignore any extra data.
    if (length > MaxDataBytes)
        length = MaxDataBytes;

    SendMessage (PacketTransmit, data, length);
}

/**
 * Generate the serial packet format message and send it to the MODEM.
 *
 * @param command 8-bit command
 * @param data pointer to optional variable length data buffer
 * @param length number of bytes in buffer
 */
void STX2::SendMessage (uint32_t command, const uint8_t *data, uint32_t length)
{
    uint32_t i, crc;

    if (this->txMessageFlag)
        return;

    // Preamble byte.
    this->txMessage[0] = PacketPreamble;

    // Total number of bytes in the serial packet including the preamble.
    this->txMessage[1] = (5 + length);

    // 8-bit command value.
    this->txMessage[2] = command & 0xff;

    // Save the variable length data.
    for (i = 0; i < length; ++i)
        this->txMessage[3 + i]  = data[i];

    // Calculate the CRC-16 over the header and data block.
    crc = CRC16::Calculate (this->txMessage, 3 + length, 0xffff);

    // Append the CRC data little endian first.
    this->txMessage[3 + length] = crc & 0x00ff;
    this->txMessage[4 + length] = (crc >> 8) & 0x00ff;

    this->txMessageLength = 5 + length;

    this->txMessageFlag = true;
}

/**
 * Process an incoming message.
 */
void STX2::ProcessMessage()
{
    uint32_t crc;
    uint8_t setup[9] = { 0, 0, 0, 0, 0x00, 3, 12, 13, 0 };

    // Calculate the CRC-16 of the message contents.
    crc = CRC16::Calculate (this->rxMessage, this->rxMessageLength - 2, 0xffff);

    // Check the LSB and MSB.
    if ((crc & 0x00ff) != this->rxMessage[this->rxMessageLength - 2])
        return;

    if (((crc >> 8) & 0x00ff) != this->rxMessage[this->rxMessageLength - 1])
        return;


//    USART4::GetInstance()->WriteLine("0x%x", this->rxMessage[2]);


    switch (this->rxMessage[2])
    {
        case 0x01:
            this->unitID = (static_cast<uint32_t> (this->rxMessage[3]) << 24) | (static_cast<uint32_t> (this->rxMessage[4]) << 16) | (static_cast<uint32_t> (this->rxMessage[5]) << 8) | (static_cast<uint32_t> (this->rxMessage[6]));
            SystemControl::Sleep(10);
            SendMessage (RequestFirmwareID, NULL, 0);
            break;

        case 0x05:
            this->firmwareVersion = (static_cast<uint32_t> (this->rxMessage[3]) << 8) | static_cast<uint32_t> (this->rxMessage[4]);

            SystemControl::Sleep(10);
            SendMessage (SetupMessageID, setup, sizeof(setup));
            break;

        case 0x06:
            SystemControl::Sleep(10);

            SendMessage (QuerySetupMessageID, NULL, 0);
            break;

        case 0x07:
            this->modemReady = true;
            break;
    } // END switch
}

/**
 * Update the transmit and receive state machines.
 */
void STX2::Update()
{
    uint32_t i, value;

    while (HasData())
    {
        value = ReadData();

        switch (this->parseMessageState)
        {
            case WaitPreamble:
                if (value == PacketPreamble)
                    this->parseMessageState = WaitLength;
                break;

            case WaitLength:
                this->rxMessage[0] = PacketPreamble;
                this->rxMessage[1] = value;

                if (value < 5 || value > MaxDataBytes)
                    this->parseMessageState = WaitPreamble;
                else
                {
                    this->rxMessageLength = value;
                    this->parseMessageState = WaitPayload;
                    this->rxMessageIndex = 2;
                }
                break;

            case WaitPayload:
                // Save the message until we fill the buffer.
                if (this->rxMessageIndex < sizeof(this->rxMessage))
                    this->rxMessage[this->rxMessageIndex] = value;

                if (++this->rxMessageIndex == this->rxMessageLength)
                {
                    ProcessMessage();
                    this->parseMessageState = WaitPreamble;
                } // END if
                break;
        } // END switch
    } // END if

    switch (this->modemState)
    {
        case PowerOn:
            if (SystemControl::GetTick() > this->timeStamp)
            {
                this->modemState = Sleep;

                SendMessage (RequestUnitID, NULL, 0);
            } // END if

            break;

        case Sleep:
            if (this->txMessageFlag)
            {
                SetRTS (false);
                this->modemState = WaitClearToSend;
                this->timeStamp = SystemControl::GetTick() + 0; // TODO
            } // END if

            break;

        case WaitClearToSend:
            if (!IsCTS())
            {
                for (i = 0; i < this->txMessageLength; ++i)
                    WriteData(this->txMessage[i]);

                SystemControl::Sleep(20);

                SetRTS (true);

                this->modemState = Sleep;
                this->txMessageFlag = false;
            } // END if

            break;
    } // END switch
}

/**
 * Indicates if the Modem is ready to accept incoming messages.
 *
 * @return true if ready; otherwise false
 */
bool_t STX2::IsReady()
{
    return this->modemReady;
}
