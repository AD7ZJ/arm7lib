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
 * Filename:     PWM.cpp                                                   *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

/// Reserve memory for the singleton object.
static PWM pwmSingletonObject;

/**
 * Get a pointer to the PWM object.
 */
PWM *PWM::GetInstance()
{
    return 	&pwmSingletonObject;
}

/**
 * Configure the PWM subsystem with the desired PWM channel(s) and period.  
 * The duty cycle of all active channels defaults to 0%.
 * 
 * @param pwmChannel one or more PWM channels logically ORed
 * @param frequency PWM periodic rate in Hertz
 */
void PWM::Enable(PWMChannel pwmChannel, uint32_t frequency)
{
    // Reset the PWM subsystem.
    PWMTCR = PWMTCR_RESET;
    
    // Set the pin select values required for each PWM channel.
    if (pwmChannel & PWM1)
    {
        PINSEL0 |= (0x02 << 0);    
        PWMPCR |= PWMENA1;
    } // END if
        
    if (pwmChannel & PWM2)
    {
        PINSEL0 |= (0x02 << 14);    
        PWMPCR |= PWMENA2;
    } // END if
    
    if (pwmChannel & PWM3)
    {
        PINSEL0 |= (0x02 << 2);    
        PWMPCR |= PWMENA3;
    } // END if

    if (pwmChannel & PWM4)
    {
        PINSEL0 |= (0x02 << 16);    
        PWMPCR |= PWMENA4;
    } // END if
    
    if (pwmChannel & PWM5)
    {
        PINSEL1 |= (0x01 << 10);    
        PWMPCR |= PWMENA5;
    } // END if
    
    if (pwmChannel & PWM6)
    {
        PINSEL0 |= (0x02 << 18);    
        PWMPCR |= PWMENA6;
    } // END if

    // Set the prescalar to 0 so the counter matchs the clock.
    PWMPR = 0x00000000;
    
    // Reset PWMTC when it matches PWMMR0
    PWMMCR = PWMMR0R; 
    
    // Set PWM 0 so it will match and reset at the desired period.
    this->period = SystemControl::GetInstance()->GetPClock() / frequency;
    PWMMR0 = period - 1;

    // Latch all the match registers.
    PWMLER = LER0_EN | LER1_EN | LER2_EN | LER3_EN | LER4_EN | LER5_EN | LER6_EN;
    
    // Enable the counter and PWM subsystem.
    PWMTCR = PWMTCR_COUNTER_ENABLE | PWMTCR_PWM_ENABLE; 
}

/**
 * Set the duty cycle of one or more PWM channels.  The duty cycle is in
 * units of 0.01%, i.e. 25% is 2500, 37.5% is 3750.
 * 
 * @param pwmChannel one or more PWM channels logically ORed
 * @param dutyCycle in units of 0.01 percent
 * @param invertFlag when set true set the duty cycle of the OFF cycle
 */
void PWM::SetDutyCycle (PWMChannel pwmChannel, uint32_t dutyCycle, bool_t invertFlag)
{
    uint32_t matchRegister;
    
    if (invertFlag)
        matchRegister = (this->period * (10000 - dutyCycle)) / 10000;
    else
        matchRegister = (this->period * dutyCycle) / 10000 ;
    
    // Set the pin select values required for each PWM channel.
    if (pwmChannel & PWM1)
        PWMMR1 = matchRegister;
        
    if (pwmChannel & PWM2)
        PWMMR2 = matchRegister;
    
    if (pwmChannel & PWM3)
        PWMMR3 = matchRegister;

    if (pwmChannel & PWM4)
        PWMMR4 = matchRegister;
    
    if (pwmChannel & PWM5)
        PWMMR5 = matchRegister;
    
    if (pwmChannel & PWM6)
        PWMMR6 = matchRegister;
    
    // Latch the match registers.
    PWMLER = LER1_EN | LER2_EN | LER3_EN | LER4_EN | LER5_EN | LER6_EN;
}

