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
 * Filename:     USBFIFO.cpp                                               *
 *                                                                         *
 ***************************************************************************/
 
#include "armlib.h"

/**
 *  Constructor.
 */
USBFIFO::USBFIFO()
{
    this->head = 0;
    this->tail = 0;
}

/**
 * Determine if the FIFO contains one or more entries.
 *
 * @return true if data present; otherwise false
 */
bool_t USBFIFO::HasEntry()
{
    if (this->head == this->tail)
        return false;

    return true;
}

/**
 *   Get the oldest USBHIDReport object from the FIFO.
 *
 *   @return oldest HID Report; otherwise NULL if the FIFO is empty
 */
USBHIDReport *USBFIFO::Pop()
{
    USBHIDReport *value;
    
    // Make sure we have something to return.
    if (this->head == this->tail)
        return NULL;

    // Save the value.
    value = &this->fifo[this->tail];

    // Update the pointer.
    this->tail = (this->tail + 1) & FIFO_SIZE_MASK;

    return value;
}

/**
 * Store a binary block as a USBHIDReport object in the FIFO.
 * 
 * @param value pointer to binary block to store as a USBHIDReport object
 */
void USBFIFO::Push(uint8_t *value)
{
    // Save the data in the FIFO.
    std::memcpy (this->fifo[this->head].Payload(), value, USBHIDReport::REPORT_SIZE);
    
    // Move the pointer to the next open space.
    this->head = (this->head + 1) & FIFO_SIZE_MASK;
}


