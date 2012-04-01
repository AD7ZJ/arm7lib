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
 * Filename:     AD9954.h                                                  *
 *                                                                         *
 ***************************************************************************/

#ifndef AD9954_H
#define AD9954_H

/**
 *  @defgroup external External Peripherals
 *
 *  @{
 */

/**
 *   Control the Analog Devices AD9954 DDS.  The AD9954 is a 400 MSPS, 
 *   14-Bit, 1.8 V CMOS, Direct Digital Synthesizer.
 */
class AD9954
{
public:
    /// Desired operational DDS mode.
    typedef enum 
    {
        /// Place the DDS in low power mode
        PowerDown,

        /// CW (Continuous Wave) carrier.
        CW,
        
        /// CW (Continuous Wave) carrier with automatic OSK (Output Shift Keying) disabled.
        CWNoAutoOSK
    } DDSMode;
    
    /// Enumerated type that selects 1 of 4 possible profiles.
    typedef enum
    {
        /// Profile select 0 and 1 are set low.
        Profile0 = 0x00,
        
        /// Profile select 0 is set high and 1 is set low.
        Profile1 = 0x01,
        
        /// Profile select 0 is set low and 1 is set high.
        Profile2 = 0x02,
        
        /// Profile select 0 and 1 are set high.
        Profile3 = 0x03
    } ProfileSelect;
    
    /**
     *   Callback to set the Chip Select control line.
     *
     *   @param state false to set line low and enable device; otherwise true
     */
    virtual void IOSetCS(bool_t state);

    /**
     *   Callback to clock and read data from the SPI bus.
     *
     *   @return 8-bit data read from SPI bus
     */
    virtual uint8_t SPIRead();

    /**
     *   Callback to clock and send data over SPI bus.
     *
     *   @param data 8-bit data to write
     */
    virtual void SPIWrite(uint8_t data);
    
    /**
     *   Callback to set OSK (Output Shift Key) control line.
     *
     *   @param state true to turn on RF output; otherwise false
     */    
    virtual void IOSetOSK(bool_t state);
    
    /**
     *   Callback to set I/O Update strobe line.
     *
     *   @param state true to update the I/O registers; otherwise false
     */    
    virtual void IOSetIOUpdate(bool_t state);
    
    /**
     *   Callback to set the Reset control line.
     *
     *   @param state true to place AD9954 in reset mode
     */      
    virtual void IOSetReset(bool_t state);
    
    /**
     *   Callback to set the profile select control lines.
     *
     *   @param profile enumerated type that selects 1 of 4 possible profiles
     */      
    virtual void IOSetProfileSelect(ProfileSelect profile);    

    void Enable();
    static uint32_t GetAmplitudeScale (uint32_t amplitude);
    void SetAmplitude (uint32_t amplitude);
    void SetAmplitudeRampRate (uint32_t arr);
    void SetFreq(uint32_t freq);
    void SetFTW (uint32_t ftw);
    void SetMode (DDSMode mode);
    void SetOSK (bool_t state);
    void SetOutputScale (uint32_t scale);
    void SetPhase (bool_t phase);
    
    static AD9954 *GetInstance();
};

/** @} */

#endif // #ifndef AD9954_H

