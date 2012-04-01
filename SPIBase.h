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
 * Filename:     SPIBase.h                                                 *
 *                                                                         *
 ***************************************************************************/

#ifndef SPIBASE_H
#define SPIBASE_H

/**
 *  @defgroup onchip On-Chip Peripherals
 *
 *  @{
 */

/**
 * Object that provides the base functions and data members for
 * the SPI 0 and SPI 1 hardware.
 */
class SPIBase
{
public:
    /// Specifies the SPI data to clock phase relationship.  Settings specify; first data driven, other data driven, data sampled.
    typedef enum 
    {
        /// Prior to first SCK rising edge, SCK falling edge, SCK rising edge
        CPOL0_CPHA0,
        
        ///First SCK rising edge, SCK rising edge, SCK falling edge
        CPOL0_CPHA1,
        
        /// Prior to first SCK falling edge, SCK rising edge, SCK falling edge
        CPOL1_CPHA0,
        
        /// First SCK falling edge, SCK falling edge, SCK rising edge
        CPOL1_CPHA1
    } DataClockPhase;
    
    /// Specifies the maximum SPI clock rate based on the current PCLK setting.
    static const uint32_t MaxClock = 30000000;
};

/** @} */

#endif // #ifndef SPIBASE_H
