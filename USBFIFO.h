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
 * Filename:     USBFIFO.h                                                 *
 *                                                                         *
 ***************************************************************************/

#ifndef USBFIFO_H
#define USBFIFO_H

/**
 *  @defgroup library Generic Library Functions
 *
 *  @{
 */

/**
 * FIFO to hold received HID reports.
 */
class USBFIFO
{
public:
    USBFIFO();
    
    void Push (uint8_t *buffer);
    bool_t HasEntry();
    USBHIDReport *Pop();

    
private:
    /// Size of serial port FIFO in bytes.  It must be a power of 2, i.e. 2, 4, 8, 16, etc.
    static const uint32_t FIFO_SIZE = 8;

    /// Mask to wrap around at end of circular buffer.  (FIFO_SIZE - 1)
    static const uint32_t FIFO_SIZE_MASK = 0x07;

    /// Index to the next free location in the buffer.
    uint32_t head;
    
    /// Index to the next oldest data in the buffer.
    uint32_t tail;
    
    /// Circular buffer (FIFO) to hold USBHIDReport objects.
    USBHIDReport fifo[FIFO_SIZE];        
};

/** @} */

#endif  // #ifndef USBFIFO_H

