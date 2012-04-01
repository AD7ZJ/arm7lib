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
 * Filename:     AD9832.h                                                  *
 *                                                                         *
 ***************************************************************************/

#ifndef AD9832_H
#define AD9832_H

/**
 *  @defgroup external External Peripherals
 *
 *  @{
 */

/**
 *   Control the Analog Devices AD9832 DDS.  The AD9832 is a numerically 
 *   controlled oscillator employing a phase accumulator, a sine look-up 
 *   table and a 10-bit D/A converter integrated on a single CMOS chip.
 *   Modulation capabilities are provided for phase modulation and frequency
 *   modulation.
 */
class AD9832
{
public:
    AD9832();
    
    /// Specifies 1 of 4 possible profiles.
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
    } PROFILE_SELECT;
    
    /// Desired operational DDS mode.
    typedef enum 
    {
        /// Low power sleep mode.
        Sleep,
        
        /// Operational mode.
        PowerOn
    } DDSMode;
    
    /// Specifies reference frequency standard.
    typedef enum
    {
        /// 24.5535MHz reference frequency.
        Freq24553500Hz = 0,      
        
        /// 25.0MHz reference frequency.
        Freq25000000Hz = 1
    } ReferenceFrequency;
    
    /**
     *   Callback to set the Chip Select control line.
     *
     *    @param state false to set line low and enable device; otherwise true
     */
    virtual void IOSetCS(bool_t state);

    /**
     *   Callback to clock and send data over SPI bus.
     *
     *   @param data 8-bit data to write
     */
    virtual void SPIWrite(uint8_t data);
    
    /**
     *   Callback to set the profile select control lines.
     *
     *   @param profile enumerated type that selects 1 of 4 possible profiles
     */      
    virtual void IOSetProfileSelect(PROFILE_SELECT profile);      
    
    
    void Enable();
    void SetFreq(uint32_t freq);
    void SetReferenceFrequency (ReferenceFrequency referenceFrequency);
    void SetMode (DDSMode mode);
    
    static AD9832 *GetInstance();    
	
private:
    void SetFTW (uint32_t ftw);
    void WriteRegister (uint32_t data);
    
    /// TCXO reference frequency.
    ReferenceFrequency referenceFrequency;
};

/** @} */

#endif // #ifndef AD9832_H

