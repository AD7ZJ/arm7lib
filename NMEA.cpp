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
 * Filename:     AX25.cpp                                                  *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

/**
 * Generate the NMEA-0183 Global Positioning System Fix Data sentence.
 *
 * @param gps pointer to current GPS fix object
 * @param text pointer to NULL terminate string for NMEA-0183 string
 */
void NMEA::GPGGA (const GPSData *gps, char *text)
{
    char buffer[80];

    // Generate the GPGGA message.
    sprintf (text, "$GPGGA,");

    // UTC time stamp.
    Time (gps, text);

    // Latitude/longitude with ordinal.
    Coordinates (gps, text);

    // GPS status where 0: not available, 1: available
    if (gps->fixType == GPSData::NoFix)
        strcat (text, "0,");
    else
        strcat (text, "1,");

    // Number of visible birds.
    sprintf (buffer, "%02u,", gps->trackedSats);
    strcat (text, buffer);

    // DOP
    sprintf (buffer, "%u.%01u,", gps->dop / 10, gps->dop % 10);
    strcat (text, buffer);

    // Altitude in meters.
    sprintf (buffer, "%ld.0,M,,M,,", gps->altitude / 100);
    strcat (text, buffer);

    // Append the NMEA check sum.
    AppendChecksum (text);
}

/**
 * Generate the NMEA-0183 Recommended minimum specific GPS/Transit data sentence.
 *
 * @param gps pointer to current GPS fix object
 * @param text pointer to NULL terminate string for NMEA-0183 string
 */
void NMEA::GPRMC(const GPSData *gps, char *text)
{
    uint32_t knots;
    char buffer[80];

    // Generate the GPRMC message.
    sprintf (text, "$GPRMC,");

    // UTC time stamp.
    Time (gps, text);

    // GPS status.
    if (gps->fixType == GPSData::NoFix)
        strcat (text, "V,");
    else
        strcat (text, "A,");

    // Latitude/longitude with ordinal.
    Coordinates (gps, text);

    // Speed in knots and heading in degrees.
    knots = gps->SpeedKnots();
    sprintf (buffer, "%lu.%lu,%u.%u,", knots / 10, knots % 10, gps->heading / 100, (gps->heading % 100) / 10);
    strcat (text, buffer);

    // Date
    sprintf (buffer, "%02d%02d%02d,,", gps->day, gps->month, gps->year % 100);
    strcat (text, buffer);

    // Append the NMEA check sum.
    AppendChecksum (text);
}

/**
 * Append the NMEA string with the UTC time.
 *
 * @param gps pointer to current GPS fix object
 * @param text pointer to NULL terminate string for NMEA-0183 string
 */
void NMEA::Time(const GPSData *gps, char *text)
{
    char buffer[20];

    // UTC is replaced with flight time
    sprintf (buffer, "%02d%02d%02d,", gps->hours, gps->minutes, gps->seconds);
    strcat (text, buffer);
}

/**
 * Append the NMEA string with the latitude and longitude including ordinals.
 *
 * @param gps pointer to current GPS fix object
 * @param text pointer to NULL terminated string for NMEA-0183 string
 */
void NMEA::Coordinates(const GPSData *gps, char *text)
{
    uint32_t coord, coordMin;
    bool_t dirFlag;
    char buffer[80];

    // Latitude value.
    if (gps->latitude < 0) {
        coord = gps->latitude * -1;
        dirFlag = false;
    } else {
        dirFlag = true;
        coord = gps->latitude;
    }

    coordMin = 6 * (coord % 10000000);
    sprintf (buffer, "%02ld%02ld.%04ld,", coord / 10000000, coordMin / 1000000, (coordMin % 1000000) / 100);
    strcat (text, buffer);

    if (dirFlag == true)
        strcat (text, "N,");
    else
        strcat (text, "S,");

    // Longitude value.
    if (gps->longitude < 0) {
        coord = gps->longitude * - 1;
        dirFlag = 0;
    } else {
        dirFlag = 1;
        coord = gps->longitude;
    }

    coordMin = 6 * (coord % 10000000);
    sprintf (buffer, "%03ld%02ld.%04ld,", coord / 10000000, coordMin / 1000000, (coordMin % 1000000) / 100);
    strcat (text, buffer);

    if (dirFlag == 1)
        strcat (text, "E,");
    else
        strcat (text, "W,");
}

/**
 *   Append the message checksum and Carriage Return to the end of a NMEA-0183 message.
 *
 *   @param text Pointer to NULL terminated string that contains NMEA-0183 message.
 *
 *   @return checksum of buffer
 */
void NMEA::AppendChecksum (char *text)
{
    char buffer[10];
    uint32_t i, checksum;

    // We'll just quit if we get a NULL string.
    if (text[0] == 0)
        return;

    // Start with a 0x00 checksum.
    checksum = 0;

    // Start the check sum at the second character to skip over the '$' character at the start of the message.
    for (i = 1; text[i] != 0; ++i)
        checksum ^= text[i];

    // Generate and append the checksum text.
    sprintf (buffer, "*%02lX\015", checksum);
    strcat (text, buffer);
}
