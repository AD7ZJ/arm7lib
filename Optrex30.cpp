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
 * Filename:     Optrex30.cpp                                              *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

/**
 * Initialize the display controller.
 */
void Optrex30::Enable()
{
    ChipSelect(true);

    Reset(false);
    SystemControl::Sleep(5);
    Reset(true);
    SystemControl::Sleep(1);
}

/**
 * Read the 16-bit RGB pixel value at the current display address.
 *
 * @return 16-bit RGB pixel value
 */
uint32_t Optrex30::ReadPixel()
{
}

/**
 * Set the display controller to accept a stream of RGB display data.  The
 * StopWrite method must be called when the data write is complete.
 */
void Optrex30::StartWrite()
{
}

/**
 * Stop the RGB display data stream.
 */
void Optrex30::StopWrite()
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
void Optrex30::Window(uint32_t x, uint32_t y, uint32_t sx, uint32_t sy)
{
}

/**
 * Write the 16-bit RGB pixel value at the current display address.
 *
 * @param rgb 16-bit RGB pixel value
 */
void Optrex30::WritePixel(uint32_t rgb)
{
}

/**
 * Write a block of binary data to the controller.
 *
 * @param buffer pointer to 1 or more bytes to write
 * @param length number of bytes to write to the controller
 */
void Optrex30::WriteBlock(const uint8_t *buffer, uint32_t length)
{
}
