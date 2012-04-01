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
 * Filename:     USBHIDReport.h                                            *
 *                                                                         *
 ***************************************************************************/

#ifndef USBHIDREPORT_H
#define USBHIDREPORT_H

/**
 *  @defgroup onchip On-Chip Peripherals
 *
 *  @{
 */

/**
 * Base class for the USB HID Report.
 */
class USBHIDReport
{
public:
	USBHIDReport();
	uint32_t MessageID();
	void MessageID (uint32_t messageID);
	uint8_t *Payload();
	void *Report();
	void Text (const char *text);
	
   /// Number of bytes in the HID Report.
    static const uint32_t REPORT_SIZE = 64;
	
private:	
	/// Buffer that contains the report.
    uint8_t payload[REPORT_SIZE];
};

/** @} */

#endif // #ifndef USBHIDREPORT_H
