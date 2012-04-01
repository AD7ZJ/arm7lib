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
 * Filename:     NavSwitch.h                                               *
 *                                                                         *
 ***************************************************************************/

#ifndef NAVSWITCH_H
#define NAVSWITCH_H

/**
 *  @defgroup external External Peripherals
 *
 *  @{
 */

/**
 *  Control the STMicroelectronics MP25P80 serial flash device.  The
 *  NavSwitch is an 8Mbit device organized as 1Mbyte x 8.
 */
class NavSwitch : public MuxSwitch
{
public:
    /// Specifies the orientation of the switch in relationship to the up position.
    typedef enum
    {
        Orientation0 = 0,

        Orientation90 = 1,

        Orientation180 = 2,

        Orientation270 = 3
    } SwitchOrientation;

    typedef enum
    {
        UpKey = 0x01,

        RightKey = 0x02,

        DownKey = 0x03,

        LeftKey = 0x04,

        NoKey = 0x00
    } KeyStroke;

    NavSwitch(SwitchOrientation orientation);

    bool_t HasKey();
    KeyStroke GetKey();


private:
    SwitchOrientation orientation;

};

/** @} */

#endif // #ifndef NAVSWITCH_H

