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
 * Filename:     S1V30120.cpp                                              *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

// Header file that includes the TTS engine firmware.
#include "S1V30120_INIT_DATA_ver2_1_5.h"

/// Reserve memory for the singleton object.
static S1V30120 s1v30120SingletonObject;

/**
 * Get a pointer to the S1V30120 object.
 */
S1V30120 *S1V30120::GetInstance()
{
    return 	&s1v30120SingletonObject;
}

/**
 * Setup the S1V30120 TTS engine.
 */
void S1V30120::Enable()
{
    IOSetCS (true);
    
    IOSetReset(false);
    SystemControl::Sleep(5);

    // Reset the hardware and allow the TTS masked ROM to boot and run.
    IOSetReset(true);
    SystemControl::Sleep(150);
    
    DownloadImage();
}

/**
 * Convert  text to audio speech.
 * 
 * @param text pointer to NULL terminated string
 */
void S1V30120::Speak (const char *text)
{
    uint8_t payload[16];
    char output[300];
    
    output[0] = 0x01;    
    strcpy (output + 1, text);

    responseLength = sizeof(payload);
    SendRequest(ICS_TTS_SPEAK_REQUEST, (uint8_t *) (output), strlen(text) + 2);
}

/**
 * Download the firmware image to the TTS engine. 
 */
void S1V30120::DownloadImage()
{
    uint32_t index, blockLength;
    
    SendRequest(VERSION_REQUEST, NULL, 0);
    
    for (index = 0; index < sizeof(TTSInitData); index += MaxDownloadBlock)
    {
        blockLength = sizeof(TTSInitData) - index;
        
        if (blockLength > MaxDownloadBlock)
            blockLength = MaxDownloadBlock;
        
        SendRequest(BOOT_LOAD_REQUEST, TTSInitData + index, blockLength);
    }
    
    SendRequest(RUN_REQUEST, NULL, 0);
    
    // Allow the downloaded image time to boot and run.
    SystemControl::Sleep(150);
    
    // Enable the TTS SPI interface.
    static const uint8_t TestRequest[] = { 0x01, 0x00,  0x00, 0x00,  0x00, 0x00 };

    SendRequest(TEST_REQUEST, &TestRequest, sizeof(TestRequest));

    
    // Query the version information again to make sure our firmware is running.
    SendRequest(VERSION_REQUEST, NULL, 0);
    
    
    static const uint8_t AudiConfig[] = { 0x00, 0x43, 0x00, 0x01, 0x00, 0, 0x00, 0x01 };
    
    SendRequest(ICS_AUDIO_CONFIG_REQUEST, AudiConfig, sizeof(AudiConfig));
    
   
    static const uint8_t PowerConfig[] = { 0x01, 0x00, 0x01, 0x00 };
    
    SendRequest(ICS_PMAN_CONFIG_REQUEST, PowerConfig, sizeof(PowerConfig));
    
    
    static const uint8_t ConfigRequest[] = { 0x01, 0x07, 0x01, 0x00, 0xc8, 0x00, 0x00, 0x00 };
    
    SendRequest(ICS_TTS_CONFIG_REQUEST, ConfigRequest, sizeof(ConfigRequest));
}

/**
 * Generate a request message for the S1V30120 TTS engine and wait for the response.
 * 
 * @param messageID of the request message to send
 * @param payload pointer to optional message payload bytes of request
 * @param length number of bytes in payload 
 */ 
bool_t S1V30120::SendRequest(uint32_t messageID, const void *payload, uint32_t length)
{
    uint32_t i;

    // Wrap the whole request with the chip select.
    IOSetCS (false);    
    
    // Start message indicator.
    SPIWrite (MessageStart);
    
    // Number of bytes including the header.
    SPIWrite ((length + 4) & 0x00ff);
    SPIWrite ((length + 4) >> 8);

    SPIWrite (messageID & 0x00ff);
    SPIWrite (messageID >> 8);
    
    for (i = 0; i < length; ++i)
        SPIWrite (static_cast<const uint8_t *> (payload)[i]);
    
    return IsResponse();
}

/**
 * One shot that indicates the last message sent to the TTS engine has finished.
 * 
 * @return true when current message is finished; otherwise false
 */
bool_t S1V30120::IsTTSFinished()
{
    if (!IsResponse())
        return false;
    
    // Make sure the response is TTS Finished.
    if (this->responseMessageID == ICS_TTS_FINISHED_IND)
        return true;
    
    return false;
}

/**
 * Wait for a response message from the TTS engine.
 * 
 * @return true if response message processed, otherwise false.
 */ 
bool_t S1V30120::IsResponse()
{
    uint32_t read, count;
    ResponseStateMachine state;

    // Wrap the whole request with the chip select.
    IOSetCS (false);    
    
    state = WaitMessageStart;
    count = 0;
    
    for (;;)
    {
        // Read a byte from the SPI bus.
        read = SPIRead();
        
        // Process based on the internal state machine.
        switch (state)
        {
            case WaitMessageStart:
                if (read == MessageStart)
                    state = LengthLSB;
                else
                {
                    if (++count == WaitResponseByteCount)
                    {
                        this->responseLength = 0x00;
                        IOSetCS (true);
                        return false;
                    }

                    // The TTS engine requires some processing time.  So rather than flood the SPI bus with read requests, we will slow down.
                    // The maximum wait time is 40mS; 5mS sleep * WaitResponseByteCount (8)
                    SystemControl::Sleep(5);
                }
                break;
                
            case LengthLSB:
                this->responseLength = read;
                state = LengthMSB;
                break;
                
            case LengthMSB:
                this->responseLength |= (read << 8);
                state = MessageIDLSB;
                break;
                
            case MessageIDLSB:
                this->responseMessageID = read;
                state = MessageIDMSB;
                break;
                
            case MessageIDMSB:
                this->responseMessageID |= (read << 8);
                state = Payload;
                count = 0;
                this->responseLength -= 4;   

                if (this->responseLength == 0)
                {
                    IOSetCS (true);
                    return true;                    
                }
                break;
                
            case Payload:
                if (count < ResponseBufferLength)
                    this->response[count] = read;
                
                if (++count >= this->responseLength)
                {
                    IOSetCS (true);
                    return true;
                } // END if
                
                break;
        } // END switch

    } // END for
}



