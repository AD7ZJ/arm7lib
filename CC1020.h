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
 * Filename:     CC1020.h                                                  *
 *                                                                         *
 ***************************************************************************/
 
#ifndef CC1020_H
#define CC1020_H

/**
 *  @defgroup external External Peripherals
 *
 *  @{
 */

/**
 *  Controls the Texas Instruments CC1020 Low-Power RF Transceiver 
 *  for Narrowband Systems.
 */
class CC1020
{
public:
    void Enable();
    
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
    
    static CC1020 *GetInstance();
};

/** @} */

#endif  // #ifndef CC1020_H

