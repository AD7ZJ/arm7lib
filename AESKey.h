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
 * Filename:     AESKey.h                                                  *
 *                                                                         *
 ***************************************************************************/

#ifndef AESKEY_H
#define AESKEY_H

/**
 *  @defgroup library Generic Library Functions
 *
 *  @{
 */

/**
 *  Manages a single AES-256 key.
 */
class AESKey
{
public:
    AESKey();

    /// Key size in bytes.
    static const uint32_t KeySize = 32;

    const uint8_t *Get() const;
    void Set(const uint8_t key[KeySize]);

private:
    /// Buffer to store the key.
    uint8_t key[KeySize];
};

/** @} */

#endif // #ifndef AESKEY_H

