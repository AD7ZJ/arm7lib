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
 * Filename:     ADC.h                                                     *
 *                                                                         *
 ***************************************************************************/

#ifndef ADC_H
#define ADC_H

/**
 *  @defgroup onchip On-Chip Peripherals
 *
 *  @{
 */

/**
 *  Manage the on board ADC (Analog to Digital) converter.
 */
class ADC
{
public:
    /// Defines the desired ADC channel to enable and read data from.
    typedef enum
    {
        /// ADC Converter 0, Pin 1.
        AD0_1 = 0x02,

        /// ADC Converter 0, Pin 2.
        AD0_2 = 0x04,
        
        /// ADC Converter 0, Pin 3.
        AD0_3 = 0x08,
       
        /// ADC Converter 0, Pin 4.
        AD0_4 = 0x10,
        
        /// ADC Converter 0, Pin 6.
        AD0_6 = 0x40,
        
        /// ADC Converter 0, Pin 7.
        AD0_7 = 0x80,        
        
        /// ADC Converter 1, Pin 0.
        AD1_0 = 0x0100,
        
        /// ADC Converter 1, Pin 1.
        AD1_1 = 0x0200,
       
        /// ADC Converter 1, Pin 2.
        AD1_2 = 0x0400,
        
        /// ADC Converter 1, Pin 3.
        AD1_3 = 0x0800,
        
        /// ADC Converter 1, Pin 4.
        AD1_4 = 0x1000,
        
        /// ADC Converter 1, Pin 5.
        AD1_5 = 0x2000,
        
        /// ADC Converter 1, Pin 6.
        AD1_6 = 0x4000,
        
        /// ADC Converter 1, Pin 7.
        AD1_7 = 0x8000        
    } ADCChannel;
    
	uint32_t Read (ADCChannel adcChannel);
	void Enable(ADCChannel adcChannel);

	static ADC *GetInstance();
};

/** @} */

#endif // #ifndef ADC_H
