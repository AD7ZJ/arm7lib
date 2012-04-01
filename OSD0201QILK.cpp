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
 * Filename:     OSD0201QILK.cpp                                           *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

/**
 * Initialize the display controller.
 */
void OSD0201QILK::Enable()
{
    ChipSelect(true);

    Reset(false);
    SystemControl::Sleep(500);

    Reset(true);
    SystemControl::Sleep(10);

    // Select the 8-bit interface mode.
    DisplayData(false);

    ChipSelect (false);
    Write (0x24);
    ChipSelect (true);

    // Set RGB Interface control.
    WriteRegister (0x02, 0x0000);

    // Set entry mode for 262K colors, auto increment address pointer.
    WriteRegister (0x03, 0x4130);

    // Standby off.
    WriteRegister (0x10, 0x0000);

    // Required delay to allow display converts to come up.
    SystemControl::Sleep(100);

    WriteRegister (0x70, 0x2900);
    WriteRegister (0x71, 0x2A00);
    WriteRegister (0x72, 0x3700);
    WriteRegister (0x73, 0x1912);
    WriteRegister (0x74, 0x1B0D);
    WriteRegister (0x75, 0x2014);
    WriteRegister (0x76, 0x1812);
    WriteRegister (0x77, 0x2118);
    WriteRegister (0x78, 0x2111);


    // Set the window size.
    Window (0, 0, this->sizeX, this->sizeY);

    // Clear the screen.
    StartWrite();

    uint32_t pixelCount = this->sizeX * this->sizeY;

    while (pixelCount-- != 0)
        WritePixel(GUI::ColorBlack);

    StopWrite();

    // Turn on the ARVDD/ARVSS supplies.
    PowerConverter(true);

    // Allow the converters time to stabilize.
    SystemControl::Sleep(32);

    // Display on.
    WriteRegister (0x05, 0x0001);
}

/**
 * Read the 16-bit RGB pixel value at the current display address.
 *
 * @return 16-bit RGB pixel value
 */
uint32_t OSD0201QILK::ReadPixel()
{
    return 0;
}

/**
 * Set the display controller to accept a stream of RGB display data.  The
 * StopWrite method must be called when the data write is complete.
 */
void OSD0201QILK::StartWrite()
{
    DisplayData(false);
    ChipSelect(false);

    Write (0x22);

    DisplayData(true);
}

/**
 * Stop the RGB display data stream.
 */
void OSD0201QILK::StopWrite()
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
void OSD0201QILK::Window(uint32_t x, uint32_t y, uint32_t sx, uint32_t sy)
{
    // Vertical start address.
    WriteRegister (0x35, y);

    // Vertical end address.
    WriteRegister (0x36, y + sy - 1);

    // Horizontal address range.
    WriteRegister (0x37, ((x + 0x20) << 8) | (x + sx + 0x20 - 1));

    // X start address.
    WriteRegister (0x20, x + 0x20);

    // Y start address.
    WriteRegister (0x21, y);
}

/**
 * Write the 16-bit RGB pixel value at the current display address.
 *
 * @param rgb 16-bit RGB pixel value
 */
void OSD0201QILK::WritePixel(uint32_t rgb)
{
    Write ((rgb >> 8) & 0xfc);
    Write ((rgb >> 3) & 0xfc);
    Write (rgb << 3);
}

/**
 * Write the 16-bit value to the specified 8-bit register.
 *
 * @param reg 8-bit control register
 * @param value 16-bit value to write
 */
void OSD0201QILK::WriteRegister(uint32_t reg, uint32_t value)
{
    DisplayData(false);

    ChipSelect (false);
    Write (reg);

    DisplayData(true);
    Write (value >> 8);
    Write(value & 0xff);
    ChipSelect (true);
}

