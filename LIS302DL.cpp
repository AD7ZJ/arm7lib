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
 * Filename:     LIS302DL.cpp                                              *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

/// Reserve memory for the singleton object.
static LIS302DL lis302dlSingletonObject;

/**
 * Get a pointer to the base class of the UART-1 instance.
 */
LIS302DL *LIS302DL::GetInstance()
{
    return &lis302dlSingletonObject;
}

/**
 * Constructor.
 */
LIS302DL::LIS302DL()
{
    memset (&this->axes, 0x00, sizeof(this->axes));
    this->address = SDOLow;
}

/**
 * Enable the LIS302DL sensor.
 *
 * @param address specifies the hardware address
 * @param range defines the G force range of the sensor
 */
void LIS302DL::Enable(Address address, MeasurementRange range)
{
    uint8_t data[2];

    // Save the I2C bus address for the device.
    this->address = static_cast <uint32_t> (address);

    // Control register 1.
    data[0] = 0x20;

    // Set the device to the active state with all 3 axes and the desired range.
    data[1] = 0x47 | static_cast <uint8_t> (range);

    I2C0::GetInstance()->Start(this->address);
    I2C0::GetInstance()->Write(data, 2);
    I2C0::GetInstance()->Stop();
}

/**
 * Place the MEMS sensor in power down mode for lowest current draw.
 */
void LIS302DL::PowerDown()
{
    uint8_t data[2];

    // Control register 1.
    data[0] = 0x20;

    // Clear the power down control bit to enter the power down state.
    data[1] = 0x00;

    I2C0::GetInstance()->Start(this->address);
    I2C0::GetInstance()->Write(data, 2);
    I2C0::GetInstance()->Stop();
}

/**
 * Read the Device ID value.
 *
 * @return device ID
 */
uint32_t LIS302DL::ReadID()
{
    uint8_t data[1];

    I2C0::GetInstance()->Start(this->address);

    data[0] = 0x0f;
    I2C0::GetInstance()->Write(data, 1);

    I2C0::GetInstance()->Start(this->address | 0x01);
    I2C0::GetInstance()->Read(data, 1);
    I2C0::GetInstance()->Stop();

    return data[0];
}

/**
 * Set the source and parameters that will generate an interrupt signal based on the current state of the MEMs.
 *
 * @param intSource
 * @param intEnable
 * @param threshold
 * @param timePeriod
 */
void LIS302DL::SetInterrupt(InterruptSource intSource, InterruptEnable intEnable, uint32_t threshold, uint32_t timePeriod)
{


}

/**
 * Read and return the current X, Y, and Z axis sensor values.
 *
 * @return pointer to LIS302DLData structure
 */
LIS302DL::LIS302DLData *LIS302DL::Read()
{
    uint8_t data[6];

    I2C0::GetInstance()->Start(this->address);

    // Set the auto increment mode to start at register 0x29.  0xa9 = 0x80 | 0x29
    data[0] = 0xa9;
    I2C0::GetInstance()->Write(data, 1);

    I2C0::GetInstance()->Start(this->address | 0x01);
    I2C0::GetInstance()->Read(data, 5);
    I2C0::GetInstance()->Stop();

    // Sign extend to 32-bit integers.
    this->axes.x = (int8_t) data[0];
    this->axes.y = (int8_t) data[2];
    this->axes.z = (int8_t) data[4];

    return &this->axes;
}
