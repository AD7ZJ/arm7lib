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
 * Filename:     IAP.cpp                                                   *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"
 
/// Set the In-Application Entry point address.  NOTE: LSB is set to 1 for Thumb Mode code.
const IAP::IAPMethod IAP::iap = reinterpret_cast <IAPMethod> (0x7ffffff1);

/// Starting address of each flash sector 1 through 26.
static const uint32_t SECTOR_ADDRESS_START[27] =
{
    0X00001000,
    0X00002000,
    0X00003000,
    0X00004000,
    0X00005000,
    0X00006000,
    0X00007000,
    0x00008000,
    0x00010000,
    0x00018000,
    0x00020000,
    0x00028000,
    0x00030000,
    0x00038000,
    0x00040000,
    0x00048000,
    0x00050000,
    0x00058000,
    0x00060000,
    0x00068000,
    0x00070000,
    0x00078000,
    0x00079000,
    0x0007A000,
    0x0007B000,
    0x0007C000,
    0x0007D000  // Specifies the first address after the end of flash memory
};

/// Sector number to indicate an invalid sector was selected.
const uint32_t INVALID_SECTOR = 99;

/**
 * Get the Device ID.
 * 
 * @return device ID
 */
uint32_t IAP::PartID()
{
    uint32_t result[2];
    uint32_t command = 54;
    
    iap (&command, result);
    
    return result[1];    
}

/**
 * Get the "Mask ROM" boot loader version.  The boot loader really resides in flash memory that is write
 * protected at the factory.
 * 
 * @return boot loader version
 */
uint32_t IAP::BootCodeVersion()
{
    uint32_t result[2];
    uint32_t command = 55;
    
    iap (&command, result);
    
    return result[1];    
}

/**
 * Erase the flash memory starting at the desired address for a block of bytes.  NOTE: The address range is
 * translated to device sector numbers.  Therefore the operational range may be larger than specified.
 * 
 * @param destAddress starting address to erase
 * @param length number of bytes to erase
 * 
 * @return IAP Status code
 */
IAP::StatusCode IAP::Erase (uint32_t destAddress, uint32_t length)
{
    StatusCode statusCode;
    uint32_t irqState, command[5], result[2];
    
    // 
    command[0] = 52;
    command[1] = Sector(destAddress);
    command[2] = Sector(destAddress + length);
    command[3] = SystemControl::GetInstance()->GetPClock() / 1000;
    
    if ((statusCode = PrepareSector(command[1], command[2])) != CmdSuccess)
        return statusCode;    
    
    // We have to disable interrupts because flash memory will not be available to execute out of.
    irqState = disableIRQ();
    
    iap (command, result);
    
    restoreIRQ (irqState);
    
    return static_cast <StatusCode> (result[0]);
}

/**
 * Write the flash memory starting at the desired address for a block of bytes.  NOTE: The length
 * must be 256, 512, 1024, or 4096 bytes.  The data pointer must be on a WORD boundary.
 * 
 * @param destAddress flash memory address
 * @param length number of bytes to write
 * @param data pointer to data block
 * 
 * @return IAP Status code
 */
IAP::StatusCode IAP::Write (uint32_t destAddress, uint32_t length, void *data)
{
    StatusCode statusCode;
    uint32_t irqState, command[5], result[2];
    
    if ((statusCode = PrepareSector(Sector(destAddress), Sector(destAddress + length))) != CmdSuccess)
        return statusCode;
    
    command[0] = 51;
    command[1] = destAddress;
    command[2] = reinterpret_cast <uint32_t> (data);
    command[3] = length;
    command[4] = SystemControl::GetInstance()->GetPClock() / 1000;
    
    // We have to disable interrupts because flash memory will not be available to execute out of.
    irqState = disableIRQ();
    
    iap (command, result);
    
    restoreIRQ (irqState);
    
    return static_cast <StatusCode> (result[0]);
}

/**
 * Prepare the flash memory for erase or write operations.
 * 
 * @param startSector starting sector number of operational block
 * @param endSector ending sector number (inclusive) of operational block
 * 
 * @return IAP Status code
 */
IAP::StatusCode IAP::PrepareSector (uint32_t startSector, uint32_t endSector)
{
    uint32_t command[5];
    uint32_t result[2];

    command[0] = 50;
    command[1] = startSector;
    command[2] = endSector;

    iap (command, result);
    
    return static_cast <StatusCode> (result[0]); 
}

/**
 * Get the Flash Memory sector at the specified memory address.
 * 
 * @param address desired flash memory address
 * 
 * @return sector number; otherwise INVALID_SECTOR if invalid address is specified
 */
uint32_t IAP::Sector(uint32_t address)
{
    uint32_t i;
    
    // Error if we are before the flash memory area.
    if (address < SECTOR_ADDRESS_START[0])
        return InvalidSector;
    
    // Look up the sector number.  The sectors vary between 4K and 32K each.
    for (i = 0; i < 27; ++i)
        if (address < SECTOR_ADDRESS_START[i])
            return i;
    
    // We are past the end, show an error.
    return InvalidSector;    
}
