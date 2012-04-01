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
 * Filename:     DAC.cpp                                                   *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"
 
/// Reserve memory for singleton object.
static DAC dacSingletonObject;

const uint32_t DACPinSelect = 0x80000;

/**
 * Get a pointer to the DAC singleton object.
 */
DAC *DAC::GetInstance()
{
	return &dacSingletonObject;
}

/**
 *   Constructor.
 */
DAC::DAC()
{
	settlingTimeMask = 0x00000;
}

/**
 *  Set the DAC setling time.  The slower setting allows for less
 *  power consumption, while the higher setting allow for higher
 *  bandwidth control.
 *
 *  @param settlingTime enumerated type that specifies the DAC setting time
 */
void DAC::SettlingTime (SettlingTimeBias settlingTime)
{
	if (settlingTime == SettlingTime1uS)
		settlingTimeMask = 0x00000;
	else
		settlingTimeMask = 0x10000;		
}

/**
 *   Set the DAC output in the range 0 to 1023.
 *
 *   @param dac output value
 */
void DAC::Set (uint32_t dac)
{
	DACR = settlingTimeMask | ((dac & 0x03ff) << 6);
}

/**
 *   Enable the required pins for the DAC.
 */
void DAC::Enable()
{
	PINSEL1 |= DACPinSelect;
}
