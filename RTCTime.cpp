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
 * Filename:     RTCTime.cpp                                               *
 *                                                                         *
 ***************************************************************************/
 
#include "armlib.h"

/**
 * Create the object with 00:00:00 00/00/0000 time.
 */
RTCTime::RTCTime()
{
    memset (this, 0x00, sizeof(this));
}

/**
 * Create the object using GPS Epoch time in seconds since 6 Jan 1980 at 0000 UTC.
 * 
 * @param timeSinceEpoch time in seconds
 */
RTCTime::RTCTime(uint32_t timeSinceEpoch)
{
    // Time base difference between time_t epoch (1 Jan 1970) and GPS epoch (6 Jan 1980).
    timeSinceEpoch += EpochTimeDifference;
    
    // Convert to GMT time.
    struct tm *gmtTime = gmtime (reinterpret_cast<const time_t *> (&timeSinceEpoch));
    
    this->hours = gmtTime->tm_hour;
    this->minutes = gmtTime->tm_min;
    this->seconds = gmtTime->tm_sec;
    
    this->month = gmtTime->tm_mon + 1;
    this->day = gmtTime->tm_mday;
    this->year = gmtTime->tm_year + 1900;
    
    this->dayOfWeek = gmtTime->tm_wday;
}

/**
 * Create the object using GPS Week Number, Time Of Week, and UTC offset all in units of seconds.
 * 
 * @param gpsWeekNumber GPS Week Number
 * @param gpsTimeOfWeek GPS Time Of Week in seconds
 * @param utcOffset Difference in seconds between UTC and GPS time
 */
RTCTime::RTCTime(uint32_t gpsWeekNumber, uint32_t gpsTimeOfWeek, uint32_t utcOffset)
{
    // Time base difference between time_t epoch (1 Jan 1970) and GPS epoch (6 Jan 1980).
    gpsTimeOfWeek += EpochTimeDifference;
    
    // Add GPS Week Number offset.
    gpsTimeOfWeek += (gpsWeekNumber * SecondsPerWeek);
    
    // Offset between GPS and UTC time base.
    gpsTimeOfWeek -= utcOffset;
    
    // Convert to GMT time.
    struct tm *gmtTime = gmtime (reinterpret_cast<const time_t *> (&gpsTimeOfWeek));
    
    this->hours = gmtTime->tm_hour;
    this->minutes = gmtTime->tm_min;
    this->seconds = gmtTime->tm_sec;
    
    this->month = gmtTime->tm_mon + 1;
    this->day = gmtTime->tm_mday;
    this->year = gmtTime->tm_year + 1900;
    
    this->dayOfWeek = gmtTime->tm_wday;    
}
