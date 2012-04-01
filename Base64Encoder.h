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
 * Filename:     Base64Encoder.h                                           *
 *                                                                         *
 ***************************************************************************/

#ifndef BASE64_ENCODER_H
#define BASE64_ENCODER_H

/**
 *  @defgroup library Generic Library Functions
 *
 *  @{
 */

/**
 *  Used to encode arbitrary octet sequences into a form that satisfies
 *  the rules of 7-bit ASCII.
 */
class Base64Encoder
{
public:
    static void Decode (const char *text, void *binary);
    static void Encode (const void *binary, char *text, uint32_t length);

private:
    /// Lookup table that converts 6-bit number to ASCII equivalent.
    static const uint8_t B64EncodeTable[64];

    /// Lookup table that converts ASCII text to 6-bit number.
    static const uint8_t B64DecoderTable[256];
};

/** @} */

#endif  // #ifndef BASE64_ENCODER_H
