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
 * Filename:     M25P80.cpp                                                *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

/// Reserve memory for singleton object.
static M25P80 m25P80SingletonObject;

/**
 *  Get a pointer to the hg object.
 */
M25P80 *M25P80::GetInstance()
{
    return  &m25P80SingletonObject;
}

/** 
 *   Determine if a flash write or erase operation is in progress.
 *
 *   @return true if write/erase in progress
 */
bool_t M25P80::IsWriteInProgress()
{
    uint8_t status;

    IOSetCS (false);

    // Read Status Register (RDSR) flash command.
    SPIWrite (0x05);

    status = SPIRead();

    IOSetCS (true);

    return (((status & 0x01) == 0x01) ? true : false);
}

/**
 *   Read a block of memory from the flash device.
 *
 *   @param address of desired location in the range 0x00000 to 0xFFFFF (1MB)
 *   @param blockPnt pointer to locate of data block
 *   @param length number of bytes to read
 */
void M25P80::ReadBlock(uint32_t address, void *blockPnt, uint32_t length)
{
    uint32_t i;
    uint8_t *block = reinterpret_cast<uint8_t *> (blockPnt);
    
    IOSetCS (false);

    // Read Data Byte(s) (READ) flash command.
    SPIWrite (0x03);
    SendAddress (address);
    
    for (i = 0; i < length; ++i)
        *block++ = SPIRead();
    
    IOSetCS (true);
}

/**
 *   Write a block of memory to the flash device.
 *
 *   @param address of desired location in the range 0x00000 to 0xFFFFF (1MB)
 *   @param blockPnt pointer data block to write
 *   @param length number of bytes to write
 */
void M25P80::WriteBlock(uint32_t address, const void *blockPnt, uint32_t length)
{
    uint32_t i;
    const uint8_t *block = reinterpret_cast<const uint8_t *> (blockPnt);

    IOSetCS (false);
    // Write Enable (WREN) flash command.
    SPIWrite (0x06);
    IOSetCS (true);
    
    IOSetCS (false);
    // Page Program (PP) flash command.
    SPIWrite (0x02);
    SendAddress (address);
    
    for (i = 0; i < length; ++i) 
    {
        // Send each byte in the data block.
        SPIWrite (*block++);

        // Track the address in the flash device.
        ++address;

        // If we cross a page boundary (a page is 256 bytes) we need to stop and send the address again.
        if ((address & 0xff) == 0x00) 
        {
            IOSetCS (true);

            // Write this block of data.
            while (IsWriteInProgress());

            IOSetCS (false);
            // Write Enable (WREN) flash command.
            SPIWrite (0x06);
            IOSetCS (true);

            IOSetCS (false);
            // Page Program (PP) flash command.
            SPIWrite (0x02);
            SendAddress (address);
        } // END if
    } // END for    

    IOSetCS (true);

    // Wait for the final write operation to complete.
    while (IsWriteInProgress());
}

/** 
 *  Bulk erase the entire flash device (all locations set to 0xff).
 */
void M25P80::BulkErase()
{
    IOSetCS (false);
    // Write Enable (WREN) flash command.
    SPIWrite (0x06);
    IOSetCS (true);
	    
    IOSetCS (false);
    // Bulk Erase (BE) flash command.
    SPIWrite (0xc7);
    IOSetCS (true);
	
    while (IsWriteInProgress());
}

/** 
 * Erase the desired sector of the flash device (all locations set to 0xff).
 * 
 * @param sector number in the range 0 to 15.
 */
void M25P80::SectorErase(uint32_t sector)
{
    // Don't do anything if we have an invalid sector.
    if (sector > 15)
        return;
    
    IOSetCS (false);
    // Write Enable (WREN) flash command.
    SPIWrite (0x06);
    IOSetCS (true);
    
    IOSetCS (false);
    // Sector Erase (SE) flash command.
    SPIWrite (0xd8);
    
    SPIWrite (sector);
    SPIWrite (0x00); 
    SPIWrite (0x00);
    IOSetCS (true);

    while (IsWriteInProgress());
}

/**
 *   Write the 24-bit address to the flash device through the serial interface.  This function
 *   only controls the clock line.  The chip select must be configured before calling
 *   this function.
 *
 *   @param address 24-bit flash device address
 */
void M25P80::SendAddress(uint32_t address)
{
	SPIWrite ((address >> 16) & 0xff);
	SPIWrite ((address >> 8) & 0xff);
	SPIWrite (address & 0xff);
}

/**
 *  Read the flash chip electronic signature value.
 * 
 *  @return ES (Electronic Signature)
 */
uint32_t M25P80::ReadSignature ()
{
	uint32_t signature;
	
    IOSetCS (false);

    SPIWrite (0xab);
    SPIWrite (0x00);
    SPIWrite (0x00);
    SPIWrite (0x00);
    
    signature = SPIRead();
    
    IOSetCS (true);
    
    return signature;	
}
