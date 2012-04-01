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
 * Filename:     SPI0.cpp                                                  *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

/// Reserve memory for singleton object.
static SPI0 spi0SingletonObject;

const uint32_t SSEL0 = (1 << 7);

/**
 *  Get a pointer to the SPI0 object.
 */
SPI0 *SPI0::GetInstance()
{
    return 	&spi0SingletonObject;
}

/**
 *  Enable the required pins for the SPI port and configure it for operation.
 * 
 * @param writeOnly true to disable MISO pin and leave as GPIO; otherwise false
 */
void SPI0::Enable(bool_t writeOnly)
{
    // Set the SSEL0 as HIGH output pin.
    FIO0SET = SSEL0;
    FIO0DIR |= SSEL0;
    
    // Set the pins required for the SSP controller.
    if (writeOnly)
        PINSEL0 |= ((0x01 << 8) | (0x01 << 12));
    else
        PINSEL0 |= ((0x01 << 8) | (0x01 << 10) | (0x01 << 12));

    // Set the clock counter to maximum speed.  Must be 8 or greater per the LPC21x User Manual.
    S0SPCCR = 0x08;
    
    // Configure in SPI master mode.
    S0SPCR = 0x0020;
}

/**
 *  Disable SPI and set the pins for GPIO.
 */
void SPI0::Disable()
{
    PINSEL1 &= ~((0x01 << 8) | (0x01 << 10) | (0x01 << 12));
}

/**
 *  Set the state of the CS (Chip Select) to enable/disable slave access.
 *  In some instances, another GPIO pin may control the chip select.
 * 
 *  @param state true to enable slave; otherwise false
 */
void SPI0::SetCS (bool_t state)
{
    if (state)
        FIO0SET = SSEL0;
    else
        FIO0CLR = SSEL0;
}

/**
 *  Write a single byte to the SPI port and wait for it to complete its transmission.
 * 
 *  @param value 8-bit value to write
 */
void SPI0::Write(uint8_t value)
{
    S0SPDR = value;	
    while ((S0SPSR & 0x80) == 0x00);	
}

/**
 *  Waits for and returns a single character from the SPI port.
 * 
 *  @return byte read from SPI bus
 */
uint8_t SPI0::Read()
{
    S0SPDR = 0x00;	
    while ((S0SPSR & 0x80) == 0x00);
    
    return S0SPDR;
}

