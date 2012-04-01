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
 * Filename:     MuxSwitch.cpp                                             *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

/**
 * Constructor.
 *
 * @param rowCount number of rows in the switch matrix
 * @param columnCount number of columns in the switch matrix
 */
MuxSwitch::MuxSwitch (uint32_t rowCount, uint32_t columnCount)
{
    this->rowCount = rowCount;
    this->columnCount = columnCount;
}

/**
 * Enable the multiplex switch driver.
 */
void MuxSwitch::Enable()
{
    uint32_t row, col;

    this->keys.Clear();
    this->tickCount = SystemControl::GetTick();

    for (row = 0; row < this->rowCount; ++row)
        for (col = 0; col < this->columnCount; ++col)
        {
            this->lastState[row][col] = false;
            this->debounceCount[row][col] = 0;
        } // END for
}

/**
 * Read and process the multiplex switch array.
 */
void MuxSwitch::Update()
{
    uint32_t columns, row, col;

    // Process the switch at a regular rate.
    if (this->tickCount > SystemControl::GetTick())
        return;

    // Time of the next scan.
    this->tickCount += ScanRate;

    // Scan the
    for (row = 0; row < this->rowCount; ++row)
    {
        // Set the matrix row selection.
        SetRow(row);

        // Get the selected columns.
        columns = GetColumn();

        for (col = 0; col < this->columnCount; ++col)
        {
            if ((columns & 0x01) == 0x01)
            {
                if (!this->lastState[row][col])
                {
                    this->lastState[row][col] = true;

                    if (this->debounceCount[row][col] == 0)
                        this->keys.Write((row << 4) | col);
                } // END if

                this->debounceCount[row][col] = DebounceCount;
            } else {
                this->lastState[row][col] = false;

                if (this->debounceCount[row][col] != 0)
                    --this->debounceCount[row][col];

            } // END if-else

            columns = columns >> 1;
        } // END for col
    } // END for row
}

/**
 * Indicate if the FIFO has keys.
 *
 * @return true if key has been pushed; otherwise false
 */
bool_t MuxSwitch::HasKey()
{
    return this->keys.HasData();
}

/**
 * Return the oldest entry in the FIFO.
 *
 * @return key pressed
 */
uint32_t MuxSwitch::GetKey()
{
    return this->keys.Read();
}
