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
 * Filename:     AES.h                                                     *
 *                                                                         *
 ***************************************************************************/

#ifndef AES_H
#define AES_H

/**
 *  @defgroup library Generic Library Functions
 *
 *  @{
 */

/**
 *  AES encryption/decryption engine.
 */
class AES
{
public:
    /// Allowable key sizes.
    typedef enum
    {
        /// AES 128-bit standard.
        Key128Bits = 128,

        /// AES 192-bit standard.
        Key192Bits = 192,

        /// AES 256-bit standard.
        Key256Bits = 256
    } KEY_SIZE;

    /// Encryption/decryption mode.
    typedef enum
    {
        /// Decrypt the data set.
        Decrypt = 0,

        /// Encrypt the data set.
        Encrypt = 1
    } EncryptionMode;

    /// Number of bytes in the input and output blocks.
    static const uint32_t BlockSize = 16;

    /// Constant IV set to all zeros.
    static const uint8_t ZeroIV[BlockSize];

    void CryptCBC(EncryptionMode mode, uint32_t length, const uint8_t iv[BlockSize], const uint8_t *input, uint8_t *output);
    void CryptECB(EncryptionMode mode, uint8_t const input[BlockSize], uint8_t output[BlockSize]);
    void SetDecryptionKey(const AESKey *key);
    void SetDecryptionKey(const uint8_t *key, KEY_SIZE keysize);
    void SetEncryptionKey(const AESKey *key);
    void SetEncryptionKey(const uint8_t *key, KEY_SIZE keysize);

private:
    /// Number of rounds.
    int32_t numberOfRounds;

    /// AES round keys.
    uint32_t *roundKey;

    /// Expanded key buffer.
    uint32_t expandedKey[68];
};

/** @} */

#endif // #ifndef AES256_H

