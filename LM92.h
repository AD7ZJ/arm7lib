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
 * Filename:     LM92.h                                                    *
 *                                                                         *
 ***************************************************************************/

#ifndef LM92_H
#define LM92_H

/**
 *  @defgroup external External Peripherals
 *
 *  @{
 */

/**
 *  Control the National Semiconductor Temperature Sensor.
 *  The LM92 is a digital temperature sensor and thermal window
 *  comparator with an I2C Serial Bus interface and an
 *  accuracy of �0.33�C.
 */
class LM92
{
public:
    void Enable();
    int32_t ReadTempC();
    int32_t ReadTempF();
    
    static LM92 *GetInstance();
    
private:
    int32_t ReadRaw();

};

/** @} */

#endif // #ifndef LM92_H
