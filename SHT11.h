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
 * Filename:     SHT11.h                                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef SHT11_H
#define SHT11_H

/**
 *  @defgroup external External Peripherals
 *
 *  @{
 */

/**
 *  Control the Sensirion SHT1x / SHT7x Humidity/Temperature sensors.
 */
class SHT11
{
public:
    void Enable();
    int32_t ReadTemp();
    uint32_t ReadHum();

    /**
     *   Callback to set the clock control line.
     *
     *   @param state true to set high; otherwise false
     */
    virtual void IOSetClock(bool_t state);

    /**
     *   Callback to set the data control line.
     *
     *   @param state true to set high; otherwise false
     */
    virtual void IOSetData(bool_t state);

    /**
     *   Callback to get the data control line state.
     *
     *   @return true if line is high; otherwise false
     */
    virtual bool_t IOGetData();

    /**
     *   Callback to set the data control line direction.
     *
     *   @param state true to set as an output; otherwise false for an input
     */
    virtual void IOSetDataDirection(bool_t state);

    static SHT11 *GetInstance();

private:
    uint32_t CRC (uint32_t crc, uint32_t value);
    uint32_t ReadAckByte(bool_t ackFlag);
    uint32_t ReverseBits (uint32_t value);
    uint32_t SendCommand (uint32_t command);
    void StrobeClock();
    void TransmitStart();

    static const uint8_t CRCTable[256];

    static const uint16_t HumidityTable[100];
};

/** @} */

#endif // #ifndef SHT11_H
