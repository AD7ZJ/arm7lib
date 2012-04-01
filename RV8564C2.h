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
 * Filename:     RV8564C2.h                                                *
 *                                                                         *
 ***************************************************************************/

#ifndef RV8564C2_H
#define RV8564C2_H

/**
 *  @defgroup external External Peripherals
 *
 *  @{
 */

/**
 *  Control the Micro Crystal Real Time Clock.  The RV-8564-C2 is a CMOS
 *  real-time clock/calendar optimized for low power consumption.
 */
class RV8564C2 : public RTCBase
{
public:
    const RTCTime *GetTime();
    bool_t IsAlarm();
    bool_t IsLowPower();
    void EnableAlarm(const RTCTime *alarm);
    void SetTime(const RTCTime *time);
    void SetTime(const GPSData *gps);

    static RV8564C2 *GetInstance();

private:
    /// Control register - Stop bit.
    static const uint32_t CONTROL1_STOP = (1 << 5);

    /// Control register -
    static const uint32_t CONTROL2_AIE = (1 << 1);

    /// Control register -
    static const uint32_t CONTROL2_AF = (1 << 3);

    /// Alarm register -
    static const uint32_t ALARM_AD = (1 << 7);
};

/** @} */

#endif // #ifndef RV8564C2_H
