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
 * Filename:     UART0.cpp                                                 *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

/// Reserve memory for singleton object.
static UART0 uart0SingletonObject;

void UART0ISR(void)
{
    UART0::GetInstance()->ISR();
}

/**
 *   Pointer to the UART 0 object.
 */
UART0 *UART0::GetInstance()
{
    return &uart0SingletonObject;
}

/**
 *   Enable the required pins for the UART port and configure it for operation.
 */
void UART0::Enable(BaudRate baudRate)
{
    uint32_t divisor;

    // Enable the pins that are required for UART0.
    PINSEL0 |= 0x00000005;

    // Reset and enable the FIFOs.
    U0FCR = 0x07;

    // Enable access to the baud rate divisor latches.
    U0LCR |= 0x80;

    // Calculate the baud rate divisor based on the peripheral clock and desired rate.
    divisor = SystemControl::GetInstance()->GetPClock() / 16;
    divisor /= static_cast <uint32_t> (baudRate);

    U0DLL = (divisor & 0xff);
    U0DLM = ((divisor >> 8) & 0xff);

    // Set the Line Control Register for 8N1.
    U0LCR = 0x03;

    // Enable the FIFO.
    U0FCR = 0x01;

    // Set the interrupt address.
    VICVectAddr6 = reinterpret_cast <uint32_t> (UART0ISR);

    // Enable the interrupt channel and interrupts.
    VICVectCntl6 = VICVectCntl_ENABLE | VIC_Channel_UART0;
    VICIntEnable = (1 << VIC_Channel_UART0);

    // Enable the receiver interrupts.
    U0IER = UIER_ERBFI;
}

/**
 * Disable UART and set the pins for GPIO.
 */
void UART0::Disable()
{
    PINSEL0 &= ~0x00000005;
}

/**
 * Write the characters in the NULL terminate string.
 *
 * @param text pointer to NULL terminated string
 */
void UART0::Write (const char *text)
{
    while (*text != 0)
        WriteChar (*text++);
}

/**
 * Write the characters in the NULL terminated string and include CR/LF at the end.
 *
 * @param text pointer to NULL terminated string
 */
void UART0::WriteLine (const char *text, ...)
{
    va_list argList;
    char buffer[200];

    va_start (argList, text);
    vsnprintf (buffer, sizeof(buffer), text, argList);
    va_end (argList);

    Write (buffer);
    Write ("\r\n");
}

/**
 * Write a single character to the UART port.
 *
 * @param text 8-bit value to write
 */
void UART0::WriteChar (uint8_t text)
{
    while (!(U0LSR & 0x20));

    U0THR = text;
}

/**
 * Waits for and returns a single character from the UART port.
 *
 * @return 8-bit character from UART
 */
uint8_t UART0::ReadChar()
{
    return fifo.Read();
}

/**
 * Determine if the UART has a character ready to read.
 *
 * @return true if character in read buffer; otherwise false
 */
bool_t UART0::IsCharReady()
{
    return fifo.HasData();
}

/**
 * Interrupt Service Routine to process receive characters.
 */
void UART0::ISR()
{
    if ((U0IIR & UIIR_ID_MASK) == UIIR_RDA_INT)
        do
        {
            fifo.Write (U0RBR);
        } while (U0LSR & ULSR_RDR);
}
