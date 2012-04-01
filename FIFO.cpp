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
 * Filename:     FIFO.cpp                                                  *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

/**
 *  Constructor.
 */
FIFO::FIFO()
{
    Clear();
}

/**
 * Clear the FIFO contents.
 */
void FIFO::Clear()
{
    this->head = 0;
    this->tail = 0;
}

/**
 * Determine if the FIFO contains data.
 *
 * @return true if data present; otherwise false
 */
bool_t FIFO::HasData()
{
    if (head == tail)
        return false;

    return true;
}

/**
 * Get the oldest character from the FIFO.
 *
 * @return oldest character; 0 if FIFO is empty
 */
uint8_t FIFO::Read()
{
    uint8_t value;

    // Make sure we have something to return.
    if (head == tail)
        return 0;

    // Save the value.
    value = buffer[tail];

    // Update the pointer.
    tail = (tail + 1) & FIFOBufferMask;

    return value;
}

/**
 * Store a new character in the FIFO.
 *
 * @param value character to add to FIFO.
 */
void FIFO::Write(uint8_t value)
{
    // Save the value in the FIFO.
    buffer[head] = value;

    // Move the pointer to the next open space.
    head = (head + 1) & FIFOBufferMask;
}


