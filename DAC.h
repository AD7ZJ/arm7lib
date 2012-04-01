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
 * Filename:     DAC.h                                                     *
 *                                                                         *
 ***************************************************************************/

#ifndef DAC_H
#define DAC_H

/**
 *  @defgroup onchip On-Chip Peripherals
 *
 *  @{
 */

/**
 *  Manage the on board DAC (Digital To Analog) converter.
 */
class DAC
{
public:
	DAC();

	/// Enumeration that controls the DAC output settling time and current.
	typedef enum
	{
	    /// DAC settling time 1uS and 700uA drive current.
		SettlingTime1uS,

		/// DAC settling time 2.5uS and 350uA drive current.
		SettlingTime2_5uS
	} SettlingTimeBias;

	void Enable();
	void Set (uint32_t value);
	void SettlingTime (SettlingTimeBias settlingTime);

	static DAC *GetInstance();

private:
    /// Mask that is bit ORed with the DAC value.
	uint32_t settlingTimeMask;
};

/** @} */

#endif // #ifndef DAC_H
