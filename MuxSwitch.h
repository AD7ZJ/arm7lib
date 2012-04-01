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
 * Filename:     MuxSwitch.h                                               *
 *                                                                         *
 ***************************************************************************/

#ifndef MUXSWITCH_H
#define MUXSWITCH_H

/**
 *  @defgroup external External Peripherals
 *
 *  @{
 */

/**
 * Manages a generic multiplex switch array by providing a queue and
 * de-bounce functions.
 */
class MuxSwitch
{
public:
    /**
     * Callback to set the row select line.
     *
     * @param row index in the range 0 to rowCount
     */
    virtual void SetRow(uint32_t row);

    /**
     * Callback to get the selected column(s).
     *
     * @return bit map of selected columns.
     */
    virtual uint32_t GetColumn();

    /// Enumerate type that indicates which button in the matrix was pushed.
    typedef enum
    {
        Row1Col1 = 0x00,

        Row1Col2 = 0x01,

        Row1Col3 = 0x02,

        Row1Col4 = 0x03,

        Row1Col5 = 0x04,


        Row2Col1 = 0x10,

        Row2Col2 = 0x11,

        Row2Col3 = 0x12,

        Row2Col4 = 0x13,

        Row2Col5 = 0x14,


        Row3Col1 = 0x20,

        Row3Col2 = 0x21,

        Row3Col3 = 0x22,

        Row3Col4 = 0x23,

        Row3Col5 = 0x24
    } KeyIndex;

    MuxSwitch (uint32_t rowCount, uint32_t columnCount);

    void Enable();
    bool_t HasKey();
    uint32_t GetKey();
    void Update();

private:
    /// Maximum number of rows in the switch matrix.
    static const uint32_t MaxRowCount = 5;

    /// Maximum number of columns in the switch matrix.
    static const uint32_t MaxColumnCount = 5;

    /// Scan rate in milliseconds.
    static const uint32_t ScanRate = 20;

    /// The debounce count in scan rate periods.
    static const uint32_t DebounceCount = 2;

    /// Array that stores the last button state.
    bool_t lastState[MaxRowCount][MaxColumnCount];

    /// Array that stores the debounce count for each switch.
    uint8_t debounceCount[MaxRowCount][MaxColumnCount];

    /// The number of rows in the switch matrix.
    uint32_t rowCount;

    /// The number of columns in the switch matrix.
    uint32_t columnCount;

    /// FIFO that stores each key press.
    FIFO keys;

    /// System timer tick used to determine when to process and debounce the switch matrix.
    uint32_t tickCount;
};

/** @} */

#endif // #ifndef MUXSWITCH_H

