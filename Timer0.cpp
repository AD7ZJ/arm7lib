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
 * Filename:     Timer0.cpp                                                *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

/// Reserve memory for the singleton object.
static Timer0 timer0SingletonObject;

/**
 * C callback function used to call the timer tick function.
 */
inline void Timer0ISR(void)
{
    timer0SingletonObject.TimerTick();
}

/**
 * Get a pointer to the Timer 0 object.
*/
Timer0 *Timer0::GetInstance()
{
    return 	&timer0SingletonObject;
}

/**
*   Enable the required pins for Timer 0 and configure it for operation.
*/
void Timer0::Enable()
{
    SetPeriod (1000);    
    
    T0MCR = TxMCR_INT_ON_MR0 | TxMCR_RESET_ON_MR0;
    T0TCR = TxTCR_COUNTER_ENABLE;

    VICVectAddr9 = reinterpret_cast <uint32_t> (Timer0ISR);
    VICVectCntl9 = VICVectCntl_ENABLE | VIC_Channel_Timer0;
    VICIntEnable = (1 << VIC_Channel_Timer0);
}

/**
 * Set the timer interrupt rate.
 * 
 * @param period in microseconds
 */
void Timer0::SetPeriod (uint32_t period)
{
    // Save the rate for generating the 1mS timer tick.
    TimerBase::SetPeriod(period);
    
    // Reset the counter before setting the new value.
    T0TCR = TxTCR_COUNTER_RESET; 
    T0MR0 = (period * (SystemControl::GetInstance()->GetPClock() / 1000000)) - 1;
    T0TCR = TxTCR_COUNTER_ENABLE;
}

/**
 * Interrupt Service Routine to process the timer tick.
 */
void Timer0::TimerTick()
{
    // Reset the timer flag.
    T0IR = TxIR_MR0_FLAG;

    TimerBase::TimerTick();
}


