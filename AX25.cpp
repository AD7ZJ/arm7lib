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
 * Filename:     AX25.cpp                                                  *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

/**
 * Constructor.
 */
AX25::AX25()
{
    this->preambleCount = 45;
    this->ax25HeaderLength = 0;
}

/**
 * Get the data stream suitable for synchronous transmission that includes the
 * preamble, header, payload, and CRC check bytes.  The data is stored in a byte
 * array with the message stream from LSB to MSB in each byte.  The data bits are
 * NRZI encoded, so for proper playback a 0 bit is tone A and a 1 bit is tone B.
 * Typical tones are 1200 and 2200Hz.
 *
 * @return pointer to data stream
 */
const uint8_t *AX25::Stream()
{
    return this->txBuffer;
}

/**
 * Get the number of bytes in the AX25 data stream.
 */
uint32_t AX25::Length()
{
    return this->streamIndex;
}

/**
 * Set the preamble message flag count.  Each flag represents 8 data bits or 6.67mS.
 *
 * @param count in flag counts
 */
void AX25::SetPreambleCount(uint32_t count)
{
    this->preambleCount = count;
}

/**
 * Set the AX.25 destination address and SSID.
 *
 * @param address pointer to NULL terminated string that contains destination address
 * @param ssid SSID in the range 0 to 15.
 */
void AX25::SetDestAddress (const char *address, uint32_t ssid)
{
    SetAddress (DestAddressOffset, address);

    this->ax25Header[DestAddressOffset + 6] = 0x60 | (ssid << 1);
}

/**
 * Set the AX.25 source address and SSID.
 *
 * @param address pointer to NULL terminated string that contains source address
 * @param ssid SSID in the range 0 to 15.
 */
void AX25::SetSourceAddress (const char *address, uint32_t ssid)
{
    SetAddress (SourceAddressOffset, address);

    this->ax25Header[SourceAddressOffset + 6] = 0x60 | (ssid << 1);
}

/**
 * Set the AX.25 digipeater path and SSID.
 *
 * @param path pointer to NULL terminated string that contains digipeater path
 * @param ssid SSID in the range 0 to 15.
 */
void AX25::SetDigiPath (const char *path, uint32_t ssid)
{
    SetAddress (DigiPath1Offset, path);

    this->ax25Header[DigiPath1Offset + 6] = 0x61 | (ssid << 1);
    this->ax25Header[DigiPath1Offset + 7] = 0x03;
    this->ax25Header[DigiPath1Offset + 8] = 0xf0;

    this->ax25HeaderLength = 23;
}

/**
 * Set the AX.25 digipeater path and SSID.
 *
 * @param path1 pointer to NULL terminated string that contains the first digipeater path
 * @param ssid1 SSID in the range 0 to 15.
 * @param path2 pointer to NULL terminated string that contains the second digipeater path
 * @param ssid2 SSID in the range 0 to 15.
 */
void AX25::SetDigiPath (const char *path1, uint32_t ssid1, const char *path2, uint32_t ssid2)
{
    SetAddress (DigiPath1Offset, path1);

    this->ax25Header[DigiPath1Offset + 6] = 0x60 | (ssid1 << 1);

    SetAddress (DigiPath2Offset, path2);

    this->ax25Header[DigiPath2Offset + 6] = 0x61 | (ssid2 << 1);
    this->ax25Header[DigiPath2Offset + 7] = 0x03;
    this->ax25Header[DigiPath2Offset + 8] = 0xf0;

    this->ax25HeaderLength = 30;
}

/**
 * Convert the ASCII address into an AX.25 compatible source, destination, or digipeater path.
 *
 * @param offset in bytes to the location to write the address
 * @param address NULL terminate string, up to 6-charcters long that contains the address
 */
void AX25::SetAddress (uint32_t offset, const char *address)
{
    uint32_t i;

    // Save up to 6-characters.
    for (i = 0; i < 6 && address[i] != 0; ++i)
        this->ax25Header[i + offset] = address[i] << 1;

    // Pad the rest of the address with spaces.
    for (; i< 6; ++i)
        this->ax25Header[i + offset] = ' ' << 1;
}

