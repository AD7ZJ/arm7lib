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
 * Filename:     IAP.h                                                     *
 *                                                                         *
 ***************************************************************************/

#ifndef IAP_H
#define IAP_H

/**
 *  @defgroup onchip On-Chip Peripherals
 *
 *  @{
 */

/**
 *  Provide support for IAP (In-Application Programming).
 */
class IAP
{
public:
    /// IAP Status Codes.
    typedef enum
    {
        /// Command is executed successfully.
        CmdSuccess = 0,
        
        /// Invalid command.
        InvalidCommand = 1,
        
        /// Source address is not on a word boundary.
        SrcAddressError = 2,
        
        /// Destination address is not on a correct boundary.
        DsgAddressError = 3,
        
        /// Source address is not mapped in the memory map.
        SrcAddressNotMapped = 4,
        
        /// Destination address is not mapped in the memory map.
        DstAddressNotMapped = 5,
        
        /// Byte count is not multiple of 4 or is not a permitted value.
        CountError = 6,
        
        /// Sector number is invalid.
        InvalidSector = 7,
        
        /// Sector is not blank.
        SectorNotBlank = 8,
        
        /// Command to prepare sector for write operation was not executed.
        SectorNotPreparedForWriteOperation = 9,
        
        /// Source and destination data is not same.
        CompareError = 10,
        
        /// Flash programming hardware interface is busy.
        Busy = 11
    } StatusCode;
    
    static uint32_t BootCodeVersion();
    static StatusCode Erase (uint32_t destAddress, uint32_t length);
    static uint32_t PartID();
    static StatusCode Write (uint32_t destAddress, uint32_t length, void *data);
    
private:
    static uint32_t Sector(uint32_t address);
    static StatusCode PrepareSector (uint32_t startSector, uint32_t endSector);
    
    /// Pointer to function to call "Masked ROM" IAP routine.
    typedef void (*IAPMethod)(uint32_t[], uint32_t[]);
    
    /// Entry point to the the IAP routines in "masked ROM".
    static const IAPMethod iap;
};

/** @} */

#endif // #ifndef IAP_H
