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
 * Filename:     PWM.h                                                     *
 *                                                                         *
 ***************************************************************************/

#ifndef PWM_H
#define PWM_H

/**
 *  @defgroup onchip On-Chip Peripherals
 *
 *  @{
 */

/**
 * Object that manages the PWM (Pulse Width Modulation) hardware.
 */
class PWM
{
public:
    /// Defines the desired PWM channel.
    typedef enum
    {
        /// PWM Channel 1
        PWM1 = 0x0001,
       
        /// PWM Channel 2
        PWM2 = 0x0002,
       
        /// PWM Channel 3
        PWM3 = 0x0004,
       
        /// PWM Channel 4
        PWM4 = 0x0008,
       
        /// PWM Channel 5
        PWM5 = 0x0010,
       
        /// PWM Channel 6
        PWM6 = 0x0020      
    } PWMChannel;
    
    void SetDutyCycle (PWMChannel pwmChannel, uint32_t dutyCycle, bool_t invertFlag = false);
    void Enable(PWMChannel pwmChannel, uint32_t frequency);    
    
    static PWM *GetInstance();  
    
private:
    /// The PWM Pulse Repetition Period in units of PClock cycles. 
    uint32_t period;
};

/** @} */

#endif  // #ifndef PWM_H
