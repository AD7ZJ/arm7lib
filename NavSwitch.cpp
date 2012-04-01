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
 * Filename:     NavSwitch.cpp                                             *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

NavSwitch::NavSwitch(SwitchOrientation orientation) : MuxSwitch(2, 3)
{
    this->orientation = orientation;
}

/**
 * Indicate if the FIFO has keys.
 *
 * @return true if key has been pushed; otherwise false
 */
bool_t NavSwitch::HasKey()
{
    return MuxSwitch::HasKey();
}

/**
 * Return the oldest entry in the FIFO.
 *
 * @return key pressed
 */
NavSwitch::KeyStroke NavSwitch::GetKey()
{
    uint32_t key;

    if (!MuxSwitch::HasKey())
        return NoKey;

    switch (MuxSwitch::GetKey())
    {
        case Row1Col1:
            key = UpKey;
            break;

        default:
            return NoKey;

    } // END switch

    key = key + static_cast<uint32_t> (this->orientation);

    if (key > 4)
        key = 1;

    return static_cast<NavSwitch::KeyStroke> (key);
}
