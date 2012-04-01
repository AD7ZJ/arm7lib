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
 * Filename:     WatchDogTimer.cpp                                         *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"
 
/**
 * Force a hardware reset by setting the WDT to a short time period
 * and letting it expire.
 */
void WatchDogTimer::Reset()
{
    // Disable all the interrupts.
    disableIRQ();
    
    // Set the minimum WDTC value.
    WDTC = 0x00ff;
    
    // Enable the watch dog timer and reset options.
    WDMOD = WDMOD_WDEN | WDMOD_WDRESET;

    // Feed sequence to start the WDT.
    WDFEED = 0xAA;
    WDFEED = 0x55;
    
    // Wait for reset.
    for (;;);    
}
