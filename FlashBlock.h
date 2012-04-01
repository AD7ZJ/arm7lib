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
 * Filename:     FlashBlock.h                                              *
 *                                                                         *
 ***************************************************************************/

#ifndef FLASH_BLOCK_H
#define FLASH_BLOCK_H

/**
 *  @defgroup library Generic Library Functions
 *
 *  @{
 */

/**
 * Manages a block of memory within the processor flash memory area.  The
 * block is wrapped with a magic number, block length, and CRC-32.
 */
class FlashBlock
{
public:
    FlashBlock(uint32_t magicNumber, uint32_t flashAddress);

    void Erase();
    const void *Get();
    bool_t IsValid();
    void Write (const void *buffer, uint32_t length);

    /// Number of bytes in flash block area.
    static const uint32_t FlashBlockSize = 256;

private:
    /// Starting address of the flash block.
    uint32_t flashAddress;

    /// Magic number used to protect and validate block.
    uint32_t magicNumber;
};

/** @} */

#endif // #ifndef FLASH_BLOCK_H
