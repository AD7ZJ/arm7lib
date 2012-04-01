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
 * Filename:     UARTBase.h                                                *
 *                                                                         *
 ***************************************************************************/

#ifndef UARTBASE_H
#define UARTBASE_H

/**
 *  @defgroup onchip On-Chip Peripherals
 *
 *  @{
 */

/**
*   Common methods and constants shared between UART 0 and UART 1.
*/
class UARTBase
{
public:
    void Clear();

    /// Enumeration that determines UART Baud Rate in BPS (Bits Per Second).
    typedef enum
    {
        /// 1,200 BPS (Bit Per Second).
        BaudRate1200 = 1200,

        /// 2,400 BPS (Bit Per Second).
        BaudRate2400 = 2400,

        /// 4,800 BPS (Bit Per Second).
        BaudRate4800 = 4800,

        /// 9,600 BPS (Bit Per Second).
        BaudRate9600 = 9600,

        /// 19,200 BPS (Bit Per Second).
        BaudRate19200 = 19200,

        /// 38,400 BPS (Bit Per Second).
        BaudRate38400 = 38400,

        /// 57,600 BPS (Bit Per Second).
        BaudRate57600 = 57600,

        /// 115,200 BPS (Bit Per Second).
        BaudRate115200 = 115200
    } BaudRate;

    /// Enumeration that specifies the line control mode.
    typedef enum
    {
        /// 8-data bits, no parity, 1 stop bit
        Control8N1 = 0x03,

        /// 8-data bits, odd parity, 1 stop bit
        Control8O1 = 0x0b
    } LineControl;

    /// Receive serial FIFO.
    FIFO fifo;
};

/** @} */

#endif // #ifndef UARTBASE_H
