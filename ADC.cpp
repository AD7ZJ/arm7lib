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
 * Filename:     ADC.cpp                                                   *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

/// Reserve memory for singleton object.
static ADC adcSingletonObject;

/**
 * Get a pointer to the ADC singleton object.
 */
ADC *ADC::GetInstance()
{
	return &adcSingletonObject;
}

/**
 * Enable the A/D converter hardware.  Multiple channels may be selected by ORing together the
 * channel selection.  The ADC channel 0 and/or 1 is automatically enabled based on the desired
 * channels.
 *
 * @param adcChannel one or more desired ADC channels to enable
 */
void ADC::Enable(ADCChannel adcChannel)
{
    uint32_t clockDiv;

    // Calculate the divider to get the desired 4.5MHz ADC clock.
    clockDiv = ((SystemControl::GetInstance()->GetPClock() / 450000) + 5) / 10;

    if (clockDiv != 0)
        --clockDiv;

    // Set the pin select values required for each ADC pin.
    if (adcChannel & AD0_1)
        PINSEL1 |= (0x01 << 24);

    if (adcChannel & AD0_2)
        PINSEL1 |= (0x01 << 26);

    if (adcChannel & AD0_3)
        PINSEL1 |= (0x01 << 28);

    if (adcChannel & AD0_4)
        PINSEL1 |= (0x01 << 18);

    if (adcChannel & AD0_6)
        PINSEL0 |= (0x03 << 8);

    if (adcChannel & AD0_7)
        PINSEL0 |= (0x03 << 10);

    if (adcChannel & AD1_0)
        PINSEL0 |= (0x03 << 12);

    if (adcChannel & AD1_1)
        PINSEL0 |= (0x03 << 16);

    if (adcChannel & AD1_2)
        PINSEL0 |= (0x03 << 20);

    if (adcChannel & AD1_3)
        PINSEL0 |= (0x03 << 24);

    if (adcChannel & AD1_4)
        PINSEL0 |= (0x03 << 26);

    if (adcChannel & AD1_5)
        PINSEL0 |= (0x03 << 30);

    if (adcChannel & AD1_6)
        PINSEL1 |= (0x02 << 10);

    if (adcChannel & AD1_7)
        PINSEL1 |= (0x01 << 12);

    // Enable the ADC channel 0 if we use any ADC channels from it.
	if (adcChannel & 0x00ff)
        AD0CR = (clockDiv << 8) | ADxCR_PDN;

	// ENable the ADC channel 1 if we use any ADC channels from it.
	if (adcChannel & 0xff00)
	    AD1CR = (clockDiv << 8) | ADxCR_PDN;
}

/**
 * Start an A/D conversion and return the current channel value.
 *
 * @param adcChannel desired ADC channel to read
 *
 * @return ADC reading in the range 0 to 1023.
 */
uint32_t ADC::Read (ADCChannel adcChannel)
{
    uint32_t value;

    // Determine if we are using ADC converter 0 or 1 based on the desired channel.
    if (adcChannel < 0x0100)
    {
        // Set the desired channel and start the conversion.
        AD0CR = (AD0CR & 0xffffff00) | adcChannel;
        AD0CR |= ADxCR_START_NOW;

        // Wait for the conversion to complete.
        do
        {
            value = AD0GDR;
        } while ((value & ADxGDR_DONE) == 0x00);

        // Stop the converter.
        AD0CR &= 0xF8FFFFFF;
    } else {
        // Set the desired channel and start the conversion.
        AD1CR = (AD1CR & 0xffffff00) | (adcChannel >> 8);
        AD1CR |= ADxCR_START_NOW;

        // Wait for the conversion to complete.
        do
        {
            value = AD1GDR;
        } while ((value & ADxGDR_DONE) == 0x00);

        // Stop the converter.
        AD1CR &= 0xF8FFFFFF;
    }

    // Return the ADC reading.
    return (value >> 6) & 0x3ff;
}


