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
 * Filename:     AX25.h                                                    *
 *                                                                         *
 ***************************************************************************/

#ifndef AX25_H
#define AX25_H

/**
 *  @defgroup library Generic Library Functions
 *
 *  @{
 */


/**
 *  Generate the bit stream required for an AX.25 message.
 */
class AX25
{
public:
    AX25();
    void GenerateMessage(const char *message);
    const uint8_t *Stream();
    uint32_t Length();
    void SetDestAddress (const char *address, uint32_t ssid);
    void SetDigiPath (const char *path, uint32_t ssid);
    void SetDigiPath (const char *path1, uint32_t ssid1, const char *path2, uint32_t ssid2);
    void SetPreambleCount(uint32_t count);
    void SetSourceAddress (const char *address, uint32_t ssid);

private:
    /// Number of bytes to hold the complete message with NRZI encoding and bit stuffing.    
    static const uint32_t TxBufferSize = 200;
    
    /// Offset in bytes to the destination address.
    static const uint32_t DestAddressOffset = 0;

    /// Offset in bytes to the source address.
    static const uint32_t SourceAddressOffset = 7;

    /// Offset in bytes to the first Digipeater path.
    static const uint32_t DigiPath1Offset = 14;    
    
    /// Offset in bytes to the second Digipeater path.
    static const uint32_t DigiPath2Offset = 21;  
    
    /// Maximum number of bytes in the AX.25 header.  (Should be enough bytes for the destination, source, 2 paths, and terminating bytes.
    static const uint32_t AX25HeaderSize = 30;
    
    void AddBit (bool_t bit);
    void AddStream (uint32_t value, bool_t bitStuffFlag = true);
    void EndStream();
    void SetAddress (uint32_t offset, const char *address);
    void StartStream();

    /// Number of 0x7e start flags to add to the start of the message.
    uint32_t preambleCount;

    /// Index into the output stream buffer.
    uint32_t streamIndex;

    /// Count the number of bits that have been added to the current output stream byte.
    uint32_t streamBitCount;

    /// Accumulator that stores each bit until we have 8 of them for the output stream byte.
    uint32_t streamBitAccum;

    /// Last 5 bits that have been written to the output stream to determine if we need to bit stuff the output.
    uint32_t streamBitStuff;

    /// The last bit that was written to the output stream so we can NRZI encode the stream.
    bool_t lastBit;

    /// Buffer to store the bit stream.
    uint8_t txBuffer[TxBufferSize];

    /// Buffer that contains the AX.25 header.
    uint8_t ax25Header[AX25HeaderSize];
    
    /// Number of bytes in the AX.25 header.
    uint32_t ax25HeaderLength;
};

/** @} */

#endif  // #ifndef AX25_H
