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
 * Filename:     AD9954.cpp                                                *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

/// AD9954 CFR1 - Control functions including RAM, profiles, OSK, sync, sweep, SPI, and power control settings.
const uint32_t DDS_AD9954_CFR1 = 0x00;

/// AD9954 CFR2 - Control functions including sync, PLL multiplier, VCO range, and charge pump current.
const uint32_t DDS_AD9954_CFR2 = 0x01;

/// AD9954 ASF - Auto ramp rate speed control and output scale factor (0x0000 to 0x3fff).
const uint32_t DDS_AD9954_ASF = 0x02;

/// AD9954 ARR - Amplitude ramp rate for OSK function.
const uint32_t DDS_AD9954_ARR = 0x03;

/// AD9954 FTW0 - Frequency tuning word 0.
const uint32_t DDS_AD9954_FTW0 = 0x04;

/// AD9954 POW - Phase Offset Word 0.
const uint32_t DDS_AD9954_POW0 = 0x05;

/// AD9954 FTW1 - Frequency tuning word 1
const uint32_t DDS_AD9954_FTW1 = 0x06;

/// AD9954 NLSCW - Negative Linear Sweep Control Word used for spectral shaping in FSK mode
const uint32_t DDS_AD9954_NLSCW = 0x07;

/// AD9954 PLSCW - Positive Linear Sweep Control Word used for spectral shaping in FSK mode
const uint32_t DDS_AD9954_PLSCW = 0x08;

/// AD9954 RSCW0 - RAM Segment Control Word 0
const uint32_t DDS_AD9954_RWCW0 = 0x07;

/// AD9954 RSCW0 - RAM Segment Control Word 1
const uint32_t DDS_AD9954_RWCW1 = 0x08;

/// AD9954 RAM segment
const uint32_t DDS_RAM = 0x0b;

/// Number of digits in DDS frequency to FTW conversion.
const uint32_t DDSFreqToFTWDigits = 9;

/// Array of multiplication factors used to convert frequency to the FTW.
const uint32_t DDSMult[DDSFreqToFTWDigits] = { 11, 1, 8, 4, 8, 1, 0, 6, 6 };

/// Array of divisors used to convert frequency to the FTW.
const uint32_t DDSDivisor[DDSFreqToFTWDigits - 1] = { 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000 };

/// Lookup table to convert dB amplitude scale in 0.5 steps to a linear DDS scale factor.
const uint16_t DDSLogToLinear[] =
{
    16383, 15467, 14601, 13785, 13013, 12286, 11598, 10949, 10337, 9759, 9213, 8697,
    8211, 7752, 7318, 6909, 6522, 6157, 5813, 5488, 5181, 4891, 4617, 4359, 4115, 3885,
    3668, 3463, 3269, 3086, 2913, 2750, 2597, 2451, 2314, 2185, 2062, 1947, 1838, 1735,
    1638, 1547, 1460, 1378, 1301, 1229, 1160, 1095, 1034
};


/// Reserve memory for singleton object.
static AD9954 ad9954SingletonObject;

/**
 *  Get a pointer to the SPI0 object.
 */
AD9954 *AD9954::GetInstance()
{
    return  &ad9954SingletonObject;
}

/**
 *   Initialize the DDS registers and RAM.
 */
void AD9954::Enable()
{
    // Set default I/O for the DDS.
    IOSetCS (true);
    IOSetProfileSelect (Profile0);
    IOSetIOUpdate (false);

    // Turn off the output.
    IOSetOSK (false);

    IOSetReset (true);
    SystemControl::Sleep(10);

    IOSetReset (false);
    SystemControl::Sleep(10);

    SetMode (PowerDown);

    // ASF (Amplitude Scale Factor) to full scale (0x3fff).
    SetOutputScale (0x3fff);

    // ARR (Amplitude Ramp Rate) to 15.5mS for OSK
    SetAmplitudeRampRate (181);

    // CFR2 (Control Function Register No. 2)
    IOSetCS (false);
    SPIWrite (0x01);

    SPIWrite (0x00);     // Unused register bits
    SPIWrite (0x00);
    SPIWrite (0xa4);     // 20x reference clock multiplier, high VCO range, nominal charge pump current
    IOSetCS (true);

    // Strobe the part so we apply the updates.
    IOSetIOUpdate (true);
    IOSetIOUpdate (false);
}

/**
 *  Set DDS amplitude value in the range 0 to 16383 where 16383 is full scale.  This value is a
 *  linear multiplier and needs to be scale for RF output power in log scale.
 *
 *  @param scale in the range 0 to 16383
 */
void AD9954::SetOutputScale (uint32_t scale)
{
    // Set ASF (Amplitude Scale Factor)
    IOSetCS (false);
    SPIWrite (DDS_AD9954_ASF);

    SPIWrite ((scale >> 8) & 0xff);
    SPIWrite (scale & 0xff);

    IOSetCS (true);

    // Strobe the DDS to set the value.
    IOSetIOUpdate (true);
    IOSetIOUpdate (false);
}

/**
 *  Set the ARR (Amplitude Ramp Rate)  register in the range 0 to 255.
 *
 *  @param arr in the range 0 to 255
 */
void AD9954::SetAmplitudeRampRate (uint32_t arr)
{
    // Set ARR (Amplitude Ramp Rate).
    IOSetCS (false);
    SPIWrite (DDS_AD9954_ARR);

    SPIWrite (arr);

    IOSetCS (true);

    // Strobe the DDS to set the value.
    IOSetIOUpdate (true);
    IOSetIOUpdate (false);
}

