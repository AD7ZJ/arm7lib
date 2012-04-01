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
 * Filename:     UUEncoder.h                                               *
 *                                                                         *
 ***************************************************************************/

#ifndef UUENCODER_H
#define UUENCODER_H

/**
 *  @defgroup library Generic Library Functions
 *
 *  @{
 */

/**
 *  Provides coder and decoder Uuencoding functions.  Uuencoding is a
 *  form of binary-to-text encoding that originated in the Unix program
 *  uuencode, for encoding binary data for transmission over the uucp
 *  mail system.
 */
class UUEncoder
{
public:
    static void Decode (const char *text, void *binary);
    static void Encode (const void *binary, char *text, uint32_t length);

private:
    /// Lookup table that converts 6-bit number to ASCII equivalent.
    static const uint8_t UUEncodeTable[64];

    /// Convert ASCII text to a 6-bit number.
    static inline uint32_t ConvertText(char text) { return (text - ' ') & 0x3f; };
};

/** @} */

#endif  // #ifndef UUENCODER_H
