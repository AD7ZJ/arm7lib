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
 * Filename:     NMEA.h                                                    *
 *                                                                         *
 ***************************************************************************/

#ifndef NMEA_H
#define NMEA_H

/**
 *  @defgroup library Generic Library Functions
 *
 *  @{
 */

/**
 *  Generate NMEA-0183 (National Marine Electronics Assocation) compatible
 *  sentences from GPS fix information.
 */
class NMEA
{
public:
    static void AppendChecksum (char *buffer);
    static void GPGGA (const GPSData *gps, char *text);
    static void GPRMC(const GPSData *gps, char *text);
    
private:
    static void Coordinates(const GPSData *gps, char *text);
    static void Time(const GPSData *gps, char *text);
};

/** @} */

#endif  // #ifndef NMEA_H
