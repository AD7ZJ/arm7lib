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
 * Filename:     M25P80.h                                                  *
 *                                                                         *
 ***************************************************************************/

#ifndef M25P80_H_
#define M25P80_H_

/**
 *  @defgroup external External Peripherals
 *
 *  @{
 */

/**
 *  Control the STMicroelectronics MP25P80 serial flash device.  The
 *  M25P80 is an 8Mbit device organized as 1Mbyte x 8.
 */
class M25P80
{
public:
    /**
     *   Callback to set the Chip Select control line.
     *
     *    @param state false to set line low and enable device; otherwise true
     */
    virtual void IOSetCS(bool_t state);

    /**
     *   Callback to clock and read data from the SPI bus.
     *
     *   @return 8-bit data read from SPI bus
     */
    virtual uint8_t SPIRead();

    /**
     *   Callback to clock and send data over SPI bus.
     *
     *   @param data 8-bit data to write
     */
    virtual void SPIWrite(uint8_t data);
    
    void BulkErase();
    void ReadBlock(uint32_t address, void *block, uint32_t length);
    uint32_t ReadSignature();
    void SectorErase(uint32_t sector);
    void WriteBlock(uint32_t address, const void *block, uint32_t length);
    
    static M25P80 *GetInstance();
	
private:
    bool_t IsWriteInProgress();
    void SendAddress(uint32_t address);
};

/** @} */

#endif // #ifndef M25P80_H_

