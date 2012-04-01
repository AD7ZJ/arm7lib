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
 * Filename:     Navigation.h                                              *
 *                                                                         *
 ***************************************************************************/

#ifndef NAVIGATION_H
#define NAVIGATION_H

/**
 *  @defgroup library Generic Library Functions
 *
 *  @{
 */

/**
 * Variety of methods to calculate great circle distance and heading
 * based on GPS coordiantes.
 */
class Navigation
{
public:
    Navigation();
    Navigation(const GPSData *gps);
    Navigation(int32_t latitude, int32_t longitude);
    Navigation (float_t latitude, float_t longitude);
    
    void SetCoordinates(int32_t latitude, int32_t longitude);
    
    void DistCourse(const Navigation *nav);  
    void AddDistCourse (float_t faz, float_t s); 
    
    float_t DistanceNM();
    uint32_t DistanceFeet();
    int32_t Latitude();
    int32_t Longitude();
    float_t ForwardCourse();
    float_t ReverseCourse();
    
private:
    /// Maximum number of interations when calculating distance/course.
    static const uint32_t MaxIterationCount = 25;
    
    /// Error term limit for calculation of distance/course. 
    static const float_t EPSLimit = 0.00000000005;
    
    /// Latitude in radians
    float_t latitude;
    
    /// Longitude in radians
    float_t longitude;
    
    /// Distance between points in nautical miles.
    float_t distance;
    
    /// Forward course in degrees.
    float_t crs12;

    /// Reverse course in degrees.
    float_t crs21;
};

/** @} */

#endif // #ifndef NAVIGATION_H

