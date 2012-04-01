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
 * Filename:     Navigation.cpp                                            *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

/**
 * Constructor.
 */
Navigation::Navigation()
{
    this->latitude = 0.;
    this->longitude = 0.;
}

/**
 * Set the current latitude and longitude coordinates.
 *
 * @param gps pointer to GPS data set
 */
Navigation::Navigation (const GPSData *gps)
{
    this->latitude = (static_cast<float_t>(gps->latitude) / 10000000.0) * M_PI / 180.0;
    this->longitude = (static_cast<float_t>(gps->longitude) / 10000000.0) * M_PI / 180.0;
}

/**
 * Set the current latitude and longitude coordinates.
 *
 * @param latitude Latitude in degrees * 10 ^ 7, where + is North, - is South.
 * @param longitude Longitude in degrees * 10 ^ 7, where + is East, - is West.
 */
Navigation::Navigation (int32_t latitude, int32_t longitude)
{
    SetCoordinates(latitude, longitude);
}

/**
 * Set the current latitude and longitude coordinates.
 *
 * @param latitude Latitude in degrees, where + is North, - is South.
 * @param longitude Longitude in degrees, where + is East, - is West.
 */
Navigation::Navigation (float_t latitude, float_t longitude)
{
    this->latitude = latitude * M_PI / 180.0;
    this->longitude = longitude * M_PI / 180.0;
}

/**
 * Current latitude in degrees * 10 ^ 7, where + is North, - is South
 */
int32_t Navigation::Latitude()
{
    return lroundf(this->latitude * 1800000000. / M_PI);
}

/**
 * Current longitude in degrees * 10 ^ 7, where + is East, - is West
 */
int32_t Navigation::Longitude()
{
    return lroundf(this->longitude * 1800000000. / M_PI);
}

/**
 * Set the current latitude and longitude coordinates.
 * 
 * @param latitude Latitude in degrees * 10 ^ 7, where + is North, - is South
 * @param longitude Longitude in degrees * 10 ^ 7, where + is East, - is West
 */
void Navigation::SetCoordinates (int32_t latitude, int32_t longitude)
{
    this->latitude = (static_cast<float_t>(latitude) / 10000000.) * M_PI / 180.;
    this->longitude = (static_cast<float_t>(longitude) / 10000000.) * M_PI / 180.;
}

/**
 * Calculate the distance and course from the current location to the one specified as
 * the navigation point.
 * 
 * @param nav pointer to destination coordinate
 */
void Navigation::DistCourse(const Navigation *nav)
{
    float_t a = 6378.137/1.852;
    float_t f = 1/298.257223563;
    
    float_t r, tu1, tu2, cu1, su1, cu2, s1, b1, f1;
    float_t x, sx = 0, cx = 0, sy = 0, cy = 0,y = 0, sa, c2a = 0, cz = 0, e = 0, c, d;
    float_t EPS = EPSLimit;
    float_t faz, baz, s;
    uint32_t iter = 1;
    
    r = 1 - f;
    tu1 = r * tan (this->latitude);
    tu2 = r * tan (nav->latitude);
    cu1 = 1. / sqrt (1. + tu1 * tu1);
    su1 = cu1 * tu1;
    cu2 = 1. / sqrt (1. + tu2 * tu2);
    s1 = cu1 * cu2;
    b1 = s1 * tu2;
    f1 = b1 * tu1;
    x = nav->longitude - this->longitude;
    d = x + 1; // force one pass

    while ((abs(d - x) > EPS) && (iter < MaxIterationCount))
    {
        ++iter;
        
        sx = sin (x);
        cx = cos (x);
        tu1 = cu2 * sx;
        tu2 = b1 - su1 * cu2 * cx;
        sy = sqrt(tu1 * tu1 + tu2 * tu2);
        cy = s1 * cx + f1;
        y = atan2 (sy, cy);
        sa = s1 * sx / sy;
        c2a = 1 - sa * sa;
        cz = f1 + f1;
        
        if (c2a > 0.)
            cz = cy - cz / c2a;
        
        e = cz * cz * 2. - 1.;
        c = ((-3. * c2a + 4.) * f + 4.) * c2a * f / 16.;
        d = x;
        x = ((e * cy * c + cz) * sy * c + y) * sa;
        x = (1. - c) * x * f + nav->longitude - this->longitude;
    } // END while
    
    faz = atan2(tu1, tu2);
    baz = (atan2(cu1 * sx, b1 * cx - su1 * cu2) + M_PI);
    
    x = sqrt ((1 / (r * r) - 1) * c2a + 1);
    x +=1;
    x = (x - 2.) / x;
    
    c = 1. - x;
    c = (x * x / 4. + 1.) / c;
    d = (0.375 * x * x - 1.) * x;
    x = e * cy;
    
    s = ((((sy*sy*4.-3.)*(1.-e-e)*cz*d/6.-x)*d/4.+cz)*sy*d+y)*c*a*r;

    this->distance = s;
    
    this->crs12 = faz * (180. / M_PI);
    
    if (this->crs12 < 0)
        this->crs12 += 360.;

    if (this->crs12 >= 360.)
        this->crs12 -= 360.;

    this->crs21 = baz * (180. / M_PI);
    
    if (this->crs21 < 0)
        this->crs21 += 360.;

    if (this->crs21 >= 360.)
        this->crs21 -= 360.;    
}

