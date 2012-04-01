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
 * Filename:     LM92.cpp                                                  *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

/// Reserve memory for the singleton object.
static LM92 lm92SingletonObject;

/**
 * Get a pointer to the LM92 object.
 */
LM92 *LM92::GetInstance()
{
    return  &lm92SingletonObject;
}

/**
 * Configure the temperature sensor for operation.
 */
void LM92::Enable()
{
    
}

/**
 * Read the raw LM92 sensor value.
 * 
 * @return raw measurement value
 */
int32_t LM92::ReadRaw()
{
    uint8_t data[10];
    
    if (!I2C0::GetInstance()->Start(0x91))
        return -999;
    
    I2C0::GetInstance()->Read(data, 2);
    I2C0::GetInstance()->Stop();

    // Convert from 8-bit binary data to a 32-bit 2's compliment number.
    return ((int8_t) (data[0]) << 8) | data[1];
}

/**
 *   Read the current temperature in degrees F.
 *
 *   @return temperature in units of 0.1 degrees F
 */
int32_t LM92::ReadTempC()
{
    int32_t value;

    if ((value = ReadRaw()) == -999)
        return -999;
    
    // Convert from degC to degF.
    // See the LM72_92.xls Spreadsheet in the .../unit_test directory for additional information.    
    return ((5 * value) / 64);
}

/**
 *   Read the current temperature in degrees F.
 *
 *   @return temperature in units of 0.1 degrees F
 */
int32_t LM92::ReadTempF()
{
    int32_t value;

    if ((value = ReadRaw()) == -999)
        return -999;
    
    // Convert from raw units to degrees F.  
    // See the LM72_92.xls Spreadsheet in the .../unit_test directory for additional information.
    return ((9 * value) / 64) + 320;
}
