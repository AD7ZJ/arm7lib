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
 * Filename:     Timer1.h                                                  *
 *                                                                         *
 ***************************************************************************/

#ifndef TIMER1_H
#define TIMER1_H

/**
 *  @defgroup onchip On-Chip Peripherals
 *
 *  @{
 */

/**
 * Object that manages the Timer 1 hardware functions.
 */
class Timer1 : public TimerBase
{
public:
    static uint32_t Counter();
    void Enable();
    void EnableCapture(MatchCaptureChannel channel, CaptureEdge edge, uint32_t period);
    static uint32_t GetCaptureTick();
    bool_t IsCapture();
    void SetPeriod(uint32_t period);
    void SetPeriodnS(uint32_t period);
    void TimerTick();
    
    static Timer1 *GetInstance();
};

/** @} */

#endif  // #ifndef TIMER1_H
