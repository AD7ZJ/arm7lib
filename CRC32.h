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
 * Filename:     CRC32.h                                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef CRC32_H
#define CRC32_H

/**
 *  @defgroup library Generic Library Functions
 *
 *  @{
 */

/**
 *  Calculate the CRC-32 CCITT of a binary data block.
 */
class CRC32
{
public:
    static uint32_t Calculate(const void *buffer, uint32_t length);

private:
    static const uint32_t CRCTable[256];

};

/** @} */

#endif // #ifndef CRC32_H
