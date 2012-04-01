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
 * Filename:     MIC-E.h                                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef MIC_ENCODER_H
#define MIC_ENCODER_H

/**
 *  @defgroup library Generic Library Functions
 *
 *  @{
 */

/**
 *  Generate a MIC-E type message
 */
class MICEncoder
{
public:
    void Encode (const GPSData *gps);
    
    const char *GetInformationField();
    const char *GetDestAddress();
    
private:
    /// Destination address as part of the AX.25 message.
    char destAddress[7];
    
    /// Informational text field as part of the AX.25 message.
    char information[20]; 
};

/** @} */

#endif  // #ifndef MIC-MIC_ENCODER_H
