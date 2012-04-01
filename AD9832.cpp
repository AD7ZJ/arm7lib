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
 * Filename:     AD9832.cpp                                                *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

/// Number of digits in DDS frequency to FTW conversion.
const uint32_t DDSFreqToFTWDigits = 9;

/// Array of multiplication factors used to convert frequency to the FTW.
const uint32_t DDSMult[2] [DDSFreqToFTWDigits] = 
{ 
    { 174, 9, 2, 2, 8, 1, 3, 2, 9 },
    { 171, 7, 9, 8, 6, 9, 1, 8, 4 } 
};

/// Array of divisors used to convert frequency to the FTW.
const uint32_t DDSDivisor[DDSFreqToFTWDigits - 1] = { 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000 };

/// Reserve memory for singleton object.
static AD9832 ad9832SingletonObject;

/**
 * Constructor.
 */
AD9832::AD9832()
{
    this->referenceFrequency = Freq25000000Hz;
}

/**
 *  Get a pointer to the SPI0 object.
 */
AD9832 *AD9832::GetInstance()
{
    return  &ad9832SingletonObject;
}

/**
 *   Initialize the DDS regsiters and RAM.
 */
void AD9832::Enable()
{
    // Set default I/O for the DDS.
    IOSetCS (true);
    IOSetProfileSelect (Profile0);
    
    SetMode (Sleep);
    
    // Set SYNC to 1 and SELSRC to 0.
    WriteRegister (0xa000);
}

/**
 * Write a 16-bit control register in the AD9832.
 * 
 * @param data 16-bit data to write
 */
void AD9832::WriteRegister (uint32_t data)
{
    IOSetCS (false); 
    
    SPIWrite ((data >>8) & 0x00ff);
    SPIWrite (data & 0xff);
    
    IOSetCS (true);
}

/**
 *  Set the DDS frequency.
 *
 *  @param freq frequency in Hertz
 *
 */
void AD9832::SetFreq(uint32_t freq)
{
    uint32_t i, ftw;
    
    // To avoid rounding errors with floating point math, we do a long multiply on the data.
    ftw = freq * DDSMult[this->referenceFrequency][0];
    
    for (i = 0; i < DDSFreqToFTWDigits - 1; ++i)
        ftw += (freq * DDSMult[this->referenceFrequency][i+1]) / DDSDivisor[i];
    
    SetFTW (ftw);
}

/**
 * Set the DDS operational mode.
 * 
 * @param mode specifies the desired mode
 */
void AD9832::SetMode(DDSMode mode)
{
    switch (mode)
    {
        case Sleep:
            WriteRegister (0xf800);
            break;
            
        case PowerOn:
            WriteRegister (0xc000);
            break;
    } // END switch
}

/**
 *  Set DDS frequency tuning word.  The output frequency is equal to MClk * (ftw / 2 ^ 32).
 *
 *  @param ftw Frequency Tuning Word
 */
void AD9832::SetFTW (uint32_t ftw)
{
    // Write FREQ0 8-bit defer and 16-bit registers.
    WriteRegister (0x3300 | ((ftw >> 24) & 0xff));
    WriteRegister (0x2200 | ((ftw >> 16) & 0xff));
    WriteRegister (0x3100 | ((ftw >> 8) & 0xff));
    WriteRegister (0x2000 | (ftw & 0xff));
}

/**
 * Set the reference clock frequency.
 * 
 * @param referenceFrequency reference clock value
 */
void AD9832::SetReferenceFrequency (ReferenceFrequency referenceFrequency)
{
    this->referenceFrequency = referenceFrequency;    
}
