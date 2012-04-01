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
 * Filename:     USBHIDReport.cpp                                          *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

/**
 * Constructor.
 */
USBHIDReport::USBHIDReport()
{
    // Always clear the entire payload in case we don't populate everything.
    // This prevents leaking undesired stack contents.
    std::memset (this->payload, 0x00, sizeof(this->payload));
}

/**
 * Get the message ID contained in the HID report.
 */
uint32_t USBHIDReport::MessageID()
{
    return this->payload[0];
}

/**
 * Get a pointer to the raw HID message contents.  This pointer is typically
 * static_cast to another type that overlays the raw binary block.
 * 
 * @return pointer to raw report data
 */
void *USBHIDReport::Report()
{
    return this->payload + 1;
}

/**
 * Set the 8-bit message ID in the HID report.
 * 
 * @param messageID 8-bit unique ID
 */
void USBHIDReport::MessageID(uint32_t messageID)
{
    this->payload[0] = messageID;
}

/**
 * Get a pointer to the entire contents of the HID Report payload, including
 * the message ID.
 * 
 * @return pointer to HID report raw buffer
 */
uint8_t *USBHIDReport::Payload()
{
    return this->payload;
}

/**
 * Copy the text string to the HID report.  If the string is longer than
 * what is supported by the HID report, it is truncated.
 * 
 * @param text pointer to string to save in HID report
 */
void USBHIDReport::Text (const char *text)
{
    std::strncpy ((char *) this->payload + 1, text, REPORT_SIZE - 2);
    this->payload[REPORT_SIZE - 1] = 0;    
}

