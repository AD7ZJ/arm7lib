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
 * Filename:     ISL12026.cpp                                              *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

/// Reserve memory for the singleton object.
static ISL12026 isl12026SingletonObject;

/**
 * Pointer to the ISL12026 Real Time Clock object.
 */
ISL12026 *ISL12026::GetInstance()
{
    return  &isl12026SingletonObject;
}

/**
 *  Read the current real time clock value.
 *
 *  @return pointer to the RTCTime object that contains the time
 */
const RTCTime *ISL12026::GetTime()
{
    uint8_t data[8];

    I2C0::GetInstance()->Start(WriteCCR);

    // Set the address pointer to 0x30 to start the RTC (SRAM) locations.
    data[0] = 0x00;
    data[1] = 0x30;
    I2C0::GetInstance()->Write(data, 2);

    // Restart and read 8 byte from the device.
    I2C0::GetInstance()->Start(ReadCCR);
    I2C0::GetInstance()->Read(data, 8);
    I2C0::GetInstance()->Stop();

    // Populate the time structure.
    this->time.seconds = ConvertBCDToDecimal(data[0] & 0x7f);
    this->time.minutes = ConvertBCDToDecimal(data[1] & 0x7f);
    this->time.hours = ConvertBCDToDecimal(data[2] & 0x3f);

    this->time.day = ConvertBCDToDecimal(data[3] & 0x3f);
    this->time.month = ConvertBCDToDecimal(data[4] & 0x1f);
    this->time.year = 100 * ConvertBCDToDecimal(data[7]) + ConvertBCDToDecimal(data[5]);

    return &this->time;
}

/**
 * Set the RTC time to UTC using the GPS fix data.
 *
 * @param gps pointer to GPSData object
 */
void ISL12026::SetTime(const GPSData *gps)
{
    RTCTime rtc;

    // Ignore the request if we don't have a valid fix.
    if (gps->fixType == GPSData::NoFix)
        return;

    rtc.seconds = gps->seconds;
    rtc.minutes = gps->minutes;
    rtc.hours = gps->hours;

    rtc.month = gps->month;
    rtc.day = gps->day;
    rtc.year = gps->year;

    SetTime (&rtc);
}

/**
 * Set the RTC time to the RTCTime object value.
 *
 * @param time pointer to desired time.
 */
void ISL12026::SetTime(const RTCTime *time)
{
    uint8_t data[10];

    WriteEnable();

    // Set the time register values.
    I2C0::GetInstance()->Start(WriteCCR);

    data[0] = 0x00;
    data[1] = 0x30;

    // Seconds.
    data[2] = ConvertDecimalToBCD(time->seconds);

    // Minutes.
    data[3] = ConvertDecimalToBCD(time->minutes);

    // Hours.
    data[4] = 0x80 | ConvertDecimalToBCD(time->hours);

    // Days.
    data[5] = ConvertDecimalToBCD(time->day);

    // Month.
    data[6] = ConvertDecimalToBCD(time->month);

    // Tens/ones of years.
    data[7] = ConvertDecimalToBCD(time->year % 100);

    // Day of week.
    data[8] = 0x00;

    // Thousands/hundreds of years.
    data[9] = ConvertDecimalToBCD(time->year / 100);

    I2C0::GetInstance()->Write(data, 10);
    I2C0::GetInstance()->Stop();

    WriteDisable();
}

/**
 * Set the time of the alarm in HH:MM:SS.
 *
 * @param alarm pointer to RTCTime object that contains the alarm time
 */
void ISL12026::EnableAlarm(const RTCTime *alarm)
{
    uint8_t data[20];

    // Set the time register values.
    WriteEnable();

    I2C0::GetInstance()->Start(WriteCCR);

    data[0] = 0x00;
    data[1] = 0x00;

    // Seconds.
    data[2] = 0x80 | ConvertDecimalToBCD(alarm->seconds);

    // Minutes.
    data[3] =  0x80 | ConvertDecimalToBCD(alarm->minutes);

    // Hours.
    data[4] = 0x80 | ConvertDecimalToBCD(alarm->hours);

    data[5] = 0x00;
    data[6] = 0x00;
    data[7] = 0x00;
    data[8] = 0x00;
    data[9] = 0x00;
    data[10] = 0x00;

    I2C0::GetInstance()->Write(data, 5);
    I2C0::GetInstance()->Stop();

    WriteDisable();


    // Set the alarm and interrupt enable bits.
    WriteEnable();

    I2C0::GetInstance()->Start(WriteCCR);

    data[0] = 0x00;
    data[1] = ControlRegister;
    data[2] = ControlRegisterAlarm1 | ControlRegisterInterruptMode;

    I2C0::GetInstance()->Write(data, 3);
    I2C0::GetInstance()->Stop();

    WriteDisable();
}

