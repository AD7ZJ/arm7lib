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
 * Filename:     Timer1.cpp                                                *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

/// Reserve memory for the singleton object.
static Timer1 timer1SingletonObject;

/**
 * C callback function used to call the timer tick function.
 */
inline void Timer1ISR(void)
{
    timer1SingletonObject.TimerTick();
}

/**
 * Get a pointer to the Timer 1 object.
 */
Timer1 *Timer1::GetInstance()
{
    return 	&timer1SingletonObject;
}

/**
 * Get the current timer counter value.
 *
 * @return timer counter value
 */
uint32_t Timer1::Counter()
{
    return T1TC;
}

/**
 * Configure Timer 1 to provide a periodic 1mS interrupt.
 */
void Timer1::Enable()
{
    SetPeriod (1000);
    
    T1MCR = TxMCR_INT_ON_MR0 | TxMCR_RESET_ON_MR0;
    T1TCR = TxTCR_COUNTER_ENABLE;

    VICVectAddr8 = reinterpret_cast <uint32_t> (Timer1ISR);
    VICVectCntl8 = VICVectCntl_ENABLE | VIC_Channel_Timer1;
    VICIntEnable = (1 << VIC_Channel_Timer1);
}

/**
 * Configure Timer 1 to capture the rising, falling, or both edges of the desired channel.
 *
 * @param channel to capture edge event
 * @param edge specifies the rising, falling, or both edges
 * @param period in microseconds
 */
void Timer1::EnableCapture(MatchCaptureChannel channel, CaptureEdge edge, uint32_t period)
{
    // Reset the counter while we set the capture port(s).
    T1TCR = TxTCR_COUNTER_RESET; 
    
    // Set the prescalar for the desired period.
    T1PR = (period * (SystemControl::GetInstance()->GetPClock() / 1000000)) - 1;;
    
    if (channel & Capture0)
    {
        // Set the pin required for the capture.
        PINSEL0 |= (0x02 << 20);
        
        // Enable the interrupts.
        T1CCR |= TxCCR_CAP0I;
        
        // Set the desired edges.
        if (edge & Rising)
            T1CCR |= TxCCR_CAP0RE;
        
        if (edge & Falling)
            T1CCR |= TxCCR_CAP0FE;
        
        T1IR = TxIR_CR0_FLAG; 
    } // END if
    
    // Start the counter.
    T1TCR = TxTCR_COUNTER_ENABLE;
}

/**
 * Set the timer interrupt period.
 * 
 * @param period in microseconds
 */
void Timer1::SetPeriod (uint32_t period)
{
    // Save the rate for generating the 1mS timer tick.
    TimerBase::SetPeriod(period);
    
    // Reset the counter before setting the new value.
    T1TCR = TxTCR_COUNTER_RESET; 
    T1MR0 = (period * (SystemControl::GetInstance()->GetPClock() / 1000000)) - 1;
    T1TCR = TxTCR_COUNTER_ENABLE;
}

/**
 * Set the timer interrupt period.
 * 
 * @param period in nanoseconds
 */
void Timer1::SetPeriodnS (uint32_t period)
{
    // Save the rate for generating the 1mS timer tick.
    TimerBase::SetPeriod(period / 1000);
    
    // Reset the counter before setting the new value.
    T1TCR = TxTCR_COUNTER_RESET; 
    T1MR0 = ((period * (SystemControl::GetInstance()->GetPClock() / 1000000)) / 1000) - 1;
    T1TCR = TxTCR_COUNTER_ENABLE;
}

/**
 * Determine if a capture event has occured.  THis is a one-shot method that is automatically reset
 * after a single capture event.
 * 
 * @return true if capture occured; otherwise false
 */
bool_t Timer1::IsCapture()
{
    if (T1IR & TxIR_CR0_FLAG)
    {
        T1IR = TxIR_CR0_FLAG;
        return true;
    }
    
    return false;
}

/**
 * Get the timer capture value.
 */
uint32_t Timer1::GetCaptureTick()
{
    return T1CR0;
}

/**
 * Interrupt Service Routine to process the timer tick.
 */
void Timer1::TimerTick()
{
    // Reset the timer flag.
    T1IR = TxIR_MR0_FLAG;
    
    TimerBase::TimerTick();
}
