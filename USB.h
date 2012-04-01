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
 * Filename:     USB.h                                                     *
 *                                                                         *
 ***************************************************************************/

#ifndef USB_H
#define USB_H

/**
 *  @defgroup onchip On-Chip Peripherals
 *
 *  @{
 */

/**
 * Manage the USB (Universal Serial Bus) port.  This object wraps the open
 * source LPC214x USB stack (http://sourceforge.net/projects/lpcusb).
 */
class USB
{
public:
	USB();

	void CheckInterrupt();
	void Enable(uint32_t vendorID, uint32_t productID, const char *manufacturer, const char *product, const char *serialNumber);
    bool_t HasHIDReport();
    USBHIDReport *HIDReport();
    bool_t IsActive();
    bool_t IsConnected();
	void Send (USBHIDReport *report);
    void Debug(const char *text, ...);

	static USB *GetInstance();

private:
    /// Number of bytes in the USB HID Descriptor binary block.
    static const uint32_t DESCRIPTOR_LENGTH = 200;

    uint32_t AddDescriptorString(uint32_t offset, const char *text);
    void DeviceStatus(uint8_t status);
    void InterruptEP(uint8_t ep, uint8_t status);

    /// C style function to call the End Point Interrupt callback in the USB class.
    inline static void InterruptEPCallback(uint8_t ep, uint8_t status) { GetInstance()->InterruptEP(ep, status); };

    /// C style function to call the Device Status callback in the USB class.
    inline static void DeviceStatusCallback(uint8_t status) { GetInstance()->DeviceStatus(status); };

    /// Buffer to hold HID class requests.
    uint8_t abClassReqData[4];

    /// Flag that indicates a write operation is in progress.
    bool_t writeFlag;

    /// FIFO to store incoming HID Reports from the host.
    USBFIFO fifo;

    /// Flag that indicates the USB device is connected.
    bool_t connectFlag;

    /// One-shot flag that indicates the user was notified the device was connected.
    bool_t wasConnectedFlag;

    /// System time when USB connection is ready.
    uint32_t connectReadyTime;

    /// USB HID Descriptor provided to the low-level USB driver.
    uint8_t HIDDescriptor[DESCRIPTOR_LENGTH];
};

/** @} */

#endif // #ifndef USB_H
