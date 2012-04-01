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
 * Filename:     RV8564C2.cpp                                              *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

/// Reserve memory for the singleton object.
static RV8564C2 rv8564c2SingletonObject;

/**
 * Pointer to the RV8564C2 Real Time Clock object.
 */
RV8564C2 *RV8564C2::GetInstance()
{
    return  &rv8564c2SingletonObject;
}

/**
 * Read the current real time clock value.
 *
 * @return pointer to the RTCTime object that contains the time
 */
const RTCTime *RV8564C2::GetTime()
{
    uint8_t data[10];

    I2C0::GetInstance()->Start(0xa2);

    // Set the address pointer to start at 02 - Seconds.
    data[0] = 0x02;
    I2C0::GetInstance()->Write(data, 1);

    // Restart and read 7 bytes from the device.
    I2C0::GetInstance()->Start(0xa3);

    I2C0::GetInstance()->Read(data, 7);

    I2C0::GetInstance()->Stop();

    // Populate the time structure.
    this->time.seconds = ConvertBCDToDecimal(data[0] & 0x7f);
    this->time.minutes = ConvertBCDToDecimal(data[1] & 0x7f);
    this->time.hours = ConvertBCDToDecimal(data[2] & 0x3f);

    this->time.day = ConvertBCDToDecimal(data[3] & 0x3f);
    this->time.month = ConvertBCDToDecimal(data[5] & 0x1f);
    this->time.year = 2000 + ConvertBCDToDecimal(data[6]);

    return &this->time;
}

/**
 * Set the RTC time to UTC using the GPS fix data.
 *
 * @param gps pointer to GPSData object
 */
void RV8564C2::SetTime(const GPSData *gps)
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
 * Set the RTC hardware.  Setting the time will also clear the low power indicator bit.
 * Check the low power bit BEFORE setting the time.
 *
 * @param rtc pointer to RTCTime object
 */
void RV8564C2::SetTime(const RTCTime *rtc)
{
    uint8_t data[10];

    I2C0::GetInstance()->Start(0xa2);

    // Set the address pointer to start at 00 - Control / Status 1.
    data[0] = 0x00;

    // Control / Status 1 byte.  Set the STOP bit so we clear the pre-scalar and stop the clock during the update.
    data[1] = CONTROL1_STOP;

    // Control / Status 2 byte.
    data[2] = 0x00;

    // Seconds.
    data[3] = ConvertDecimalToBCD(rtc->seconds);

    // Minutes.
    data[4] = ConvertDecimalToBCD(rtc->minutes);

    // Hours.
    data[5] = ConvertDecimalToBCD(rtc->hours);

    // Days.
    data[6] = ConvertDecimalToBCD(rtc->day);

    // Weekdays.
    data[7] = 0x00;

    // Month / Century.
    data[8] = ConvertDecimalToBCD(rtc->month);

    // Years.
    data[9] = ConvertDecimalToBCD(rtc->year - 2000);

    I2C0::GetInstance()->Write(data, 10);

    I2C0::GetInstance()->Stop();

    // Clear the STOP bit so the clock will now run.
    I2C0::GetInstance()->Start(0xa2);

    // Set the address pointer to start at 00 - Control / Status 1.
    data[0] = 0x00;
    data[1] = 0x00;

    I2C0::GetInstance()->Write(data, 2);

    I2C0::GetInstance()->Stop();
}

/**
 * Set the time of the alarm in Hours/Minutes.  The alarm time is cleared
 * if the system time is updated.
 *
 * @param alarm pointer to RTCTime object that contains the alarm time
 */
void RV8564C2::EnableAlarm(const RTCTime *alarm)
{
    uint8_t data[5];

    I2C0::GetInstance()->Start(0xa2);

    // Set the address pointer to start at 09 - Minute Alarm.
    data[0] = 0x09;

    // Minute Alarm.
    data[1] = ConvertDecimalToBCD(alarm->minutes);

    // Hour Alarm.
    data[2] = ConvertDecimalToBCD(alarm->hours);

    // Day Alarm set to ignore state.
    data[3] = ALARM_AD;

    // Weekday Alarm set to ignore state.
    data[4] = ALARM_AD;

    I2C0::GetInstance()->Write(data, 5);

    I2C0::GetInstance()->Stop();

    // Enable the alarm clock function.
    I2C0::GetInstance()->Start(0xa2);

    // Set the address pointer to start at 01 - Control / Status 2.
    data[0] = 0x01;
    data[1] = CONTROL2_AIE;

    I2C0::GetInstance()->Write(data, 2);

    I2C0::GetInstance()->Stop();
}

/**
 * One-shot that determines if an alarm event has occurred.
 *
 * @return true if alarm as occurred; otherwise false
 */
bool_t RV8564C2::IsAlarm()
{
    uint8_t data[2];
    uint32_t status;

    I2C0::GetInstance()->Start(0xa2);

    // Set the address pointer to start at 01 - Control / Status 2.
    data[0] = 0x01;
    I2C0::GetInstance()->Write(data, 1);

    // Restart and read 1 byte from the device.
    I2C0::GetInstance()->Start(0xa3);
    I2C0::GetInstance()->Read(data, 1);
    I2C0::GetInstance()->Stop();

    status = data[0];

    if ((status & CONTROL2_AF) == 0x00)
        return false;

    // Clear the alarm flag if it has occurred.
    I2C0::GetInstance()->Start(0xa2);

    // Set the address pointer to start at 01 - Control / Status 2.
    data[0] = 0x01;

    // Clear the AF flag.
    data[1] = status & ~CONTROL2_AF;
    I2C0::GetInstance()->Write(data, 2);
    I2C0::GetInstance()->Stop();

    return true;
}

/**
 * Determine if low power has been detected and the time needs to be set/reset.
 *
 * @return true if low power; otherwise false
 */
bool_t RV8564C2::IsLowPower()
{
    RTCTime time;
    uint8_t data[2];
    uint32_t seconds;

    I2C0::GetInstance()->Start(0xa2);

    // Set the address pointer to start at 02 - Seconds.
    data[0] = 0x02;
    I2C0::GetInstance()->Write(data, 1);

    // Restart and read 1 byte from the device.
    I2C0::GetInstance()->Start(0xa3);
    I2C0::GetInstance()->Read(data, 1);
    I2C0::GetInstance()->Stop();

    seconds = data[0];

    if ((seconds & 0x80) == 0x00)
        return false;

    // Set the clock to 0000 UTC on 1 Jan 2008.
    time.hours = 0;
    time.minutes = 0;
    time.seconds = 0;

    time.month = 1;
    time.day = 1;
    time.year = 2008;

    SetTime(&time);

    return true;
}
