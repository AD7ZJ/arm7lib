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
 * Filename:     Optrex19.cpp                                              *
 *                                                                         *
 ***************************************************************************/
 
#include "armlib.h"

static const uint8_t VOSCOn[] = { 0x96 };
static const uint8_t DisplaySet[] = { 0xca, 0x00, 0x3a, 0x00, 0x11, 0xdb, 0x00, 0x03, 0x02, 0x00 };
static const uint8_t DisplaySetTiming[] = { 0xa1, 0x00, 0x37, 0x01, 0x34, 0x00, 0x13, 0x09 };
static const uint8_t DataSet[] = { 0xbc, 0x00 };
static const uint8_t StartLine[] = { 0xab, 0x00 };
static const uint8_t DataIntefaceSet[] = { 0x31, 0x00, 0x00 };
static const uint8_t ColorModeSet[] = { 0x8b, 0x00, 0x11, 0x44, 0x77 };
static const uint8_t LineScanMode[] = { 0x6f, 0x00, 0x00, 0xdb };
static const uint8_t WaveformControlSet[] = { 0x8c, 0x00, 0x00 };
static const uint8_t EVRSet[] = { 0x20, 0x17, 0x1b, 0x15, 0x00, 0x00, 0x0d, 0x08, 0x00 };
static const uint8_t YControlSet[] = { 0x22, 0x04, 0x05, 0x44, 0x43, 0x00, 0x00 };
static const uint8_t PowerControlSet[] = { 0x21, 0x11, 0x11, 0x0f, 0x19, 0x0d, 0x00, 0x33, 0xff, 0x03, 0xff, 0x03, 0x11, 0x34 };
static const uint8_t SleepOut[] = { 0x94 };
static const uint8_t StartAddressSet[] = { 0x15, 0x00, 0x00 };
static const uint8_t EndAddressSet[] = { 0x75, 0xaf, 0xdb };
static const uint8_t DisplayOn[] = { 0xaf };

/**
 * Initialize the display controller.
 */
void Optrex19::Enable()
{
    ChipSelect(true);
    
    Reset(false);        
    SystemControl::Sleep(5);
    Reset(true);  
    SystemControl::Sleep(1);
    
    WriteBlock (VOSCOn, sizeof(VOSCOn));    
    WriteBlock (DisplaySet, sizeof(DisplaySet));    
    WriteBlock (DisplaySetTiming, sizeof(DisplaySetTiming));    
    WriteBlock (DataSet, sizeof(DataSet));    
    WriteBlock (StartLine, sizeof(StartLine));    
    WriteBlock (DataIntefaceSet, sizeof(DataIntefaceSet));    
    WriteBlock (ColorModeSet, sizeof(ColorModeSet));    
    WriteBlock (WaveformControlSet, sizeof(WaveformControlSet));
    WriteBlock (EVRSet, sizeof(EVRSet));
    WriteBlock (YControlSet, sizeof(YControlSet));
    WriteBlock (PowerControlSet, sizeof(PowerControlSet));
    WriteBlock (SleepOut, sizeof(SleepOut));
    WriteBlock (StartAddressSet, sizeof(StartAddressSet));
    WriteBlock (EndAddressSet, sizeof(EndAddressSet));
    
    WriteBlock (DisplayOn, sizeof(DisplayOn));
}

/**
 * Read the 16-bit RGB pixel value at the current display address.
 * 
 * @return 16-bit RGB pixel value
 */
uint32_t Optrex19::ReadPixel()
{
	return 0;
}

/**
 * Set the display controller to accept a stream of RGB display data.  The
 * StopWrite method must be called when the data write is complete.
 */
void Optrex19::StartWrite()
{
    ChipSelect(false);
    DisplayData(false);

	Write (0x5c);
    
    DisplayData(true);  
}

/**
 * Stop the RGB display data stream.
 */
void Optrex19::StopWrite()
{
    ChipSelect(true); 
}

/**
 * Set the display window area with a upper, left-hand corner at (x, y) 
 * that is sx pixels wide and sy pixels high.
 * 
 * @param x upper left hand X coordinate window position
 * @param y upper left hand Y coordinate window position
 * @param sx width of window in pixels
 * @param sy height of window in pixels
 */
void Optrex19::Window(uint32_t x, uint32_t y, uint32_t sx, uint32_t sy)
{
    uint8_t SetStart[] = { 0x15, x, y };
    uint8_t SetEnd[] = { 0x75, x + sx - 1, y + sy - 1 };
    
    WriteBlock (SetStart, sizeof(SetStart));
    WriteBlock (SetEnd, sizeof(SetEnd));
}

/**
 * Write the 16-bit RGB pixel value at the current display address.
 * 
 * @param rgb 16-bit RGB pixel value
 */
void Optrex19::WritePixel(uint32_t rgb)
{
    Write (rgb >> 8);
    Write (rgb & 0x00ff);
}

/**
 * Write a block of binary data to the controller.
 * 
 * @param buffer pointer to 1 or more bytes to write
 * @param length number of bytes to write to the controller
 */
void Optrex19::WriteBlock(const uint8_t *buffer, uint32_t length)
{
    uint32_t i;
    
	ChipSelect (false);
	
	for (i = 0; i < length; ++i)
	{
	    DisplayData((i == 0) ? false : true);

	    Write(buffer[i]);
	} // END for

	ChipSelect (true);
}
