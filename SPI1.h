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
 * Filename:     SPI1.h                                                    *
 *                                                                         *
 ***************************************************************************/

#ifndef SPI1_H
#define SPI1_H

/**
 *  @defgroup onchip On-Chip Peripherals
 *
 *  @{
 */

/**
 *   Object that manages the SPI 1 peripheral port.
 */
class SPI1 : public SPIBase
{
public:
    /// Specifies the data size in bits for each transfer.
    typedef enum 
    {
        /// 4-bit data transfer.
        DataSize_4Bits = 0x03,
        
        /// 5-bit data transfer.
        DataSize_5Bits = 0x04,
        
        /// 6-bit data transfer.
        DataSize_6Bits = 0x05,
        
        /// 7-bit data transfer.
        DataSize_7Bits = 0x06,
        
        /// 8-bit data transfer.
        DataSize_8Bits = 0x07,
        
        /// 9-bit data transfer.
        DataSize_9Bits = 0x08,
        
        /// 10-bit data transfer.
        DataSize_10Bits = 0x09,
        
        /// 11-bit data transfer.
        DataSize_11Bits = 0x0a,
        
        /// 12-bit data transfer.
        DataSize_12Bits = 0x0b,
        
        /// 13-bit data transfer.
        DataSize_13Bits = 0x0c,
        
        /// 14-bit data transfer.
        DataSize_14Bits = 0x0d,
        
        /// 15-bit data transfer.
        DataSize_15Bits = 0x0e,
        
        /// 16-bit data transfer.
        DataSize_16Bits = 0x0f,        
    } DataSize;
    
    void Disable();
    void Enable(uint32_t clockRate, DataSize dataSize, DataClockPhase dataClockPhase);
    void SetCS (bool_t state);
    uint32_t Read();
    uint32_t Write(uint32_t value);

    static SPI1 *GetInstance();
};

/** @} */

#endif // #ifndef SPI1_H
