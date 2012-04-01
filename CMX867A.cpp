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
 * Filename:     CMX867A.cpp                                               *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

/// Reserve memory for the singleton object.
static CMX867A cmx867ASingletonObject;

/**
 * Get a pointer to the CMX867 object.
 */
CMX867A *CMX867A::GetInstance()
{
	return 	&cmx867ASingletonObject;
}

/**
 * Initialize the CMX867A MODEM chip.
 */
void CMX867A::Enable()
{
	// Configure as 
	IOSetCS (false);

	SPIWrite (0xe0);
	SPIWrite (0x01);	
	SPIWrite (0x00);

	IOSetCS (true);			
			
	IOSetCS (false);

	SPIWrite (0xe1);
	SPIWrite (0x30);
	SPIWrite (0x1c);

	IOSetCS (true);

	SendByte(0x00);
}

/**
 * Transmit the 8-bit value LSB first through the UART.
 * 
 * @param value 8-bit value to send
 */
void CMX867A::SendByte (uint8_t value)
{
	// Write to UART command 0xe3.
	IOSetCS (false);

	SPIWrite (0xe3);
	SPIWrite (value);

	IOSetCS (true);	
}

/**
 * Get the 16-bit status word from the CMX867A.
 * 
 * @return 16-bit status word
 */
uint32_t CMX867A::Status()
{
    uint32_t status;
	
	// Read status command 0xe6.
	IOSetCS (false);

	SPIWrite (0xe6);
	
	status = SPIRead() << 8;	
	status |= SPIRead();

	IOSetCS (true);	
	
	return status;	
}

/**
 * Indicates if the transmit buffer is empty and ready for a data byte.
 * 
 * @return true a new value should be loaded in the transmit buffer; otherwise false
 */
bool_t CMX867A::IsTxDataReady()
{
    return ((Status() & StatusTxDataReady) == StatusTxDataReady ? true : false);
}
