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
 * Filename:     GPSData.h                                                 *
 *                                                                         *
 ***************************************************************************/

#ifndef GPSDATA_H
#define GPSDATA_H

/**
 *  @defgroup library Generic Library Functions
 *
 *  @{
 */

/**
*   Object that manages a generic GPS fix data set.
*/
class GPSData
{
public:
    GPSData();

    int32_t AltitudeFeet() const;
    uint32_t AverageCNo() const;
    uint32_t CNo(uint32_t channel) const;
    void RxChannel (uint32_t channel, uint32_t prn, uint32_t state, uint32_t cNo);
    uint32_t SpeedKnots() const;
    uint32_t SpeedMPH() const;
    uint32_t State (uint32_t channel) const;
    uint32_t SVID (uint32_t channel) const;
    uint32_t TimeSinceEpoch() const;

    /// Enumeration that describes the fix type.
    typedef enum
    {
        /// No GPS fix.
        NoFix = 0x00,

        /// 2D only (no altitude) fix.
        Fix2D = 0x02,

        /// 3D (with altitude) fix.
        Fix3D = 0x03
    } FixType;

    /// Number of receive channels.
    static const uint32_t RECEIVE_CHANNEL_COUNT = 12;

    /// GPS Time Of Week in milliseconds.
    uint32_t timeOfWeek;

    /// GPS Week Number.
    uint32_t weekNumber;

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

    /// Latitude in degrees * 10 ^ 7, where + is North, - is South.
    int32_t latitude;

    /// Longitude in degrees * 10 ^ 7, where + is East, - is West.
    int32_t longitude;

    /// Raw, unprocessed latitude data from the GPS engine.  Data format is GPS engine dependent.
    uint8_t rawLatitude[4];

    /// Raw, unprocessed longitude data from the GPS engine.  Data format is GPS engine dependent.
    uint8_t rawLongitude[4];

    /// Altitude from MSL in cm.
    int32_t altitude;

    /// Raw, unprocessed altitude data from the GPS engine.  Data format is GPS engine dependent.
    uint8_t rawAltitude[4];

    /// Speed over the ground in cm/second.
    uint16_t speed;

    /// Heading clockwise from north in units of 0.01 degrees.
    uint16_t heading;

    /// Raw, unprocessed speed/heading data from the GPS engine.  Data format is GPS engine dependent.
    uint8_t rawSpeedHeading[8];

    /// DOP (Dilution of Precision)
    uint16_t dop;

    /// Number of tracked satellites used in the fix position.
    uint16_t trackedSats;

    /// Number of visible satellites.
    uint16_t visibleSats;

    /// GPS fix type, None/2D/3D.
    FixType fixType;

    /// Raw navigation type information from GPS engine.  (Varies based on type of GPS Engine).
    uint16_t navType;

    /// Time in seconds until the first 2D or 3D fix with a 1-PPS aligned Time of Day.
    uint8_t timeToFirstFix;

private:
    /// SV PRN, state, and C/No for each of the 12 receiver channels.
    uint32_t rxChannel[RECEIVE_CHANNEL_COUNT];
};

/** @} */

#endif // #ifndef GPSDATA_H
