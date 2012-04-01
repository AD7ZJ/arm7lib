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
 *               (c) Copyright, 2009 - 2021, ANSR                          *
 *               (c) Copyright, 2001-2008, Michael Gray                    *
 *                 Sadly, Micheal Gray passed away in 2008.  It is his	   *
 *                 inspiration and hard work that have made much of this   *
 *                 library possible.  In his memorial and the spirit of    *
 *                 giving which he so personified, it is released under    *
 *                 the terms of the GNU GPL to the ham radio high          *
 *                 altitude ballooning community.                          *
 *                                                                         *
 ***************************************************************************
 *                                                                         *
 * Filename:     armlib.h                                                  *
 *                                                                         *
 ***************************************************************************/

#ifndef ARMLIB_H
#define ARMLIB_H

/**
 * @mainpage ARM 7 Library
 *
 * @section overview_sec Overview
 *
 *   Generic ARM7 library that abstracts on chip peripherals as well as
 *   external devices such as serial flash memory, GPS engines, and other
 *   RF devices.
 *
 * @section copyright Copyright
 *
 *   <b>(c) Copyright 1997-2011, ANSR</b><br>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111 USA
 */

/**
 *  @defgroup external External Peripherals
 *
 *  Objects to manage and control external peripheral chips.
 */

/**
 *  @defgroup onchip On-Chip Peripherals
 *
 *  Objects that control on-chips functions such as serial buses or
 *  analog input and output.
 */

/**
 *  @defgroup library Generic Library Functions
 *
 *  Objects that provide generic functions such as CRC calculation or
 *  FIFOs.
 */

// We define types that are used for all variables.  These are declared
// because each processor has a different sizes for char, int, long, etc.

/// Boolean value { true, false }
typedef bool bool_t;

/// Signed 8-bit number in the range -128 through 127.
typedef signed char int8_t;

/// Unsigned 8-bit number in the range 0 through 255.
typedef unsigned char uint8_t;

/// Signed 16-bit number in the range -32768 through 32767.
typedef signed short int16_t;

/// Unsigned 16-bit number in the range 0 through 65535.
typedef unsigned short uint16_t;

/// Signed 32-bit number in the range -2147483648 through 2147483647.
typedef signed long int32_t;

/// Unsigned 32-bit number in the range 0 through 4294967295.
typedef unsigned long uint32_t;

/// Signed 64-bit number in the range -9223372036854775808 through 9223372036854775807.
typedef signed long long int64_t;

/// Unsigned 64-bit number in the range 0 to 18446744073709551615.
typedef unsigned long long uint64_t;

/// IEEE 32-bit floating point number.
typedef float float_t;

/// IEEE 64-bit floating point number.
typedef double double_t;


// Include the base processor definitions.
#include "lpc214x.h"

// C runtime library functions.
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cstdarg>

// Header files for the library components.
#include "AESKey.h"
#include "AES.h"
#include "CRC16.h"
#include "CRC32.h"
#include "FlashBlock.h"
#include "GPSData.h"
#include "Navigation.h"
#include "RTCTime.h"
#include "FIFO.h"

#include "ADC.h"
#include "DAC.h"
#include "IAP.h"
#include "I2C0.h"
#include "I2C1.h"
#include "PWM.h"
#include "RTC.h"
#include "RTCBase.h"
#include "SPIBase.h"
#include "SPI0.h"
#include "SPI1.h"
#include "TimerBase.h"
#include "Timer0.h"
#include "Timer1.h"
#include "UARTBase.h"
#include "UART0.h"
#include "UART1.h"
#include "USBHIDReport.h"
#include "USBFIFO.h"
#include "USB.h"
#include "HIDReport.h"
#include "VIC.h"
#include "SystemControl.h"
#include "WatchDogTimer.h"

#include "AD9832.h"
#include "AD9954.h"
#include "AT26DF161A.h"
#include "CC1020.h"
#include "CMX808A.h"
#include "CMX867A.h"
#include "GPSLassen.h"
#include "GPSNavman.h"
#include "GSM0308.h"
#include "ISL12026.h"
#include "LIS302DL.h"
#include "LM73.h"
#include "LM92.h"
#include "M25P80.h"
#include "MuxSwitch.h"
#include "NavSwitch.h"
#include "RV8564C2.h"
#include "STX2.h"
#include "S1V30120.h"
#include "SHT11.h"


// Fonts for displays.  These file are auto generated by the fontgen tool.
extern "C"
{
#include <fonts/Tahoma_10_n_nnnn_0_nh.h>
#include <fonts/Tahoma_10_n_bnnn_0_nh.h>
#include <fonts/Tahoma_12_n_nnnn_0_nh.h>
#include <fonts/Tahoma_14_n_bnnn_0_nh.h>
}

#include "GUIBase.h"
#include "GUI.h"
#include "Optrex15.h"
#include "Optrex19.h"
#include "Optrex30.h"
#include "OSD0201QILK.h"

#include "AX25.h"
#include "Base64Encoder.h"
#include "NMEA.h"
#include "MIC-E.h"
#include "UUEncoder.h"

#endif  // #ifndef ARMLIB_H


