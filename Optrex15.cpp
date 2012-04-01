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
 * Filename:     Optrex15.cpp                                              *
 *                                                                         *
 ***************************************************************************/
 
#include "armlib.h"

/**
 * Initialize the display controller.
 */
void Optrex15::Enable()
{
    ChipSelect(true);
    
    Reset(false);        
    SystemControl::Sleep(2);
    Reset(true);  
    SystemControl::Sleep(2);
    
    WriteRegister (0x00, 0x0000);
    WriteRegister (0x00, 0x0000);
    WriteRegister (0x00, 0x0000);
    WriteRegister (0x00, 0x0000);
    WriteRegister (0x00, 0x0001);
    
    SystemControl::Sleep(10);
    
    WriteRegister (0x07, 0x0001);
    WriteRegister (0x17, 0x0001);
    WriteRegister (0x10, 0x24c0);
    WriteRegister (0x11, 0x0001);
    WriteRegister (0x12, 0x001a);
    WriteRegister (0x13, 0x0828);
    WriteRegister (0x12, 0x003a);
    
    SystemControl::Sleep(150);
    
    WriteRegister (0x01, 0x0110);
    WriteRegister (0x03, 0x1030);
    WriteRegister (0x08, 0x0404);
    WriteRegister (0x0b, 0x000a);
    WriteRegister (0x0d, 0x5559);
    WriteRegister (0x15, 0x0000);
    WriteRegister (0x30, 0x0000);
    WriteRegister (0x31, 0x0000);
    WriteRegister (0x32, 0x0303);
    WriteRegister (0x33, 0x0100);
    WriteRegister (0x34, 0x0404);
    WriteRegister (0x35, 0x0707);
    WriteRegister (0x36, 0x0707);
    WriteRegister (0x37, 0x0001);
    WriteRegister (0x38, 0x1f04);
    WriteRegister (0x39, 0x040f);
    WriteRegister (0x40, 0x0000);
    WriteRegister (0x41, 0x0000);
    WriteRegister (0x42, 0x8300);
    WriteRegister (0x44, 0xaf00);
    WriteRegister (0x45, 0x8300);
    WriteRegister (0x21, 0x0000);
    
    WriteRegister (0x02, 0x0600);
    WriteRegister (0x07, 0x0021);
    SystemControl::Sleep(1);
    
    
    WriteRegister (0x07, 0x0072);
    SystemControl::Sleep(100);
    
    
    WriteRegister (0x02, 0x0700);
    WriteRegister (0x07, 0x0077);
}

/**
 * Read the 16-bit RGB pixel value at the current display address.
 * 
 * @return 16-bit RGB pixel value
 */
uint32_t Optrex15::ReadPixel()
{
	return 0;
}

/**
 * Set the display controller to accept a stream of RGB display data.  The
 * StopWrite method must be called when the data write is complete.
 */
void Optrex15::StartWrite()
{
    ChipSelect(false);
    DisplayData(false);
    
	Write (0x00);
	Write (0x22);

	DisplayData(true); 
}

/**
 * Stop the RGB display data stream.
 */
void Optrex15::StopWrite()
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
void Optrex15::Window(uint32_t x, uint32_t y, uint32_t sx, uint32_t sy)
{
    WriteRegister (0x44, ((x + sx - 1) << 8) | x);
    WriteRegister (0x45, ((y + sy - 1) << 8) | y);
    WriteRegister (0x21, x  | (y << 8));
}

/**
 * Write the 16-bit RGB pixel value at the current display address.
 * 
 * @param rgb 16-bit RGB pixel value
 */
void Optrex15::WritePixel(uint32_t rgb)
{
    Write (rgb >> 8);
    Write (rgb & 0x00ff);
}

/**
 * Write the 16-bit value to the specified 8-bit register.
 * 
 * @param reg 8-bit control register
 * @param value 16-bit value to write
 */
void Optrex15::WriteRegister(uint32_t reg, uint32_t value)
{
    DisplayData(false);
    
	ChipSelect (false);
	Write (0);
	Write (reg);
	
    DisplayData(true);
	Write (value >> 8);
	Write(value & 0xff);
	ChipSelect (true);
}

