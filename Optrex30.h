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
 * Filename:     Optrex30.h                                                *
 *                                                                         *
 ***************************************************************************/

#ifndef OPTREX30_H
#define OPTREX30_H

/**
 *  @defgroup external External Peripherals
 *
 *  @{
 */

/**
 * Hardware specific control methods for the Optrex 3.0" TFT LCD
 * part number T-55149GD030J-MLW-AJN.
 */
class Optrex30 : public GUIBase
{
public:
	Optrex30() : GUIBase(240, 400) {};

	void Enable();
	uint32_t ReadPixel();
	void StartWrite();
	void StopWrite();
	void Window (uint32_t x, uint32_t y, uint32_t sx, uint32_t sy);
	void WritePixel(uint32_t rgb);

    /**
     * Callback to set the Chip Select control line.
     *
     * @param state false to set line low and enable device; otherwise true
     */
	virtual void ChipSelect(bool_t state) = 0;

    /**
     * Callback to set the Display Data control line.  The display data control
     * line selects the control or display memory.
     *
     * @param state false to set line low; otherwise true
     */
	virtual void DisplayData(bool_t state) = 0;

    /**
     * Callback to set the reset control line.
     *
     * @param state false to set the reset line low and hold the device in reset; otherwise true
     */
	virtual void Reset(bool_t state) = 0;

    /**
     * Callback to write and clock 8-bit data to LCD controller.
     *
     * @param value 8-bit data to write
     */
	virtual void Write(uint32_t value) = 0;

private:
	void WriteBlock(const uint8_t *buffer, uint32_t length);
};

/** @} */

#endif // #ifndef OPTREX30_H
