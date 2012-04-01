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
 * Filename:     I2C1.cpp                                                  *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

/// Reserve memory for singleton object.
static I2C1 I2C1SingletonObject;

/**
 *  Get a pointer to the I2C port 0 object.
 */
I2C1 *I2C1::GetInstance()
{
    return 	&I2C1SingletonObject;
}

/**
 *  Enable the required pins for the I2C port and configure it for operation.
 */
void I2C1::Enable()
{

}

