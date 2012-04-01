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
 * Filename:     GUIBase.h                                                 *
 *                                                                         *
 ***************************************************************************/

#ifndef GUIBASE_H
#define GUIBASE_H

/**
 *  @defgroup library Generic Library Functions
 *
 *  @{
 */

/**
 * GUI engine base class that contains primitive methods for each LCD controller.
 * Each controller will implement these routines.  The routines are called by
 * higher level GUI methods.
 */
class GUIBase
{
public:
	GUIBase(uint32_t sizeX, uint32_t sizeY);

	/**
	 * Callback to initialize the display controller.
	 */
	virtual void Enable() = 0;

	/**
	 * Callback to read the 16-bit RGB pixel value at the current display address.
	 *
	 * @return 16-bit RGB pixel value
	 */
	virtual uint32_t ReadPixel() = 0;

	/**
	 * Callback to set the display controller to accept a stream of RGB display data.
	 * The StopWrite method must be called when the data write is complete.
	 */
	virtual void StartWrite() = 0;

	/**
	 * Callback to stop the RGB display data stream.
	 */
	virtual void StopWrite() = 0;

	/**
	 * Callback to set the display window area to the box bounded by (x, y) to (x + sx, y + sy).
	 *
	 * @param x upper left hand X coordinate window position
	 * @param y upper left hand Y coordinate window position
	 * @param sx width of window in pixels
	 * @param sy height of window in pixels
	 */
	virtual void Window(uint32_t x, uint32_t y, uint32_t sx, uint32_t sy) = 0;

	/**
	 * Callback to write the 16-bit RGB pixel value at the current display address.
	 *
	 * @param rgb 16-bit RGB pixel value
	 */
	virtual void WritePixel(uint32_t rgb) = 0;

	/// Display width in pixels.
	uint32_t sizeX;

	/// Display height in pixels.
	uint32_t sizeY;
};

/** @} */

#endif // #ifndef GUIBASE_H
