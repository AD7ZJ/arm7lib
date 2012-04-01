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
 * Filename:     SHT11.cpp                                                 *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

/// CRC lookup table as defined in Rev 1.07 of the 'CRC_Calculation_Humidity_Sensor_E.pdf' application note.
const uint8_t SHT11::CRCTable[] =
{
    0, 49, 98, 83, 196, 245, 166, 151, 185, 136, 219, 234, 125, 76, 31, 46, 67, 114, 33,
    16, 135, 182, 229, 212, 250, 203, 152, 169, 62, 15, 92, 109, 134, 183, 228, 213, 66,
    115, 32, 17, 63, 14, 93, 108, 251, 202, 153, 168, 197, 244, 167, 150, 1, 48, 99, 82,
    124, 77, 30, 47, 184, 137, 218, 235, 61, 12, 95, 110, 249, 200, 155, 170, 132, 181,
    230, 215, 64, 113, 34, 19, 126, 79, 28, 45, 186, 139, 216, 233, 199, 246, 165, 148,
    3, 50, 97, 80, 187, 138, 217, 232, 127, 78, 29, 44, 2, 51, 96, 81, 198, 247, 164, 149,
    248, 201, 154, 171, 60, 13, 94, 111, 65, 112, 35, 18, 133, 180, 231, 214, 122, 75, 24,
    41, 190, 143, 220, 237, 195, 242, 161, 144, 7, 54, 101, 84, 57, 8, 91, 106, 253, 204,
    159, 174, 128, 177, 226, 211, 68, 117, 38, 23, 252, 205, 158, 175, 56, 9, 90, 107, 69,
    116, 39, 22, 129, 176, 227, 210, 191, 142, 221, 236, 123, 74, 25, 40, 6, 55, 100, 85,
    194, 243, 160, 145, 71, 118, 37, 20, 131, 178, 225, 208, 254, 207, 156, 173, 58, 11,
    88, 105, 4, 53, 102, 87, 192, 241, 162, 147, 189, 140, 223, 238, 121, 72, 27, 42, 193,
    240, 163, 146, 5, 52, 103, 86, 120, 73, 26, 43, 188, 141, 222, 239, 130, 179, 224, 209,
    70, 119, 36, 21, 59, 10, 89, 104, 255, 206, 157, 172
};

/// Humidity lookup table.
const uint16_t SHT11::HumidityTable[] =
{
    112, 138, 163, 188, 214, 239, 265, 290, 316, 342,
    368, 394, 420, 446, 473, 499, 526, 552, 579, 606,
    633, 660, 687, 715, 742, 770, 798, 825, 853, 881,
    909, 938, 966, 995, 1023, 1052, 1081, 1110, 1140, 1169,
    1198, 1228, 1258, 1288, 1318, 1348, 1379, 1409, 1440, 1471,
    1502, 1533, 1565, 1596, 1628, 1660, 1692, 1725, 1757, 1790,
    1823, 1856, 1889, 1923, 1956, 1990, 2024, 2059, 2093, 2128,
    2163, 2199, 2234, 2270, 2306, 2343, 2379, 2416, 2454, 2491,
    2529, 2567, 2605, 2644, 2683, 2723, 2762, 2803, 2843, 2884,
    2925, 2967, 3009, 3051, 3094, 3138, 3182, 3226, 3271, 3316
};


/// Reserve memory for singleton object.
static SHT11 sht1xSingletonObject;

/**
 *  Get a pointer to the SHT11 object.
 */
SHT11 *SHT11::GetInstance()
{
    return  &sht1xSingletonObject;
}

/**
 *  Set the I/O and ports to utilize the SHT-11 sensor.
 */
void SHT11::Enable()
{
    uint8_t i;

    IOSetDataDirection (true);
    IOSetData (true);
    IOSetClock (false);

    // Send the sequence to reset the sensor.
    for (i = 0; i < 12; ++i)
        StrobeClock();
}

/**
 *   Read the current temperature in degrees F.
 *
 *   @return temperature in units of 0.1 degrees F
 */
int32_t SHT11::ReadTemp()
{
    // Convert using scaled integers.  The calculation is based on degF = -39.66 + 0.018 * SensorValue.  See SHT11.xls in unit_test for additional information.
    return (((SendCommand (0x03) * 2359) / 1311) - 3966) / 10;
}

