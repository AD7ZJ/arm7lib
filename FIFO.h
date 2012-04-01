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
 * Filename:     FIFO.h                                                    *
 *                                                                         *
 ***************************************************************************/

#ifndef FIFO_H
#define FIFO_H

/**
 *  @defgroup library Generic Library Functions
 *
 *  @{
 */

/**
 * Generic FIFO suitable for UART ports and other 8-bit based devices
 * that require a data FIFO.
 */
class FIFO
{
public:
    FIFO();

    void Clear();
    bool_t HasData();
    uint8_t Read();
    void Write(uint8_t value);

private:
    /// Size of serial port FIFO in bytes.  It must be a power of 2, i.e. 2, 4, 8, 16, etc.
    static const uint32_t FIFOBufferSize = 256;

    /// Mask to wrap around at end of circular buffer.  (SERIAL_BUFFER_SIZE - 1)
    static const uint32_t FIFOBufferMask = 0x00ff;

    /// Index to the next free location in the buffer.
    uint32_t head;

    /// Index to the next oldest data in the buffer.
    uint32_t tail;

    /// Circular buffer (FIFO) to hold serial data.
    uint8_t buffer[FIFOBufferSize];
};

/** @} */

#endif  // #ifndef FIFO_H

