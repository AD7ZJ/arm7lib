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
 * Filename:     GPSLassen.cpp                                             *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

/// Reserve memory for the singleton object.
static GPSLassen lassenSingletonObject;

/**
 * Constructor.
 */
GPSLassen::GPSLassen()
{
    this->gpsParseState = MSG_IN_COMPLETE;
    this->dataReadyFlag = false;
    this->utcOffset = 0;
    this->timeOfWeek = 0;
    
    this->data.navType = 0xff;
}

/**
 * Get a pointer to the Lassen GPS Engine object.
 */
GPSLassen *GPSLassen::GetInstance()
{
	return 	&lassenSingletonObject;
}

/**
 *   Get a pointer to the GPSData object that contains the latest fix information.
 *
 *   @return pointer to GPSData object
 */
GPSData *GPSLassen::Data()
{
    return &this->data;
}

/**
 *  Convert a 16-bit value's endian order.
 *
 *  @param value to convert
 *
 *  @return reserve endian value
 */
uint16_t GPSLassen::UInt16GPSToHost (uint16_t value)
{
    return ((value >> 8) & 0x00ff) | ((value << 8) & 0xff00);
}

/**
 *  Convert a 32-bit value's endian order.
 *
 *  @param value to convert
 *
 *  @return reserve endian value
 */
uint32_t GPSLassen::Uint32GPSToHost (uint32_t value)
{
    return ((value >> 24) & 0x0000ff) | ((value >> 8) & 0x0000ff00) | ((value << 8) & 0x00ff0000) | ((value << 24) & 0xff000000);
}

/**
 * Convert a 32-bit floating piont value's endian order.
 * 
 * @param nLongNumber to convert
 *
 * @return reserve endian value
 */
float_t GPSLassen::FloatGPSToHost (float_t nLongNumber)
{
    union u { float_t vi; uint8_t c[sizeof(float_t)]; }; 
    union v { float_t ni; uint8_t d[sizeof(float_t)]; };
    union u un; 
    union v vn;
    
    un.vi = nLongNumber; 
    vn.d[0]=un.c[3]; 
    vn.d[1]=un.c[2]; 
    vn.d[2]=un.c[1]; 
    vn.d[3]=un.c[0];
    
    return (vn.ni); 
}

/**
 *   Determine if new GPS message is ready to process.  This function is a one shot and
 *   typically returns true once a second for each GPS position fix.
 *
 *   @return true if new message available; otherwise false
 */
bool_t GPSLassen::IsDataReady()
{
    if (this->dataReadyFlag)
    {
        this->dataReadyFlag = false;
        return true;
    } //END if

    return false;
}

/**
 *   Process the primary timing packet.
 *
 *   @param packet pointer to GPS_TIME_PACKET structure
 */
void GPSLassen::ProcessGPSTimePacket (const GPS_TIME_PACKET *packet)
{
    this->data.weekNumber = UInt16GPSToHost(packet->weekNumber);
    this->utcOffset = lroundf (FloatGPSToHost(packet->utcOffset));
}

/**
 * Process the All-In-View Satellite Selection.
 * 
 * @param packet pointer to GPS_ALL_IN_VIEW_PACKET structure.
 */
void GPSLassen::ProcessAllInViewPacket(const GPS_ALL_IN_VIEW_PACKET *packet)
{
    this->data.fixType = GPSData::NoFix;
    
    if (this->data.navType == 0x00)
        switch (packet->dimension & 0x07)
        {
            case 3:
                this->data.fixType = GPSData::Fix2D;
                break;
                
            case 4:
                this->data.fixType = GPSData::Fix3D;
                break;
        } // END switch
    
    this->data.trackedSats = packet->dimension >> 4;
    
    this->data.dop = lroundf (10.0 * FloatGPSToHost(packet->pdop));   
}

/**
 * Process the 20 Byte Format packet.  This packet provides current GPS position
 * fix in LLA (latitude, longitude, and altitude) coordinates.
 * 
 * @param packet pointer to GPS_LLA_PACKET structure.
 */
