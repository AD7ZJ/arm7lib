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
 * Filename:     UART1.h                                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef UART1_H
#define UART1_H

/**
 *  @defgroup onchip On-Chip Peripherals
 *
 *  @{
 */

/**
 *   Object that manages the UART 1 peripheral.
 */
class UART1 : public UARTBase
{
public:
    void Disable();
    void Enable(BaudRate baudRate, LineControl lineControl);
    bool_t IsCharReady();
    void ISR();
    uint8_t ReadChar();
    void SetLineControl (BaudRate baudRate, LineControl lineControl);
    void WriteChar (uint8_t text);
    
    static UART1 *GetInstance();
    
};

/** @} */

#endif // #ifndef UART1_H