/**
 *   Read the current humidity in percent relative humidity.
 *
 *   @return humidity in percent 0 to 100
 */
uint32_t SHT11::ReadHum()
{
    uint32_t i, value;

    // Convert using a lookup table.  The calculation is based on hum = -4  + (0.0405 * SensorValue) - (2.8e-6 * SensorValue * SensorValue).  See SHT11.xls in unit_test for additional information.
    value = SendCommand (0x05);

    for (i = 0; i <= 100; ++i)
        if (value < this->HumidityTable[i])
            return i;

    return 100;
}

/**
 *   Calculate the CRC of Humidity & Temperature sensor data stream.
 *
 *   @param crc initial CRC
 *   @param value to add to the CRC calculation
 *
 *   @return new CRC value
 */
uint32_t SHT11::CRC (uint32_t crc, uint32_t value)
{
    return CRCTable[crc ^ value];
}

/**
 *   Reverse the bit order MSB to LSB of a byte (8-bit value).
 *
 *   @param value to reverse
 *
 *   @return bit reversed value
 */
uint32_t SHT11::ReverseBits (uint32_t value)
{
    uint32_t i, revValue;

    revValue = 0x00;

    for (i = 0; i < 8; ++i)
    {
        revValue = revValue >> 1;

        if ((value & 0x80) == 0x80)
            revValue |= 0x80;

        value = value << 1;
    } // END for

    return revValue;
}

/**
 *   Send a command, read the 16-bit return value, and read/validate the CRC.
 *
 *   @param command of desired operation
 *
 *   @return validated 16-bit value; otherwise 0xffff if failure detected
 */
uint32_t SHT11::SendCommand (uint32_t command)
{
    uint32_t i, crc, value;
    uint32_t data, waitCount;

    // Only the lower 5-bits of the command are valid.
    command = command & 0x1f;

    // The initial CRC for a new calculation is 0x00.  Start the CRC calculation with the command.
    crc = CRC (0x00, command);

    // Signal that we are starting a new command sequence.
    TransmitStart();

    // Bit-bang the command.
    for (i = 0; i < 8; ++i)
    {
        IOSetData ((command & 0x80) == 0x80 ? true : false);
        command = command << 1;
        StrobeClock();
    } // END for

    // Reverse the data line to input.
    IOSetDataDirection (false);
    StrobeClock();

    waitCount = 0;

    while (IOGetData())
    {
        if (++waitCount > 300)
            return 0xffff;

        SystemControl::Sleep(1);
    } // END while

    value = ReadAckByte (true);
    data = (value << 8);
    crc = CRC (crc, value);

    value = ReadAckByte (true);
    data |= value;
    crc = CRC (crc, value);

    if (ReverseBits(crc) != ReadAckByte(false))
        return 0xfffe;

    return data;
}

/**
 *  Read an 8-bit data value and optionally ACK the reception.
 *
 *  @param ackFlag true to ack reception of 8-bit value
 *
 *  @return 8-bit data value
 */
uint32_t SHT11::ReadAckByte(bool_t ackFlag)
{
    uint32_t i, data;

    data = 0x00;

    // Set the data pin as input.
    IOSetDataDirection (false);

    // Toggle the clock as we read each data bit.
    for (i = 0; i < 8; ++i)
    {
        data = data << 1;

        IOSetClock (true);
        data = data | (IOGetData() ? 0x01 : 0x00);
        IOSetClock (false);
    } // END for

    // Set the data as an output.
    IOSetDataDirection (true);

    // Set the data output based on the desired ACK action.
    if (ackFlag)
        IOSetData (false);
    else
        IOSetData (true);

    // Toggle the clock
    StrobeClock();

    return data;
}

/**
 *   Strobe the clock high and then low.
 */
void SHT11::StrobeClock()
{
    IOSetClock (true);
    IOSetClock (false);
}

/**
 *   Send the sequence the marks the start of a transmit sequence.
 */
void SHT11::TransmitStart()
{
    IOSetClock (true);
    IOSetData (false);
    IOSetClock (false);
    IOSetClock (true);
    IOSetData (true);
    IOSetClock (false);
}