/**
 *   Set the DDS amplitude in units of dBc of full scale where 1 is 0.1 dB.  For example, a value of 30 is 3dBc
 *   or a value of 85 is 8.5dBc.
 *
 *   @param amplitude in 0.1 dBc of full scale
 */
void AD9954::SetAmplitude (uint32_t amplitude)
{
    // Set the linear DDS ASF (Amplitude Scale Factor) based on the dB lookup table.
    SetOutputScale (GetAmplitudeScale(amplitude));

    // Toggle the DDS output low and then high to force it to ramp to the new output level setting.
    IOSetOSK (false);
    SystemControl::Sleep(25);

    IOSetOSK (true);
    SystemControl::Sleep(25);
}

/**
 *   Set the DDS linear scale factor that is of dBc of full scale where 1 LSB is 0.1 dB.
 *   A value of 30 is 3dBc or a value of 85 is 8.5dBc.
 *
 *   @param amplitude in 0.1 dBc of full scale
 *
 *   @return scale factor in the range 0 to 16383
 */
uint32_t AD9954::GetAmplitudeScale (uint32_t amplitude)
{
    // Range limit based on the lookup table size.
    if (amplitude > 240)
        amplitude = 240;

    // Set the linear DDS ASF (Amplitude Scale Factor) based on the dB lookup table.
    return DDSLogToLinear[amplitude / 5];
}

/**
 *   Set the frequency.
 *
 *   @param freq frequency in Hertz
 *
 */
void AD9954::SetFreq(uint32_t freq)
{
    uint32_t i, ftw;

    // To avoid rounding errors with floating point math, we do a long multiply on the data.
    ftw = freq * DDSMult[0];

    for (i = 0; i < DDSFreqToFTWDigits - 1; ++i)
        ftw += (freq * DDSMult[i+1]) / DDSDivisor[i];

    SetFTW (ftw);
}

/**
 *   Set the output phase.
 *
 *   @param phase true for 180 degree phase shift; false for 0 degree phase shift
*/
void AD9954::SetPhase (bool_t phase)
{
    // Set the POW0 (Phase Offset Word 0) to 0 or 180 degrees.
    IOSetCS (false);
    SPIWrite (DDS_AD9954_POW0);

    if (phase)
    {
        SPIWrite (0x20);
        SPIWrite (0x00);
    } else {
        SPIWrite (0x00);
        SPIWrite (0x00);
    } // END if-else

    IOSetCS (true);

    // Strobe the DDS to write the phase change.
    IOSetIOUpdate (true);
    IOSetIOUpdate (false);
}

/**
 *    Turn on the DDS output.
 *
 *    @param state true to activate; otherwise false
 */
void AD9954::SetOSK (bool_t state)
{
    if (state)
        IOSetOSK (true);
    else
        IOSetOSK (false);
}

/**
 *  Set DDS frequency tuning word.  The output frequency is equal to RefClock * (ftw / 2 ^ 32).
 *
 *  @param ftw Frequency Tuning Word
 */
void AD9954::SetFTW (uint32_t ftw)
{
    // Set FTW0 (Frequency Tuning Word 0)
    IOSetCS (false);
    SPIWrite (DDS_AD9954_FTW0);

    SPIWrite ((ftw >> 24) & 0xff);
    SPIWrite ((ftw >> 16) & 0xff);
    SPIWrite ((ftw >> 8) & 0xff);
    SPIWrite (ftw & 0xff);

    IOSetCS (true);

    // Strobe the DDS to set the frequency.
    IOSetIOUpdate (true);
    IOSetIOUpdate (false);
}

/**
 *   Set the DDS to run in A-FSK, FSK, or PSK31 mode
 *
 *   @param mode <i>DDS_MODE_APRS</i>, <i>DDS_MODE_PSK31</i>, or <i>DDS_MODE_HF_APRS</i> constant
 */
void AD9954::SetMode (DDSMode mode)
{
    switch (mode)
    {
        case PowerDown:
            // CFR1 (Control Function Register No. 1)
            IOSetCS (false);
            SPIWrite (DDS_AD9954_CFR1);

            SPIWrite (0x00);
            SPIWrite (0x00);
            SPIWrite (0x00);
            SPIWrite (0xf0);  // Power down all subsystems.
            IOSetCS (true);
            break;

        case CW:
            // CFR0 (Control Function Register No. 1)
            IOSetCS (false);
            SPIWrite (DDS_AD9954_CFR1);

            SPIWrite (0x03);  // Clear RAM Enable, OSK Enable, Auto OSK keying
            SPIWrite (0x00);
            SPIWrite (0x02);  // SDIO input only
            SPIWrite (0x40);  // Power down comparator circuit
            IOSetCS (true);
            break;

        case CWNoAutoOSK:
            // CFR0 (Control Function Register No. 1)
            IOSetCS (false);
            SPIWrite (DDS_AD9954_CFR1);

            SPIWrite (0x02);  // Clear RAM Enable, OSK Enable
            SPIWrite (0x00);
            SPIWrite (0x02);  // SDIO input only
            SPIWrite (0x40);  // Power down comparator circuit
            IOSetCS (true);
            break;

    } // END switch

    // Strobe the DDS to change the mode.
    IOSetIOUpdate (true);
    IOSetIOUpdate (false);
}
