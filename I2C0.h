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
 * Filename:     I2C0.h                                                    *
 *                                                                         *
 ***************************************************************************/

#ifndef I2C0_H
#define I2C0_H

/**
 *  @defgroup onchip On-Chip Peripherals
 *
 *  @{
 */

/**
 *   Object that manages the I2C 0 peripheral port.
 */
class I2C0
{
public:
    void Enable();
    void Read (uint8_t *data, uint32_t count);
    bool_t Start(uint32_t data);
    void Stop();
    void Write (const uint8_t *data, uint32_t count);
    
    static I2C0 *GetInstance();
    
private:
    bool_t WaitInterrupt();

};

/** @} */

#endif // #ifndef I2C0_H
