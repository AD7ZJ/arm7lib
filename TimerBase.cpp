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
 * Filename:     TimerBase.cpp                                             *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

/**
 *  Constructor.
 */
TimerBase::TimerBase()
{
    this->timerTick = 0;
    this->timerAccum = 0;
    this->timerTickCallback = NULL;
}

/**
 * Interrupt Service Routine to process the timer tick.
 */
void TimerBase::TimerTick()
{
    // The timer accumulator is the number of microseconds that have passed since the last interrupt.
    this->timerAccum += this->period;
    
    // We add the integer number of 1000uS (1mS) periods to our timer tick.
    this->timerTick += (this->timerAccum / 1000);
    
    // Save the remainder (values less than 1mS).
    this->timerAccum %= 1000; 
    
    // Only callback if the user set the callback.
    if (this->timerTickCallback != NULL)
        this->timerTickCallback();
}

/**
 * Set the timer interrupt rate.
 * 
 * @param period in microseconds
 */
void TimerBase::SetPeriod (uint32_t period)
{
    // Save the rate for generating the 1mS timer tick.
    this->period = period;
}

/**
 * Number of milliseconds since the timer was started.
 * 
 * @return time in milliseconds
 */
uint32_t TimerBase::GetTick()
{
    return this->timerTick;	
}

/**
 * Set the function that is called at every timer tick.
 * 
 * @param timerTickCallback pointer to callback function
 */
void TimerBase::SetCallback(void (*timerTickCallback)() )
{
    this->timerTickCallback = timerTickCallback;
}




