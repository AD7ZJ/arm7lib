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
 * Filename:     RTC.cpp                                                   *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

/// Reserve memory for singleton object.
static RTC rtcSingletonObject;

/**
 * Get a pointer to the RTC singleton object.
 */
RTC *RTC::GetInstance()
{
    return &rtcSingletonObject;
}

/**
 *  Enable the RTC for operation.
 */
void RTC::Enable()
{
    // Enable the RTC and set the 32KHz clock as the source.
    CCR = (CCR_CLKEN | CCR_CLKSRC_32KHZ);
}

/**
 *   Read the current real time clock value.
 *
 *   @return pointer to the RTCTime object that contains the time
 */
RTCTime *RTC::Get()
{
    // Get the RTC time.
    this->time.seconds = SECONDS;       
    this->time.minutes = MINUTES;       
    this->time.hours = HOURS;    

    this->time.day = DOM;    
    this->time.month = MONTH;    
    this->time.year = YEAR;    

    return &this->time;
}

/**
 * Set the RTC time to UTC using the GPS fix data.
 * 
 * @param gps pointer to GPSData object
 */
void RTC::Set (const GPSData *gps)
{
    // Ignore the request if we don't have a valid fix.
    if (gps->fixType == GPSData::NoFix)
        return;
    
    // Stop the clock during the update and reset the 32KHz divider.
    CCR |= CCR_CTCRST;	
    
    SECONDS = gps->seconds;
    MINUTES = gps->minutes;
    HOURS = gps->hours;

    DOM = gps->day;
    MONTH = gps->month;
    YEAR = gps->year;
    
    // Restart the clock.
    CCR &= ~CCR_CTCRST;
}