/**
 * Disable the alarm.
 */
void ISL12026::DisableAlarm()
{
    uint8_t data[4];

    // Set the alarm enable bit.
    WriteEnable();

    I2C0::GetInstance()->Start(WriteCCR);

    data[0] = 0x00;
    data[1] = ControlRegister;
    data[2] = 0x00;

    I2C0::GetInstance()->Write(data, 3);
    I2C0::GetInstance()->Stop();

    WriteDisable();
}

/**
 * One-shot that determines if an alarm event has occurred.
 *
 * @return true if alarm as occurred; otherwise false
 */
bool_t ISL12026::IsAlarm()
{
    if ((GetStatus() & StatusRegisterAlarm1) == StatusRegisterAlarm1)
        return true;

    return false;
}

/**
 * Determine if low power has been detected and the time needs to be set/reset.
 *
 * @return true if low power; otherwise false
 */
bool_t ISL12026::IsLowPower()
{
    RTCTime time;
    uint32_t status;

    // Read the status twice since we sometimes get junk on the first read after power on.
    status = GetStatus();
    status = GetStatus();

    if ((status & StatusRegisterRTCF) != StatusRegisterRTCF)
        return false;

    // Set the clock to GPS epoch time.
    time.hours = 0;
    time.minutes = 0;
    time.seconds = 0;

    time.month = 1;
    time.day = 6;
    time.year = 1980;

    SetTime(&time);

    return true;
}

/**
 * Get the status register (0x3f) value.
 *
 * @return status register contents
 */
uint32_t ISL12026::GetStatus()
{
    uint8_t data[4];

    // Set the address pointer to 0x3f.
    I2C0::GetInstance()->Start(WriteCCR);

    data[0] = 0x00;
    data[1] = StatusRegister;

    I2C0::GetInstance()->Write(data, 2);

    // Restart and read 1 byte from the device.
    I2C0::GetInstance()->Start(ReadCCR);
    I2C0::GetInstance()->Read(data, 1);
    I2C0::GetInstance()->Stop();

    return data[0];
}

/**
 * Clear the RWEL and WEL status register bits.
 */
void ISL12026::WriteDisable()
{
    uint8_t data[4];

    // Clear the status register.
    I2C0::GetInstance()->Start(WriteCCR);

    data[0] = 0x00;
    data[1] = StatusRegister;
    data[2] = 0x00;
    I2C0::GetInstance()->Write(data, 3);

    I2C0::GetInstance()->Stop();
}

/**
 * Set the RWEL and WEL status register bits to allow for CCR write operations.
 */
void ISL12026::WriteEnable()
{
    uint8_t data[4];

    // Set the WEL bit in the status register.
    I2C0::GetInstance()->Start(WriteCCR);

    data[0] = 0x00;
    data[1] = StatusRegister;
    data[2] = StatusRegisterWEL;
    I2C0::GetInstance()->Write(data, 3);

    I2C0::GetInstance()->Stop();


    // Set the WEL and RWEL bits in the status register.
    I2C0::GetInstance()->Start(WriteCCR);

    data[0] = 0x00;
    data[1] = StatusRegister;
    data[2] = StatusRegisterWEL | StatusRegisterRWEL;
    I2C0::GetInstance()->Write(data, 3);

    I2C0::GetInstance()->Stop();
}

/**
 * Integration and test method used to display control register contents through UART0.
 */
void ISL12026::DumpRegisters()
{
    uint8_t data[8];

    I2C0::GetInstance()->Start(WriteCCR);

    // Set the address pointer to 0x10.
    data[0] = 0x00;
    data[1] = 0x10;
    I2C0::GetInstance()->Write(data, 2);

    // Restart and read 1 byte from the device.
    I2C0::GetInstance()->Start(ReadCCR);
    I2C0::GetInstance()->Read(data, 5);
    I2C0::GetInstance()->Stop();

    for (int i = 0; i < 5; ++i)
        UART0::GetInstance()->WriteLine("0x%lx = 0x%x", i + 0x10, data[i]);
}
