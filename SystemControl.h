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
 * Filename:     SystemControl.h                                           *
 *                                                                         *
 ***************************************************************************/

#ifndef SYSTEM_CONTROL_H
#define SYSTEM_CONTROL_H

/**
 *  @defgroup onchip On-Chip Peripherals
 *
 *  @{
 */

/**
 *  The System Control object includes several system features and
 *  control registers for a number of functions that are not related
 *  to specific peripheral devices.
 */
class SystemControl
{
public:
    SystemControl();

    /// Enumeration for processor clock frequency setting.
    typedef enum
    {
        /// The clock frequency has not been set.
        ClockNotSet,

        /// 12MHz processor clock and peripheral clock.
        Clock12MHz,

        /// 24MHz processor clock and peripheral clock.  (Minimum speed required for USB operation).
        Clock24MHz,

        /// 60MHz processor clock and peripheral clock.
        Clock60MHz
    } ClockFrequency;

    /// Enumeration that specifies the timer to use for the system 1mS tick.
    typedef enum
    {
        /// Utilize the Timer 0 hardware for the 1mS system tick.
        Timer0Base,

        /// Utilize the Timer 1 hardware for the 1mS system tick.
        Timer1Base
    } SystemTickTimeBase;

    void Enable (ClockFrequency clock, SystemTickTimeBase timeBase);
    uint32_t GetPClock();
    static uint32_t GetTick();
    static void Sleep(uint32_t sleep);
    static uint32_t CStackSize();
    static uint32_t IRQStackSize();

    static SystemControl *GetInstance();

private:
    void PLLFeed();

    /// Clock frequency setting.
    ClockFrequency clock;

    /// Peripheral clock frequency in Hertz.
    uint32_t pClock;

    /// System time base.
    TimerBase *timeBase;
};

/** @} */

#endif // #ifndef SYSTEM_CONTROL_H