/**
 * Generate an AX.25 APRS compatible message with the plain text string message.
 *
 * @param message NULL terminate string to transmit
 */
void AX25::GenerateMessage(const char *message)
{
    uint32_t i, crc;

    StartStream();

    // Preamble sent before actual message to give radio squelch time to open.
    for (i = 0; i < this->preambleCount; ++i)
        AddStream (0x7e, false);

    // Add the AX.25 header.
    for (i = 0; i < this->ax25HeaderLength; ++i)
        AddStream (this->ax25Header[i]);

    // Add the message contents.
    for (i = 0; message[i] != 0; ++i)
        AddStream (message[i]);

    crc = CRC16::Calculate(this->ax25Header, this->ax25HeaderLength, 0xffff);
    crc = CRC16::Calculate(message, strlen(message), crc ^ 0xffff);

    // Message CRC-16 over the header and message contents.
    AddStream (crc & 0xff);
    AddStream (crc >> 8);

    // Add an extra message delimter to flush the output buffer.
    AddStream (0x7e, false);
    AddStream (0x7e, false);

    EndStream();
}

/**
 * Prepare to generate a new message.  This method must be called before adding bits
 * to the stream.
 */
void AX25::StartStream()
{
    this->streamIndex = 0;
    this->streamBitCount = 0;
    this->streamBitAccum = 0x00;
    this->streamBitStuff = 0;
    this->lastBit = false;
}

/**
 * Complete the generation of the message.
 */
void AX25::EndStream()
{
    // If we have an odd number of bits left in the output stream, pad them with '0' bits.
    while (streamBitCount != 0)
        AddBit (false);
}

/**
 * Add a byte to the output stream and optionally perform "bit stuffing" on it.  Bit
 * stuffing is an operation to eliminate long strings of '1' bit values.  If we find
 * five '1' values in a row, insert an extra '0' bit.  We can optionally disable this
 * feature if we want to allow strings of '1' values, for instance, when sending the
 * start flag.
 *
 * @param value 8-bit value to add to stream
 * @param bitStuffFlag true to add extra '0' values
 */
void AX25::AddStream(uint32_t value, bool_t bitStuffFlag)
{
    uint32_t i;

    for (i = 0; i < 8; ++i)
    {
        // Determine if we have sent 5 ones in a row, if we have add a zero to the stream.
        if (bitStuffFlag)
        {
            if (streamBitStuff == 0x1f)
            {
                if (lastBit)
                    lastBit = false;
                else
                    lastBit = true;

                streamBitStuff = 0x00;

                AddBit (lastBit);
            }    // END if

            // Save the data stream so we can determine if bit stuffing is
            // required on the next bit time.
            streamBitStuff = ((streamBitStuff << 1) | (value & 0x01)) & 0x1f;
        } // END if

        // NRZI encode the data stream.
        if ((value & 0x01) == 0x00)
        {
            if (lastBit)
                lastBit = false;
            else
                lastBit = true;
        } // END if

        AddBit (lastBit);

        // Shift through each bit.
        value = value >> 1;
    } // END for
}

/**
 * Add a single bit to the output stream as it is stored in a byte array.
 *
 * @param bit true or false bit to add to stream
 */
void AX25::AddBit (bool_t bit)
{
    // Prevent writing past the buffer.  We don't throw an error, but we'll know when our message fails.
    if (streamIndex == TxBufferSize)
        return;

    // Accumulate each bit LSB first.
    streamBitAccum = (streamBitAccum >> 1) | (bit ? 0x80 : 0x00);

    // When we have 8-bits save it as a byte and reset to we can store the next one.
    if (++streamBitCount == 8)
    {
        streamBitCount = 0;

        txBuffer[streamIndex++] = streamBitAccum;
        streamBitAccum = 0;
    } // END if
}
