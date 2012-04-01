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
 * Filename:     RTCBase.cpp                                               *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

/// Table to speed conversion from BCD to decimal.
const uint32_t BCDTable[10] = { 0, 10, 20, 30, 40, 50, 60, 70, 80, 90 };

/**
 * Convert a 2-digit BCD number to decimal in the range 00 to 99.
 *
 * @param bcd BCD (Binary Coded Decimal) value
 *
 * @return decimal equivalent
 */
uint32_t RTCBase::ConvertBCDToDecimal(uint32_t bcd)
{
    return BCDTable[(bcd >> 4) & 0x0f] + (bcd & 0x0f);
}

/**
 * Convert a decimal number in the range 0 to 99 to a 2-digit BCD number.
 *
 * @param decimal value to convert to BCD
 *
 * @return BCD equivalent
 */
uint32_t RTCBase::ConvertDecimalToBCD(uint32_t decimal)
{
    return ((decimal / 10) << 4) + (decimal % 10);
}

