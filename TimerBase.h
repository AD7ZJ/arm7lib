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
 * Filename:     TimerBase.h                                               *
 *                                                                         *
 ***************************************************************************/

#ifndef TIMERBASE_H
#define TIMERBASE_H

/**
 *  @defgroup onchip On-Chip Peripherals
 *
 *  @{
 */

/**
 * Object that provides the base functions and data members for
 * the identical Timer 0 and Timer 1 hardware.
 */
class TimerBase
{
public:
    /// Defines the desired match or capture channel event.
    typedef enum
    {
        /// Match channel 0
        Match0 = 0x0001,
       
        /// Match channel 1
        Match1 = 0x0002,
       
        /// Match channel 2
        Match2 = 0x0004,
       
        /// Match channel 3
        Match3 = 0x0008,
       
        /// Capture Channel 0
        Capture0 = 0x0010,
       
        /// Capture Channel 1
        Capture1 = 0x0020,
        
        /// Capture Channel 2
        Capture2 = 0x0040,
        
        /// Capture Channel 3
        Capture3 = 0x0080      
    } MatchCaptureChannel;   
    
    /// Defines the desired capture signal edge.
    typedef enum
    {
        /// Rising edge from low to high.
        Rising = 0x01,
        
        /// Falling edge for high to low.
        Falling = 0x02,

        /// Either the rising or falling edge.
        Both = 0x03        
    } CaptureEdge;    
    
    TimerBase();
    
    uint32_t GetTick();
    void SetCallback(void (*timerTickCallback)() );
    void SetPeriod(uint32_t rate);
    void TimerTick();

private:
    /// Timer ticks in milliseconds.
    volatile uint32_t timerTick;
    
    /// Accumulated timer interrupt period in microseconds.
    uint32_t timerAccum;
    
    /// Timer period in microseconds.
    uint32_t period;
    
    /// User supplied timer event callback.
    void (*timerTickCallback) ();
};

/** @} */

#endif  // #ifndef TIMERBASE_H
