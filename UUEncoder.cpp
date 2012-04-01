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
 * Filename:     UUEncoder.cpp                                             *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

const uint8_t UUEncoder::UUEncodeTable[] =
{
    '`', '!', '"', '#', '$', '%', '&', '\'',
    '(', ')', '*', '+', ',', '-', '.', '/',
    '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9', ':', ';', '<', '=', '>', '?',
    '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G',
    'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
    'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
    'X', 'Y', 'Z', '[', '\\',']', '^', '_'
};


/**
 *  Convert a binary block to ASCII data using the Uuencoding convention.
 */
void UUEncoder::Encode (const void *binary, char *text, uint32_t length)
{
    uint32_t data;
    const uint8_t *encode;

    encode = reinterpret_cast<const uint8_t *> (binary);

    while (length-- != 0)
    {
        // Encode byte 1.
        data = *encode++;
        *text++ = UUEncodeTable[data >> 2];

        // Encode byte 2.
        data = (data << 8) & 0x300;

        if (length-- != 0)
            data |= *encode++;

        *text++ = UUEncodeTable[data >> 4];

        // Encode byte 3.
        data = (data << 8) & 0xf00;

        if (length-- != 0)
            data |= *encode++;

        *text++ = UUEncodeTable[data >> 6];

        // Encode byte 4.
        *text++ = UUEncodeTable[data & 0x3f];
    } // END while

    *text = 0;
}

/**
 *  Convert an ASCII data string to a binary block using the Uuencoding convention.
 */
void UUEncoder::Decode (const char *text, void *binary)
{
    uint32_t data;
    uint8_t *decode;

    decode = reinterpret_cast<uint8_t *> (binary);

    while (*text != 0)
    {
        data = ConvertText(*text++) << 18;

        if (*text != 0)
            data |= ConvertText(*text++) << 12;

        if (*text != 0)
            data |= ConvertText(*text++) << 6;

        if (*text != 0)
            data |= ConvertText(*text++);

        *decode++ = data >> 16;
        *decode++ = (data >> 8) & 0x00ff;
        *decode++ = data & 0x00ff;
    } // END while
}
