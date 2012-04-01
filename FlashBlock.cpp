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
 * Filename:     FlashBlock.cpp                                            *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

/**
 * Object that represents the contents of the flash buffer block.
 */
class FlashBuffer
{
public:
    /// Constructor.
    FlashBuffer() { std::memset (this, 0xff, sizeof(FlashBuffer)); };

    /// Calculate the CRC-32 of the flash block header and contents.
    uint32_t CRC() { return CRC32::Calculate(this, sizeof(FlashBuffer) - sizeof(uint32_t)); };

    /// Unique 32-bit number to identify the start of the flash block.
    uint32_t magicNumber;

    /// Number of data bytes in the block.
    uint32_t length;

    /// Storage area of the flash data not include the magic number, length, and CRC-32.
    uint8_t data[FlashBlock::FlashBlockSize - (3 * sizeof(uint32_t))];

    /// Calculated CRC-32 of the flash block.
    uint32_t crc32;
};

/**
 * Constructor.
 *
 * @param magicNumber unique 32-bit number used to identify the start of the flash block
 * @param flashAddress address of flash memory block to read/write
 */
FlashBlock::FlashBlock(uint32_t magicNumber, uint32_t flashAddress)
{
    // Save the values for later use.
    this->magicNumber = magicNumber;
    this->flashAddress = flashAddress;
}

/**
 * Get a pointer to the data stored in the flash block area.
 *
 * @return void pointer that may be cast to the desired data block
 */
const void *FlashBlock::Get()
{
    return reinterpret_cast<const void *> (this->flashAddress + (2 * sizeof(uint32_t)));
}

/**
 * Validate the contents of the flash block by checking the magic number and CRC-32.
 *
 * @return true if block is valid; otherwise false
 */
bool_t FlashBlock::IsValid()
{
    FlashBuffer *flash = reinterpret_cast<FlashBuffer *> (this->flashAddress);

    if (flash->magicNumber != this->magicNumber)
        return false;

    if (flash->crc32 != flash->CRC())
        return false;

    return true;
}

/**
 * Write the contents of the buffer in flash memory.
 *
 * @param buffer pointer to data buffer
 * @param length number of bytes in the data buffer
 */
void FlashBlock::Write(const void *buffer, uint32_t length)
{
    FlashBuffer flash;

    // Fill in the header information.
    flash.magicNumber = this->magicNumber;
    flash.length = length;

    // Clear the flash data buffer in case our data block isn't as big as required.
    std::memset(flash.data, 0xff, sizeof(flash.data));

    // Copy the data to the flash buffer.
    std::memcpy(flash.data, buffer, length);

    // Calculate the CRC-32.
    flash.crc32 = flash.CRC();

    // Finally erase and write flash.
    IAP::Erase (this->flashAddress, FlashBlockSize);
    IAP::Write (this->flashAddress, FlashBlockSize, &flash);
}

/**
 * Erase the flash block contents.
 */
void FlashBlock::Erase()
{
    IAP::Erase (this->flashAddress, FlashBlockSize);
}

