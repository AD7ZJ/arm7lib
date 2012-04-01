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
 * Filename:     SPI1.cpp                                                  *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

/// Reserve memory for the singleton object.
static SPI1 spi1SingletonObject;

/**
 * Get a pointer to the base class of the UART-1 instance.
 */
SPI1 *SPI1::GetInstance()
{
    return 	&spi1SingletonObject;
}

/**
 * Enable the required pins for the SPI port and configure it for operation.
 */
void SPI1::Enable(uint32_t clockRate, DataSize dataSize, DataClockPhase dataClockPhase)
{
    uint32_t value;
    
    // Set the SSEL1 as HIGH output pin.
    FIO0SET = SSEL1;
    FIO0DIR |= SSEL1;
    
    // Set the pins required for the SSP controller.
    PINSEL1 |= ((0x02 << 2) | (0x02 << 4) | (0x02 << 6));
    
    // Calculate the SCR register value.
    value = (SystemControl::GetInstance()->GetPClock() / clockRate) >> 1;
    
    // Remove +1 term added to calculation if we have head room left.
    if (value > 0)
        --value;
    
    // Shift the SCR value to bits 15:8 and select 8-bit transfer.
    value = (value << 8) | static_cast <uint32_t> (dataSize);
    
    // Set the bits for the data/clock phase.
    if (dataClockPhase == CPOL1_CPHA0 || dataClockPhase == CPOL1_CPHA1)
        value |= SSPCR0_CPOL;
    
    if (dataClockPhase == CPOL0_CPHA1 || dataClockPhase == CPOL1_CPHA1)
        value |= SSPCR0_CPHA;

    // Configure the controller.
    SSPCR0 = value;
    
    // Set the clock prescale register to the minimum value.
    SSPCPSR = 0x02;

    // Enable the SSP controller. 
    SSPCR1 = 0x02;
}

/**
 * Disable SPI and set the pins for GPIO.
 */
void SPI1::Disable()
{
    PINSEL1 &= ~((0x02 << 2) | (0x02 << 4) | (0x02 << 6));
}

/**
 *  Set the state of the CS (Chip Select) to enable/disable slave access.
 *  In some instances, another GPIO pin may control the chip select.
 * 
 *  @param state true to enable slave; otherwise false
 */
void SPI1::SetCS (bool_t state)
{
    if (state)
        FIO0SET = SSEL1;
    else
        FIO0CLR = SSEL1;
}

/**
 * Write a data value to the SPI port.
 * 
 * @param value value to write
 * 
 * @return read back from FIFO
 */
uint32_t SPI1::Write (uint32_t value)
{
    while ( !(SSPSR & SSPSR_TNF) );
    SSPDR = static_cast <uint16_t> (value);	
    while ( !(SSPSR & SSPSR_RNE) );
    
    return static_cast <uint32_t> (SSPDR);
}

/**
 * Reads and returns a single character from the SPI port.
 * 
 * @return 8-bit character from UART
 */
uint32_t SPI1::Read()
{
    // Dummy write to generate the clock to get the byte.
    SSPDR = 0x00;
    
    // Wait for the transfer to end.
    while ( SSPSR & SSPSR_BSY );
    
    return static_cast <uint32_t> (SSPDR);
}