/**
 * Add a vector (course and distance) to the current coordinate location.
 * 
 * @param faz course in degrees 0 to 359.9
 * @param s distance in nautical miles
 */
void Navigation::AddDistCourse(float_t faz, float_t s) 
{
    float_t r, tu, sf, cf, b, cu, su, sa, c2a, x, c, d, y, sy = 0, cy = 0, cz = 0, e = 0;

    float_t a = 6378.137/1.852;
    float_t f = 1/298.257223563;
    
    faz = faz * M_PI / 180.;
    
    r = 1 - f;
    tu = r * tan (-this->latitude);
    sf = sin (faz);
    cf = cos (faz);

    if (cf==0)
        b=0.;
    else
        b=2. * atan2 (tu, cf);

    cu = 1. / sqrt (1 + tu * tu);
    su = tu * cu;
    sa = cu * sf;
    c2a = 1 - sa * sa;
    x = 1. + sqrt (1. + c2a * (1. / (r * r) - 1.));
    x = (x - 2.) / x;
    c = 1. - x;
    c = (x * x / 4. + 1.) / c;
    d = (0.375 * x * x - 1.) * x;
    tu = s / (r * a * c);
    y = tu;
    c = y + 1;
    
    while (abs (y - c) > EPSLimit)
    {
        sy = sin (y);
        cy = cos (y);
        cz = cos (b + y);
        e = 2. * cz * cz - 1.;
        c = y;
        x = e * cy;
        y = e + e - 1.;
        y = (((sy * sy * 4. - 3.) * y * cz * d / 6. + x) * d / 4. - cz) * sy * d + tu;
    }

    b = cu * cy * cf - su * sy;
    c = r * sqrt (sa * sa + b * b);
    d = su * cy + cu * sy * cf;
    this->latitude = (atan2 (d, c));
    
    c = cu * cy - su * sy * cf;
    x = atan2 (sy * sf, c);
    c = ((-3. * c2a + 4.) * f + 4.) * c2a * f / 16.;
    d = ((e * cy * c + cz) * sy * c + y) * sa;
    this->longitude = (this->longitude + x - (1. - c) * d * f); 
}

/**
 * Distance in nautical miles from DistCourse method call.
 * 
 * @return distance in units of nautical miles
 */
float_t Navigation::DistanceNM()
{
    return this->distance;
}

/**
 * Distance in feet from DistCourse method call.
 * 
 * @return distance in units of feet
 */
uint32_t Navigation::DistanceFeet()
{
    return lroundf(this->distance * 185200.0 / 30.48);
}

/**
 * Forward course heading in degrees from DistCourse method call.
 * 
 * @return forward course in units of degrees
 */
float_t Navigation::ForwardCourse()
{
    return this->crs12;
}

/**
 * Reverse course heading in degrees from DistCourse method call.
 * 
 * @return forward course in units of degrees
 */
float_t Navigation::ReverseCourse()
{
    return this->crs21;
}
