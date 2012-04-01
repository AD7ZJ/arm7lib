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
 * Filename:     RTCTime.h                                                 *
 *                                                                         *
 ***************************************************************************/

#ifndef RTCTIME_H
#define RTCTIME_H

/**
 *  @defgroup library Generic Library Functions
 *
 *  @{
 */

/**
*   Object that contains a generic indication of time.
*/
class RTCTime
{
public:
    RTCTime();
    RTCTime(uint32_t timeSinceEpoch);
    RTCTime(uint32_t gpsWeekNumber, uint32_t gpsTimeOfWeek, uint32_t utcOffset);
    
    /// UTC time in hours in the range 0 to 23.
    uint8_t hours;

    /// UTC time in minutes in the range 0 to 59.
    uint8_t minutes;

    /// UTC time in seconds in the range 0 to 59.
    uint16_t seconds;
    
    /// UTC date in month in the range 1 to 12.
    uint8_t month;
    
    /// UTC date in day of month in the range 1 to 31.
    uint8_t day;
    
    /// UTC date in years.
    uint16_t year; 
    
    /// UTC day of week in the range 0 to 6 where 0 is Sunday, 1 is Monday, 2 is Tuesday, ... , 6 is Saturday
    uint8_t dayOfWeek;
    
private:
    /// Number of seconds per week.  60 seconds/minute * 60 minutes/hour * 24 hours/day * 7 days/week.
    static const uint32_t SecondsPerWeek = 604800;
    
    /// Number of seconds between time_t epoch (1 Jan 1970) and GPS epoch (6 Jan 1980).  10 years and 7 days = 3657 day * 24 hours * 60 minutes * 60 seconds
    static const uint32_t EpochTimeDifference = 315964800;
};

/** @} */

#endif // #ifndef RTCTIME_H
