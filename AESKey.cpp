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
 * Filename:     AESKey.cpp                                                *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

AESKey::AESKey()
{
    memset(this->key, 0x00, sizeof(this->key));
}

/**
 * Get the AES-256 key.
 */
const uint8_t *AESKey::Get() const
{
    return this->key;
}

/**
 * Set the AES-256 key with the 32-byte key.
 */
void AESKey::Set(const uint8_t key[KeySize])
{
    memcpy(this->key, key, sizeof(this->key));
}
