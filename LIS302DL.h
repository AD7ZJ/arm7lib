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
 * Filename:     LIS302DL.h                                                *
 *                                                                         *
 ***************************************************************************/

#ifndef LIS302DL_H
#define LIS302DL_H

/**
 *  @defgroup external External Peripherals
 *
 *  @{
 */

/**
 *  Control the ST Microelectronics LIS302DL MEMS motion sensor.
 *  The LIS302DL is an ultra compact low-power three axes linear
 *  accelerometer.  It includes a sensing element and an IC interface
 *  able to provide the measured acceleration to the external
 *  world through I2C/SPI serial interface.
 */
class LIS302DL
{
public:
    /// Structure that contains the current X, Y, and Z axes sensor values.
    typedef struct
    {
        /// X-Axis value.
        int32_t x;

        /// Y-Axis value.
        int32_t y;

        /// Z-Axis value.
        int32_t z;
    } LIS302DLData;

    /// Specifies the I2C address of the LIS302DL.
    typedef enum
    {
        /// Specifies the SDO pad is connected to the voltage supply
        SDOHigh = 0x3a,

        /// Specifies the SDO pad is connected to ground.
        SDOLow = 0x38
    } Address;

    /// Specifies the interrupt source that is configured.
    typedef enum
    {
        /// Interrupt Source 1.
        Int1,

        /// Interrupt Source 2.
        Int2
    } InterruptSource;

    /// Specifies the axis and high/low setting that enables the interrupt.
    typedef enum
    {
        ///
        ZHigh = 0x20,

        ZLow = 0x10
    } InterruptEnable;

    /// Specifies the sensor measurement range of +/- 2Gs or +/- 8Gs.
    typedef enum
    {
        /// Low range +/- 2Gs.
        LowRange = 0x00,

        /// High range +/- 8Gs.
        HighRange = 0x20
    } MeasurementRange;

    LIS302DL();

    void Enable(Address address, MeasurementRange range = LowRange);
    void PowerDown();
    LIS302DLData *Read();
    uint32_t ReadID();
    void SetInterrupt(InterruptSource intSource, InterruptEnable intEnable, uint32_t threshold, uint32_t timePeriod);

    static LIS302DL *GetInstance();

private:
    /// Contains the latest X, Y, and Z axes sensor values.
    LIS302DLData axes;

    /// I2C address of the LIS302DL.
    uint32_t address;
};

/** @} */

#endif // #ifndef LIS302DL_H
