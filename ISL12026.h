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
 * Filename:     ISL12026.h                                                *
 *                                                                         *
 ***************************************************************************/

#ifndef ISL12026_H
#define ISL12026_H

/**
 *  @defgroup external External Peripherals
 *
 *  @{
 */

/**
 * Control the Intersil Real Time Clock.  The ISL12026 device is a micro
 * power real time clock with timing and crystal compensation, clock/calendar,
 * power-fail indicator, two periodic or polled alarms, intelligent battery
 * backup switching, and integrated 512 x 8-bit EEPROM configured in
 * 16 Byte per page.
 */
class ISL12026 : public RTCBase
{
public:
    const RTCTime *GetTime();
    bool_t IsAlarm();
    bool_t IsLowPower();
    void DisableAlarm();
    void EnableAlarm(const RTCTime *alarm);
    void SetTime(const RTCTime *time);
    void SetTime(const GPSData *gps);

    static ISL12026 *GetInstance();

private:
    /// Slave address to read the CCR (Clock/Control Registers).
    static const uint32_t ReadCCR = 0xdf;

    /// Slave address to write the CCR (Clock/Control Registers).
    static const uint32_t WriteCCR = 0xde;

    /// Slave address to read the EEPROM array.
    static const uint32_t ReadArray = 0xaf;

    /// Slave address to write the EEPROM array.
    static const uint32_t WriteArray = 0xae;


    /// Control register address.
    static const uint32_t ControlRegister = 0x11;

    /// Control Register - Alarm 1 bit.
    static const uint32_t ControlRegisterAlarm1 = (1 << 5);

    /// Control Register - Alarm 2 bit.
    static const uint32_t ControlRegisterAlarm2 = (1 << 6);

    /// Control Register - Interrupt Mode bit.
    static const uint32_t ControlRegisterInterruptMode = (1 << 7);


    /// Status register address.
    static const uint32_t StatusRegister = 0x3f;

    /// Status Register - RTCF (Real Time Clock Fail) bit.
    static const uint32_t StatusRegisterRTCF = (1 << 0);

    /// Status Register - WEL (Write Enable Latch) bit.
    static const uint32_t StatusRegisterWEL = (1 << 1);

    /// Status Register - RWEL (Register Write Enable Latch) bit.
    static const uint32_t StatusRegisterRWEL = (1 << 2);

    /// Status Register - Alarm 1 bit.
    static const uint32_t StatusRegisterAlarm1 = (1 << 5);

    /// Status Register - Alarm 2 bit.
    static const uint32_t StatusRegisterAlarm2 = (1 << 6);

    void DumpRegisters();
    uint32_t GetStatus();
    void WriteDisable();
    void WriteEnable();
};

/** @} */

#endif // #ifndef ISL12026_H
