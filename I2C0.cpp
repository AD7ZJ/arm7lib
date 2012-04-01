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
 * Filename:     I2C0.cpp                                                  *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

/// Reserve memory for singleton object.
static I2C0 i2c0SingletonObject;

/**
 *  Get a pointer to the I2C port 0 object.
 */
I2C0 *I2C0::GetInstance()
{
    return 	&i2c0SingletonObject;
}

/**
 *  Enable the required pins for the I2C port and configure it for operation.
 */
void I2C0::Enable()
{
    uint32_t clock;

    // Set the pins required for the I2C controller.
    PINSEL0 |= ((0x01 << 4) | (0x01 << 6));

    I2C0CONCLR = I2CxCONCLR_AA | I2CxCONCLR_SI | I2CxCONCLR_STAC | I2CxCONCLR_I2ENC;

    // Set the I2C clock rate to 250KHz.
    clock = SystemControl::GetInstance()->GetPClock() / 500000;
    I2C0SCLH = clock;
    I2C0SCLL = clock;

    // Enable the I2C engine.
    I2C0CONSET = I2CxCONSET_I2EN;
}

/**
 * Send the start command sequence and slave address.
 *
 * @param data slave address
 *
 * @return true if slave ACKed request; otherwise false
 */
bool_t I2C0::Start(uint32_t data)
{
    uint32_t value, retryCount;

    retryCount = 0;

    for (;;)
    {
        // Clear the interrupt status.
        I2C0CONCLR = I2CxCONCLR_SI;

        // Send the start command.
        I2C0CONSET = I2CxCONSET_STA;

        if (WaitInterrupt())
            return false;

        // Write the slave address.
        I2C0DAT = data;

        // Clear the start flag and interrupt.
        I2C0CONCLR = I2CxCONSET_STA | I2CxCONCLR_SI;

        // Wait for the interrupt.
        if (WaitInterrupt())
            return false;

        value = I2C0STAT;

        // Check the start status.
        if (value != ((data & 0x01) ? 0x40 : 0x18))
        {
            Stop();

            if (++retryCount == 5)
                return false;
        } else
            return true;
    } // END for
}

/**
 * Read a one or more bytes from the slave device.
 *
 * @param data pointer to buffer to hold count bytes of data
 * @param count number of bytes to read
 */
void I2C0::Read (uint8_t *data, uint32_t count)
{
    I2C0CONCLR = I2CxCONCLR_SI;
    I2C0CONSET = I2CxCONSET_AA;

    if (count == 1)
    {
        I2C0CONCLR = I2CxCONCLR_AA | I2CxCONCLR_SI;

        if (WaitInterrupt())
            return;

        *data = I2C0DAT;
        return;
    } // END if

    for(;;)
    {
        // Wait for end data from slave.
        if (WaitInterrupt())
            return;

        *data++ = I2C0DAT;
        count--;

        switch (count)
        {
            case 0x00:
                return;

            // After next will NO ASK
            case 0x01:
                I2C0CONCLR = I2CxCONCLR_AA | I2CxCONCLR_SI;
                break;

            default:
                I2C0CONCLR = I2CxCONCLR_SI;
                I2C0CONSET = I2CxCONSET_AA;
                break;
        } // END switch
    } // END for
}

/**
 * Write one or more bytes to the slave device.
 *
 * @param data pointer to buffer of data to write
 * @param count number of bytes to send
 */
void I2C0::Write (const uint8_t *data, uint32_t count)
{
    while (count != 0)
    {
        I2C0DAT = *data++;

        I2C0CONCLR = I2CxCONCLR_SI;

        if (WaitInterrupt())
            return;

        --count;
    } // END while
}

/**
 * Send the STOP signal to the slave device.
 */
void I2C0::Stop()
{
    I2C0CONSET =  I2CxCONSET_STO;
    I2C0CONCLR = I2CxCONCLR_SI;
}

/**
 * Wait for the interrupt flag to get set or the time out period to expire.
 *
 * @return true if interrupt not detected and wait timed out; otherwise false
 */
bool_t I2C0::WaitInterrupt()
{
    uint32_t startTime;

    startTime = SystemControl::GetTick() + 50;

    while (!(I2C0CONSET & I2CxCONSET_SI))
        if (SystemControl::GetTick() > startTime)
        {
            Stop();
            return true;
        } // END if

    return false;
}
