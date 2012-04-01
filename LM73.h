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
 * Filename:     LM73.h                                                    *
 *                                                                         *
 ***************************************************************************/

#ifndef LM73_H
#define LM73_H

/**
 *  @defgroup external External Peripherals
 *
 *  @{
 */

/**
 *  Control the National Semiconductor Temperature Sensor.
 *  The LM73 is an integrated, digital-output temperature sensor
 *  featuring an incremental Delta-Sigma ADC with a two-wire
 *  interface that is compatible with the SMBus and I2C interfaces.
 */
class LM73
{
public:
    /// Specifies the hardware addressing of the LM73.
    typedef enum
    {
        /// Specifies the LM73 with the T730 package and the address pin floating.
        T730_FLOAT = 0x90,

        /// Specifies the LM73 with the T730 package and the address pin low.
        T730_GROUND = 0x92,

        /// Specifies the LM73 with the T730 package and the address pin high.
        T730_VDD = 0x94,

        /// Specifies the LM73 with the T731 package and the address pin floating.
        T731_FLOAT = 0x98,

        /// Specifies the LM73 with the T731 package and the address pin low.
        T731_GROUND = 0x9a,

        /// Specifies the LM73 with the T730 package and the address pin high.
        T731_VDD = 0x9c        
    } LM73Address;
    
    void Enable(LM73Address address);
    int32_t ReadTempC();
    int32_t ReadTempF();
    
    static LM73 *GetInstance();
    
private:
    int32_t ReadRaw();
    
    /// I2C address of the LM73.
    uint32_t address;
};

/** @} */

#endif // #ifndef LM73_H
