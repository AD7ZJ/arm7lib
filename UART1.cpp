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
 * Filename:     UART1.cpp                                                 *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

/// Reserve memory for singleton object.
static UART1 uart1SingletonObject;

void UART1ISR(void)
{
    UART1::GetInstance()->ISR();
}

/**
 *   Pointer to the UART 1 object.
 */
UART1 *UART1::GetInstance()
{
    return &uart1SingletonObject;
}

/**
 *   Enable the required pins for the UART port and configure it for operation.
 *
 * @param baudRate enumerated type that specifies the desired baud rate
 * @param lineControl enumerated type that specifies line control parameters, i.e. number of data bits, stop bits, and parity
 */
void UART1::Enable(BaudRate baudRate, LineControl lineControl)
{
    // Enable the pins that are required for UART1.
    PINSEL0 |= (0x01 << 16) | (0x01 << 18);

    // Reset and enable the FIFOs.
    U1FCR = 0x07;

    // Set the desired baud rate.
    SetLineControl (baudRate, lineControl);

    // Enable the FIFO.
    U1FCR = 0x01;

    // Set the interrupt address.
    VICVectAddr7 = reinterpret_cast <uint32_t> (UART1ISR);

    // Enable the interrupt channel and interrupts.
    VICVectCntl7 = VICVectCntl_ENABLE | VIC_Channel_UART1;
    VICIntEnable = (1 << VIC_Channel_UART1);

    // Enable the receiver interrupts.
    U1IER = UIER_ERBFI;
}

/**
 * Set the UART line control parameters.
 *
 * @param baudRate enumerated type that specifies the desired baud rate
 * @param lineControl enumerated type that specifies line control parameters, i.e. number of data bits, stop bits, and parity
 */
void UART1::SetLineControl (BaudRate baudRate, LineControl lineControl)
{
    uint32_t divisor;

    // Enable access to the baud rate divisor latches.
    U1LCR |= 0x80;

    // Calculate the baud rate divisor based on the peripheral clock and desired rate.
    divisor = SystemControl::GetInstance()->GetPClock() / 16;
    divisor /= static_cast <uint32_t> (baudRate);

    U1DLL = (divisor & 0xff);
    U1DLM = ((divisor >> 8) & 0xff);

    // Set the Line Control Register to the desired mode.
    U1LCR = static_cast<uint8_t> (lineControl);
}

/**
 * Disable UART and set the pins for GPIO.
 */
void UART1::Disable()
{
    PINSEL0 &= ~((0x01 << 16) | (0x01 << 18));

    FIO0CLR = (1 << 8) | (1 << 9);
    FIO0DIR |= (1 << 8) | (1 << 9);
}

/**
 * Write a single character to the UART port.
 *
 * @param text 8-bit value to write
 */
void UART1::WriteChar (uint8_t text)
{
    while (!(U1LSR & 0x20));

    U1THR = text;
}

/**
 * Waits for and returns a single character from the UART port.
 *
 * @return 8-bit character from UART
 */
uint8_t UART1::ReadChar()
{
    return fifo.Read();
}

/**
 * Determine if the UART has a character ready to read.
 *
 * @return true if character in read buffer; otherwise false
 */
bool_t UART1::IsCharReady()
{
    return fifo.HasData();
}

/**
 * Interrupt Service Routine to process receive characters.
 */
void UART1::ISR()
{
    if ((U1IIR & UIIR_ID_MASK) == UIIR_RDA_INT)
        do
        {
            fifo.Write (U1RBR);
        } while (U1LSR & ULSR_RDR);
}
