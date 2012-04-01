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
 * Filename:     S1V30120.h                                                *
 *                                                                         *
 ***************************************************************************/

#ifndef S1V30120_H
#define S1V30120_H

/**
 *  @defgroup external External Peripherals
 *
 *  @{
 */

/**
 *   Control the Epson TTS (Text-To-Speech) engine.  The S1V30120 is a
 *   Speech Synthesis IC that provides a cost effective solution for adding
 *   Text-To-Speech (TTS) and ADPCM speech processing applications to a
 *   range of portable devices.
 */
class S1V30120
{
public:
    void Enable();
    bool_t IsTTSFinished();
    void Speak (const char *text);

    /**
     * Callback to set the Chip Select control line.
     *
     * @param state false to set line low and enable device; otherwise true
     */
    virtual void IOSetCS(bool_t state);

    /**
     * Callback to clock and read data from the SPI bus.
     *
     * @return 8-bit data read from SPI bus
     */
    virtual uint32_t SPIRead();

    /**
     * Callback to clock and send data over SPI bus.
     *
     * @param data 8-bit data to write
     */
    virtual void SPIWrite(uint32_t data);

    /**
     * Callback to set the reset control line.
     *
     * @param state false to set line low and enable device; otherwise true
     */
    virtual void IOSetReset(bool_t state);

    static S1V30120 *GetInstance();

private:
    /// SPI bus message response state machine.
    typedef enum
    {
        /// Wait for the 0xaa message start character.
        WaitMessageStart,

        /// Message length LSB.
        LengthLSB,

        /// Message length MSB.
        LengthMSB,

        /// Message ID LSB.
        MessageIDLSB,

        /// Message ID MSB.
        MessageIDMSB,

        /// Zero or more payload bytes.
        Payload
    } ResponseStateMachine;

    /// Maximum number of SPI bytes to read waiting for the message start character.
    static const uint32_t WaitResponseByteCount = 8;

    /// Start of message character.
    static const uint32_t MessageStart = 0xaa;

    /// Number of bytes in message response buffer.
    static const uint32_t ResponseBufferLength = 16;

    /// Maximum number of bytes in each firmware download block.
    static const uint32_t MaxDownloadBlock = 2048;

    /// Test and register host hardware interface message ID.
    static const uint32_t TEST_REQUEST = 0x0003;

    /// Version and support information message ID.
    static const uint32_t VERSION_REQUEST = 0x0005;

    /// Configure audio output request message ID.
    static const uint32_t ICS_AUDIO_CONFIG_REQUEST = 0x0008;

    /// Configure the TTS engine message ID.
    static const uint32_t ICS_TTS_CONFIG_REQUEST = 0x0012;

    /// Start the TTS engine message ID.
    static const uint32_t ICS_TTS_SPEAK_REQUEST = 0x0014;

    /// TTS output is finished message ID.
    static const uint32_t ICS_TTS_FINISHED_IND = 0x0021;

    /// Power manager configuration message ID.
    static const uint32_t ICS_PMAN_CONFIG_REQUEST = 0x0062;

    /// Load code image into SRAM message ID.
    static const uint32_t BOOT_LOAD_REQUEST = 0x1000;

    /// Start executing image.
    static const uint32_t RUN_REQUEST = 0x1002;

    void DownloadImage();
    bool_t IsResponse();
    bool_t SendRequest(uint32_t messageID, const void *payload, uint32_t length);

    /// Message ID of the response message.
    uint32_t responseMessageID;

    /// Buffer to hold message response from TTS engine.
    uint8_t response[ResponseBufferLength];

    /// Number of bytes in response buffer.
    uint32_t responseLength;
};

/** @} */

#endif  // #ifndef S1V30120_H

