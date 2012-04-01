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
 * Filename:     GPSData.cpp                                               *
 *                                                                         *
 ***************************************************************************/
 
#include "armlib.h"

/**
 *  Constructor.
 */
GPSData::GPSData()
{
    memset (this, 0x0000, sizeof(GPSData));
}

/**
 *  Store the receive channel status.
 *  
 *  @param channel Receive channel number in the range 0 to RECEIVE_CHANNEL_COUNT - 1
 *  @param prn satellite PRN
 *  @param state receive channel status bit map
 *  @param cNo C/No in units of 0.1 dB/Hz
 */
void GPSData::RxChannel (uint32_t channel, uint32_t prn, uint32_t state, uint32_t cNo)
{
    if (channel >= RECEIVE_CHANNEL_COUNT)
        return;

    this->rxChannel[channel] = ((prn & 0x00ff) << 24) | ((state & 0x00ff) << 16) | (cNo & 0xffff);
}

/**
 *  Get the C/No in units of 0.1 dB/Hz for the desired receive channel.
 *
 *  @param channel Receive channel number in the range 0 to RECEIVE_CHANNEL_COUNT - 1
 *
 *  @return C/No in units of 0.1 dB/Hz
 */
uint32_t GPSData::CNo (uint32_t channel) const
{
    return this->rxChannel[channel] & 0xffff;
}

/**
 *  Calculate the C/No in units of 0.1 dB/Hz for the receive channels that are part of the fix solution.
 *
 *  @return C/No in units of 0.1 dB/Hz
 */
uint32_t GPSData::AverageCNo() const
{
    uint32_t i, count, sum;
    
    count = 0;
    sum = 0;
    
    for (i = 0; i < RECEIVE_CHANNEL_COUNT; ++i)
        if (State(i) == 0xbf)
        {
            sum += CNo(i);
            ++count;
        }
    
    if (count == 0)
        return 0;
    
    return sum / count;    
}

/**
 *  Get the SVID the desired receive channel.
 *
 *  @param channel Receive channel number in the range 0 to RECEIVE_CHANNEL_COUNT - 1
 *
 *  @return SVID
 */
uint32_t GPSData::SVID (uint32_t channel) const
{
    return this->rxChannel[channel] >> 24;
}

/**
 * Get the receiver state of the desired channel.  The bitmap format is outlined
 * in Table 3-9 of the SiRF Binary Protocol Manual.
 *
 *  @param channel Receive channel number in the range 0 to RECEIVE_CHANNEL_COUNT - 1
 *
 *  @return receiver state bitmap
 */
uint32_t GPSData::State (uint32_t channel) const
{
    return (this->rxChannel[channel] >> 16) & 0x00ff;
}

/**
 * Calculated GPS ground speed in units of 0.1 knots.
 * 
 * @return speed in 0.1 knots
 */
uint32_t GPSData::SpeedKnots() const
{
    // See GPSData.xls in unit_test for formula information. 
    return (speed * 24000) / 123383;
}

/**
 * Calculated GPS ground speed in units of 0.1 MPH
 * 
 * @return speed in 0.1 MPH
 */
uint32_t GPSData::SpeedMPH() const
{
    // See GPSData.xls in unit_test for formula information.
    return (speed * 1250) / 5588;
}

/**
 * Calculated GPS altitude in feet.
 * 
 * @return altitude in feet
 */
int32_t GPSData::AltitudeFeet() const
{
    // See GPSData.xls in unit_test for formula information.
    return (altitude * 100) / 3048;
}

/**
 * Number of seconds in UTC time since the GPS Epoch starting at 6 Jan 1980 0000 UTC.
 * 
 * @return number of seconds
 */
uint32_t GPSData::TimeSinceEpoch() const
{
    uint32_t tow = timeOfWeek / 1000;
    
    // Convert from GPS to UTC time base.
    return (weekNumber * 604800) + tow - ((tow - seconds + 60) % 60);
}