void GPSLassen::ProcessLLAPacket (const GPS_LLA_PACKET *packet)
{
    // GPS Time Of Week
    this->timeOfWeek = lroundf(FloatGPSToHost(packet->timeOfFix));
    
    // Convert to UTC time and populate HHMMSS and MMDDYYYY structure.
    TimeOfWeek(this->timeOfWeek);
    
    this->data.latitude = lroundf (572957795.13082197 * FloatGPSToHost(packet->latitude));
    this->data.longitude = lroundf (572957795.13082197 * FloatGPSToHost(packet->longitude));
    this->data.altitude = lroundf (100.0 * FloatGPSToHost (packet->altitude));
 
    // Populate the raw GPS units.
    *reinterpret_cast <float_t *> (this->data.rawLatitude) = packet->latitude;
    *reinterpret_cast <float_t *> (this->data.rawLongitude) = packet->longitude;
    *reinterpret_cast <float_t *> (this->data.rawAltitude) = packet->altitude;
}

/**
 * Convert the GPS Time of Week into units for the GPSData object
 * 
 * @param timeOfWeek GPS time of week
 */
void GPSLassen::TimeOfWeek(uint32_t timeOfWeek)
{
    RTCTime rtcTime(this->data.weekNumber, timeOfWeek, this->utcOffset);
    
    this->data.hours = rtcTime.hours;
    this->data.minutes = rtcTime.minutes;
    this->data.seconds = rtcTime.seconds;
    
    this->data.month = rtcTime.month;
    this->data.day = rtcTime.day;
    this->data.year = rtcTime.year;
    
    // Convert to units of milliseconds.
    this->data.timeOfWeek = (1000 * timeOfWeek);
}

/**
 * Process the Velocity Fix, East-North-Up (ENU).
 * 
 * @param packet pointer to GPS_VELOCITY_FIX_PACKET structure.
 */
void GPSLassen::ProcessVelocityFix (const GPS_VELOCITY_FIX_PACKET *packet)
{
    float_t nsv, ewv;
    int32_t heading;
    
    nsv = FloatGPSToHost(packet->northVelocity);
    ewv = FloatGPSToHost(packet->eastVelocity);
    
    // Populate the raw GPS units.
    reinterpret_cast <float_t *> (this->data.rawSpeedHeading)[0] = packet->northVelocity;
    reinterpret_cast <float_t *> (this->data.rawSpeedHeading)[1] = packet->eastVelocity;
    
    this->data.speed = static_cast <uint16_t> (lroundf (100.0 * sqrt(ewv * ewv + nsv * nsv)));
    
    // 5729.57795130 is the constant 100 * (360 degrees / 2 * PI).  100 scales the result to units of 0.01 degrees.
    heading = lroundf (5729.577951308 * atan2(ewv, nsv));
    
    // Convert atan2 from range of { -pi, pi } radians to { 0, 359.99 } degrees.
    this->data.heading = static_cast <uint16_t> (heading < 0 ? heading + 36000 : heading);    
}

/**
 * Process the receiver health.
 * 
 * @param packet pointer to PS_RECEIVER_HEALTH_PACKET structure.
 */
void GPSLassen::ProcessReceiverHealth (const GPS_RECEIVER_HEALTH_PACKET *packet)
{
    this->data.navType = packet->statusCode;
}

/**
 * Process the software version packet.
 * 
 * @param packet pointer to GPS_SOFTWARE_VERSION_PACKET structure.
 */
void GPSLassen::ProcessSoftwareVersion (const GPS_SOFTWARE_VERSION_PACKET *packet)
{
    sprintf(this->version, "Navigation v%d.%d %d/%d/%d, Processor v%d.%d %d/%d/%d", packet->navMajorVersionNumber, packet->navMinorVersionNumber, packet->navMonth, packet->navDay, packet->navYear + 2000, packet->sigMajorVersionNumber, packet->sigMinorVersionNumber, packet->sigMonth, packet->sigDay, packet->sigYear + 2000);
}

