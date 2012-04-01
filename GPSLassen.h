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
 * Filename:     GPSLassen.h                                               *
 *                                                                         *
 ***************************************************************************/

#ifndef GPSLASSEN_H
#define GPSLASSEN_H

/**
 *  @defgroup external External Peripherals
 *
 *  @{
 */

/**
 *   Read and process the GPS Binary messages from the Trimble Lassen
 *   GPS engine.
 */
class GPSLassen
{
public:
    GPSLassen();
    
    GPSData *Data();
    bool_t IsDataReady();
    void Update();
    const char *Version();
    
    /**
     *   Callback to determine if the there is serial data to process from the GPS engine.
     *
     *    @return true if data is in FIFO; otherwise false
     */
    virtual bool_t HasData();

    /**
     *   Callback to read the oldest serial data from the GPS engine.
     *
     *   @return oldest byte from serial FIFO
     */
    virtual uint8_t ReadData();

    /**
     *   Callback to write serial data to the GPS engine.
     *
     *   @param data 8-bit data to write
     */
    virtual void WriteData(uint8_t data);
    
  	static GPSLassen *GetInstance();
    
private:
    /// The maximum length of a binary GPS engine message.
    static const uint32_t GPSBufferSize = 80;
    
    /// Number of bytes in the software version string.
    static const uint32_t VersionSize = 80;
    
    /// Number of seconds per week.  60 seconds/minute * 60 minutes/hour * 24 hours/day * 7 days/week.
    static const uint32_t SecondsPerWeek = 604800;
    
    /// TSIP packet start/end head
    static const uint32_t DLE = 0x10;
    
    /// TSIP data packet tail     
    static const uint32_t ETX = 0x03;    
    
	/// GPS parse engine state machine values.
	typedef enum 
	{
        MSG_IN_COMPLETE,
        
        TSIP_DLE,
        
        TSIP_IN_PARTIAL	    
	} GPS_PARSE_STATE_MACHINE;
	
	/// Report Packet 0x41 - GPS Time
	typedef struct __attribute__ ((__packed__))
	{
	    /// Always 0x41 for this message.
	    uint8_t messageID;
	
	    /// GPS time of week in seconds.
	    float_t timeOfWeek;
	
	    /// GPS extended week Number.
	    uint16_t weekNumber;
	
	    /// GPS UTC Offset (seconds).
	    float_t utcOffset;	
	} GPS_TIME_PACKET;	
	
	
	/// Report Packet 0x45 - Software Version Information
	typedef struct __attribute__ ((__packed__))
	{
	    /// Always 0x45 for this message.
	    uint8_t messageID;
	
	    /// Major version number for navigation processor.
	    uint8_t navMajorVersionNumber;
	
	    /// Minor version number.
	    uint8_t navMinorVersionNumber;
	
	    /// Month.
	    uint8_t navMonth;
	
	    /// Day.
	    uint8_t navDay;
	
	    /// Year number minus 1900.
	    uint8_t navYear;
	
	    /// Major version number for signal processor.
	    uint8_t sigMajorVersionNumber;
	
	    /// Minor version number.
	    uint8_t sigMinorVersionNumber;
	
	    /// Month.
	    uint8_t sigMonth;
	
	    /// Day.
	    uint8_t sigDay;
	
	    /// Year number minus 2000.
	    uint8_t sigYear;	
	} GPS_SOFTWARE_VERSION_PACKET;		
	
	
	/// Report Packet 0x46 - Health of Receiver
	typedef struct __attribute__ ((__packed__))
	{
	    /// Always 0x46 for this message.
	    uint8_t messageID;
	
	    /// Status Code in the range 0x00 to 0x0c.
	    uint8_t statusCode;
	
	    /// Battery and antenna status bitmap.
	    uint8_t batteryAntennaStatus;
	} GPS_RECEIVER_HEALTH_PACKET;
	
	/// Report Packet 0x4A - 20 Byte Format
	typedef struct __attribute__ ((__packed__))
	{
	    /// Always 0x4A for this message.
	    uint8_t messageID;
	
	    /// Latitude in radians.
	    float_t latitude;
	
	    /// Longitude in radians.
	    float_t longitude;
	
	    /// Altitude in meters (HAE or MSL).
	    float_t altitude;
	    	
	    /// Clock bias in meters.
	    float_t clockBias;
	    	
	    /// Time of fix in seconds (GPS or UTC),
	    float_t timeOfFix;	
	} GPS_LLA_PACKET;		

	/// Report Packet 0x56 - Velocity Fix, East-North-Up (ENU).
	typedef struct __attribute__ ((__packed__))
	{
	    /// Always 0x56 for this message.
	    uint8_t messageID;
	
	    /// East velocity in m/s; + for east, - for west.
	    float_t eastVelocity;
	
	    /// North velocity in m/s; + for north, - for south.
	    float_t northVelocity;
	
	    /// Up velocity in m/s; + for up, - for down.
	    float_t upVelocity;
	    	
	    /// Clock bias rate in m/s.
	    float_t clockBiasRate;
	    	
	    /// Time of Fix in seconds (GPS or UTC).
	    float_t timeOfFix;	
	} GPS_VELOCITY_FIX_PACKET;
	
	/// Report Packet 0x6D - All-In-View Satellite Selection
	typedef struct __attribute__ ((__packed__))
	{
	    /// Always 0x6d for this message.
	    uint8_t messageID;	
	    
	    /// Dimension
	    uint8_t dimension;
	    
	    /// PDOP.n
	    float_t pdop;
	    
	    /// HDOP.
	    float_t hdop;
	    
	    /// VDOP.
	    float_t vdop;
	    
	    /// TDOP.
	    float_t tdop;
	    
	    /// Array of SV PRNs in solution.
	    uint8_t svPRN[16];		
	} GPS_ALL_IN_VIEW_PACKET;

    void ParseMessage();
	void ProcessGPSTimePacket (const GPS_TIME_PACKET *packet);
	void ProcessAllInViewPacket(const GPS_ALL_IN_VIEW_PACKET *packet);
	void ProcessLLAPacket (const GPS_LLA_PACKET *packet);
	void ProcessVelocityFix (const GPS_VELOCITY_FIX_PACKET *packet);
	void ProcessReceiverHealth (const GPS_RECEIVER_HEALTH_PACKET *packet);
	void ProcessSoftwareVersion (const GPS_SOFTWARE_VERSION_PACKET *packet);
	
	void TimeOfWeek(uint32_t timeOfWeek);
	
	uint16_t UInt16GPSToHost (uint16_t value); 
	uint32_t Uint32GPSToHost (uint32_t value);
	float_t FloatGPSToHost (float_t nLongNumber);

    /// Object that stores the current GPS fix data.
    GPSData data;
	
	/// Index into gpsBuffer used to store message data.
	uint32_t gpsIndex;
	
	/// GPS Time of Week in seconds.
	uint32_t timeOfWeek;
	
	/// Offset in seconds between GPS and UTC time.
	uint32_t utcOffset;
	
	/// State machine used to parse the GPS message stream.
	GPS_PARSE_STATE_MACHINE gpsParseState;
	
	/// Buffer to store data as it is read from the GPS engine.
	uint8_t gpsBuffer[GPSBufferSize]; 
	
    /// Buffer to store the software version.
    char version[VersionSize];
	
    /// Flag that is set when a data set has been parsed.
    bool_t dataReadyFlag;
};

/** @} */

#endif  // #ifndef GPSLASSEN_H

