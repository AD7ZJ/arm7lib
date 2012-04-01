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
 * Filename:     CMX867A.h                                                 *
 *                                                                         *
 ***************************************************************************/
 
#ifndef CMX867A_H
#define CMX867A_H

/**
 *  @defgroup external External Peripherals
 *
 *  @{
 */

/**
 *   Control the CML Microcircuits CMX867A Low Power V.22 MODEM.
 *   The CMX867A is a multi-standard modem for use in telephone based 
 *   information and telemetry systems.
 */
class CMX867A
{
public:
    void Enable();
    bool_t IsTxDataReady();
    void SendByte (uint8_t value);
    uint32_t Status();
    
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
    
    static CMX867A *GetInstance();
    
    /// Status Register - Transmit Data Ready flag.
    static const uint32_t StatusTxDataReady = (1 << 12);    
};

/** @} */

#endif  // #ifndef CMX867A_H