/**
 *   Determine the type of GPS message and parse it.
 */
void GPSLassen::ParseMessage()
{
    // Byte 0 is the messageID.
    switch (this->gpsBuffer[0])
    {
    	// Report Packet 0x41 - GPS Time
    	case 0x41:
    		ProcessGPSTimePacket (reinterpret_cast<GPS_TIME_PACKET *> (gpsBuffer));
    		break;
    		
    	// Report Packet 0x45 - Software Version Information
    	case 0x45:
    		ProcessSoftwareVersion (reinterpret_cast<GPS_SOFTWARE_VERSION_PACKET *> (gpsBuffer));
    		break;
    	
    	// Report Packet 0x46 - Health of Receiver
    	case 0x46:
    		ProcessReceiverHealth (reinterpret_cast<GPS_RECEIVER_HEALTH_PACKET *> (gpsBuffer));
    		break;
    		
    	// Report Packet 0x4A - 20 Byte Format
    	case 0x4a:
			ProcessLLAPacket (reinterpret_cast<GPS_LLA_PACKET *> (gpsBuffer));
    		break;
    		
		// Report Packet 0x4B - Machine/Code ID and Additional Status    		
    	case 0x4b:
    		break;
    	
    	// Report Packet 0x56 - Velocity Fix, East-North-Up (ENU).
    	case 0x56:
    		ProcessVelocityFix (reinterpret_cast<GPS_VELOCITY_FIX_PACKET *> (gpsBuffer));
    		break;
    	
    	// Report Packet 0x6D - All-In-View Satellite Selection
		case 0x6d:
			ProcessAllInViewPacket (reinterpret_cast<GPS_ALL_IN_VIEW_PACKET *> (gpsBuffer));
			break;
		
		// Report Packet 0x82 - Differential Position Fix Mode	
		case 0x82:
		    // The time of week doesn't increment without a fix, so we generate our own value.		    
		    if (this->data.fixType == GPSData::NoFix)
		    {
		        if (++this->timeOfWeek == SecondsPerWeek)
		            this->timeOfWeek = 0;
		        
		        TimeOfWeek (this->timeOfWeek);
		    } // END if
		    
		    // Set this flag to indicate we have a complete data set.  NOTE: This is the last packet sent during each reporting period.
		    this->dataReadyFlag = true;  		    
			break;
			
		default:
			break;	            
        
    } // END swich
}

/**
 *   Read the serial FIFO and process complete GPS messages.
 */
void GPSLassen::Update() 
{
    uint32_t value;

    // This state machine handles each characters as it is read from the GPS serial port.
    while (HasData()) 
    {
        // Get the character value.
        value = ReadData();

        // Process based on the state machine.
        switch (this->gpsParseState) 
        {
            case MSG_IN_COMPLETE:               
                if (value == DLE) 
                {
                    this->gpsParseState = TSIP_DLE;
                    this->gpsIndex = 0;
                }
                break;
    
            case TSIP_DLE:
                if (value == ETX) 
                {
                    if (this->gpsIndex > 0)
                    {
                        ParseMessage();
                        
                        this->gpsParseState = MSG_IN_COMPLETE;
                    }
                    else
                    {
                        this->gpsParseState = MSG_IN_COMPLETE;
                    }
                }
                else  
                {
                    this->gpsParseState = TSIP_IN_PARTIAL;
                    this->gpsBuffer[this->gpsIndex++] = value;
                }
                break;
    
            case TSIP_IN_PARTIAL:
                if (value == DLE) 
                {
                    this->gpsParseState = TSIP_DLE;
                }
                else 
                {
                    this->gpsBuffer[this->gpsIndex++] = value;
                }
                break;
        } // END switch
    } // END while
}

/**
 * GPS engine version information.
 * 
 * @return pointer to NULL termianted string
 */
const char *GPSLassen::Version()
{
    return this->version;
}
