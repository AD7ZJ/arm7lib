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
 * Filename:     SystemControl.cpp                                         *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

/// Reserve memory for singleton object.
static SystemControl systemControlSingletonObject;

// Symbol provided by the linker file lpc2148-flash.ld for the start of the C stack.
extern uint32_t __c_stack_top__;

// Symbol provided by the linker file lpc2148-flash.ld for the start of the IRQ stack.
extern uint32_t __irq_stack_top__;

/// Magic number used to search for unused stack space.
const uint32_t UnusedStackMagicNumber = 0xdeadbeef;

/// The maximum stack size to search based on the RAM size.
const uint32_t MaxStackSize = 0xc000;

/**
 *   Get a pointer to the SystemControl singleton object.
 */
SystemControl *SystemControl::GetInstance()
{
    return &systemControlSingletonObject;
}

/**
 *   Constructor.
 */
SystemControl::SystemControl()
{
    this->clock = ClockNotSet;
    this->pClock = 12000000;
}

/**
 * Get the Peripheral clock frequency.
 * 
 * @return frequency in Hertz
 */
uint32_t SystemControl::GetPClock()
{
    return this->pClock;	
}

/**
 * Enable the system control object to provide clock information to all library functions such as the
 * UART and timers.
 * 
 * @param clock enumeration the sets the desired CPU clock frequency
 * @param systemTimeBase enumeration that specifies Timer 0 or 1 for the system 1mS tick
 */
void SystemControl::Enable (ClockFrequency clock, SystemTickTimeBase systemTimeBase)
{
    this->clock = clock;

    switch (clock)
    {
        case SystemControl::Clock12MHz:
            // Disable the MAM so we can update the timing register.
            MAMCR = 0x00;
            
            // Set the timing register to 1 processor clock (CCLK) in duration.
            MAMTIM = 0x01;
            
            // Set MAM functions as fully enabled.
            MAMCR = 0x02;
          
            // Set the peripheral Clock (pclk) to System Clock (cclk).
            VPBDIV = 0x01;
            
            // Peripheral clock value used to calculate baud rate, timing, I2C clocks, etc.
            this->pClock = 12000000;    		
            break;
            
        case SystemControl::Clock24MHz:
            // Disable the MAM so we can update the timing register.
            MAMCR = 0x00;            
            
            // Set the multiplier and divider values for the PLL.
            PLLCFG = 0x41;
            PLLFeed();
          
            // Enable the PLL.  
            PLLCON = 0x1;
            PLLFeed();
          
            // Wait for the PLL to lock to set frequency
            while(!(PLLSTAT & PLOCK)) ;

            // Connect the PLL as the clock source.
            PLLCON = 0x3;
            PLLFeed();          
          
            // Set the timing register to 2 processor clocks (CCLK) in duration.
            MAMTIM = 0x02;
            
            // Set MAM functions as fully enabled.
            MAMCR = 0x2;
          
            // Set the peripheral Clock (pclk) to System Clock (cclk)
            VPBDIV = 0x1;            
            
            // Peripheral clock value used to calculate baud rate, timing, I2C clocks, etc.
            this->pClock = 24000000;            
            break;            
            
        case SystemControl::Clock60MHz:
            // Disable the MAM so we can update the timing register.
            MAMCR = 0x00;            
            
            // Set the multiplier and divider values for the PLL.
            PLLCFG = 0x24;
            PLLFeed();
          
            // Enable the PLL.  
            PLLCON = 0x1;
            PLLFeed();
          
            // Wait for the PLL to lock to set frequency
            while(!(PLLSTAT & PLOCK)) ;

            // Connect the PLL as the clock source.
            PLLCON = 0x3;
            PLLFeed();          
          
            // Set the timing register to 3 processor clocks (CCLK) in duration.
            MAMTIM = 0x03;
            
            // Set MAM functions as fully enabled.
            MAMCR = 0x2;
          
            // Set the peripheral Clock (pclk) to System Clock (cclk)
            VPBDIV = 0x1;            
            
            // Peripheral clock value used to calculate baud rate, timing, I2C clocks, etc.
            this->pClock = 60000000;    		
            break;
            
        default:
            break;    
    } // END switch
    
    // Enable the on board RTC (Real Time Clock).
    RTC::GetInstance()->Enable();
    
    // Enable timer 0 or 1 to provide the system 1mS timer tick.
    if (systemTimeBase == Timer0Base)
    {
        Timer0::GetInstance()->Enable();
        this->timeBase = Timer0::GetInstance();
    } else {
        Timer1::GetInstance()->Enable();
        this->timeBase = Timer1::GetInstance();
    } // END if-else
    
    // Turn on the interrupts so the timers, UARTs, and other interrupt driven devices work.
    enableIRQ();
}

/**
 * Write the special sequence required to change the PLL clock options.
 */
void SystemControl::PLLFeed()
{
    PLLFEED = 0xAA;
    PLLFEED = 0x55;    
}

/**
 * Wait for the desired time period in milli-seconds to pass.
 * 
 * @param sleep time delay in milli-seconds
 */
void SystemControl::Sleep(uint32_t sleep)
{
    uint32_t endTime = systemControlSingletonObject.timeBase->GetTick() + sleep + 1;
    
    while (systemControlSingletonObject.timeBase->GetTick() < endTime); 
}

/**
 * Get the system 1mS clock tick.
 * 
 * @return clock tick in milli-seconds
 */
uint32_t SystemControl::GetTick()
{
    return systemControlSingletonObject.timeBase->GetTick();
}

/**
 * Get the number of bytes used in the C stack.
 * 
 * @return number of bytes used in stack
 */
uint32_t SystemControl::CStackSize()
{
    uint32_t count;
    uint32_t *search;
    
    count = 0;
    search = &__c_stack_top__;
    
    --search;
    
    while (count < MaxStackSize && *search != UnusedStackMagicNumber)
    {
        ++count;
        --search;
    }
    
    return 4 * count;
}

/**
 * Get the number of bytes used in the IRQ stack.
 * 
 * @return number of bytes used in stack
 */
uint32_t SystemControl::IRQStackSize()
{
    uint32_t count;
    uint32_t *search;
    
    count = 0;
    search = &__irq_stack_top__;
    
    --search;
    
    while (count < MaxStackSize && *search != UnusedStackMagicNumber)
    {
        ++count;
        --search;
    }
    
    return 4 * count;
}

/**
 * Function that is called if we try to use a virtual function before it has been constructed.
 * Since we call the ctor functions in the startup code, we should never get to this function.
 * We provide it here so we don't have to link in the ibsupc++ library that brings all kinds
 * of extra "stuff".  This function is required if we declare "virtual void func() = 0;".
 */
extern "C" void __cxa_pure_virtual(void)
{
    // Either lock the system or reboot.  Rebooting over and over should attract some attention.
    WatchDogTimer::Reset();
}
