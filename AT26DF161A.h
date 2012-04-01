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
 * Filename:     AT26DF161A.h                                              *
 *                                                                         *
 ***************************************************************************/

#ifndef AT26DF161A_H
#define AT26DF161A_H

/**
 *  @defgroup external External Peripherals
 *
 *  @{
 */

/**
 *  Control the Atmel AT26DF161A serial flash device.  The
 *  AT26DF161A is an 16Mbit device organized as 2Mbyte x 8.
 */
class AT26DF161A
{
public:
    /**
     *  Callback to set the Chip Select control line.
     *
     *  @param state false to set line low and enable device; otherwise true
     */
    virtual void IOSetCS(bool_t state);

    /**
     *  Callback to clock and read data from the SPI bus.
     *
     *  @return 8-bit data read from SPI bus
     */
    virtual uint8_t SPIRead();

    /**
     *  Callback to clock and send data over SPI bus.
     *
     *  @param data 8-bit data to write
     */
    virtual void SPIWrite(uint8_t data);

    void BlockErase(uint32_t address);
    void BulkErase();
    void ReadBlock(uint32_t address, void *block, uint32_t length);
    uint32_t ReadSignature();
    void WriteBlock(uint32_t address, const void *block, uint32_t length);

    static AT26DF161A *GetInstance();

private:
    void ClearGlobalProtect();
    bool_t IsWriteInProgress();
    void SendAddress(uint32_t address);
};

/** @} */

#endif // #ifndef AT26DF161A_H

