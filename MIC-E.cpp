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
 * Filename:     MIC-E.cpp                                                 *
 *                                                                         *
 ***************************************************************************/
 
#include "armlib.h"

/**
 * Generates the MIC-E encoded message.  The encoding standard is based
 * in the APRS Protocol Reference Version 1.0.1 document dated 29 Aug 2000.
 *
 * @param gps pointer to current GPS fix object
 */
void MICEncoder::Encode (const GPSData *gps)
{
    int32_t value;
    
    // NOTE: The Message A/B/C bits are hard coded as 110 for Enroute.
    
    // Convert to units of decimal degrees.
    value = abs(gps->latitude) / 10000000;
    
    // Encode the 10s and 1s of the decimal degrees.
    this->destAddress[0] = 'P' + (value / 10);
    this->destAddress[1] = 'P' + (value % 10);
    
    // Convert to units of 0.0001 minutes.
    value = 6 * (abs(gps->latitude) % 10000000);
    
    // Encode the decimal minutes.
    this->destAddress[2] = '0' + (value / 10000000) % 10;
    this->destAddress[3] = '0' + (value / 1000000) % 10;
    this->destAddress[4] = '0' + (value / 100000) % 10;
    this->destAddress[5] = '0' + (value / 10000) % 10;

    // Adjust for the N/S ordinal.
    if (gps->latitude > 0)
        this->destAddress[3] += 'P' - '0';
    
    // Adjust for the E/W ordinal.
    if (gps->longitude < 0)
        this->destAddress[5] += 'P' - '0';    
    
    // NULL terminate the string.    
    this->destAddress[6] = 0;

    
    // Set the Data Type ID.
    this->information[0] = '`';
    
    // Convert to units of decimal degrees.
    value = abs(gps->longitude) / 10000000;
    
    // Adjust the destination for the +100 longitude.
    if (value <= 9 || value >= 100)
        this->destAddress[4] += 'P' - '0';
    
    // Encode the longitude in degrees.
    if (value <= 9)
        this->information[1] = value + 118;
    else if (value <= 99)
        this->information[1] = value + 28;
    else if (value <= 109)
        this->information[1] = value + 8;
    else
        this->information[1] = value - 72;
    
    // Convert to units of 1 minute.
    value = (6 * (abs(gps->longitude) % 10000000)) / 1000000;
    
    // Encode the longitude in minutes.
    if (value <= 9)
        this->information[2] = value + 88;
    else
        this->information[2] = value + 28;
    
    // Convert to units of 0.01 minutes.
    value = ((6 * (abs(gps->longitude) % 10000000)) / 10000) % 100;
    
    // Encode the longitude in decimal minutes.
    this->information[3] = value + 28;
    
    // Convert to units of 1 knot.
    value = gps->SpeedKnots() / 10;
    
    // Encode the speed in knots and heading in degrees.
    this->information[4] = 28 + (value / 10);
    this->information[5] = 28 + ((value % 10) * 10) + (gps->heading / 10000);
    this->information[6] = 28 + (gps->heading / 100) % 100;
    
    // APRS symbol setting for balloon.
    this->information[7] = 'O';
    this->information[8] = '/';
    
    // Encode the altitude in meters above 10KM datum.
    value = (gps->altitude / 100) + 10000;
    
    this->information[9] = 33 + (value / 8281);
    this->information[10] = 33 + ((value / 91) % 91);
    this->information[11] = 33 + (value % 91);     
    this->information[12] = '}';
    
    // NULL terminate the string.
    this->information[13] = 0;
}

/**
 * Get the destination address encoded as a 6-character string.
 * 
 * @return NULL terminated string
 */
const char *MICEncoder::GetDestAddress()
{
    return this->destAddress;    
}

/**
 * Get the information field text that contains the MIC-E encoded text.
 * 
 * @return NULL terminate string
 */
const char *MICEncoder::GetInformationField()
{
    return this->information;
}

