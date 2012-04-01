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
 * Filename:     CVIC.h                                                    *
 *                                                                         *
 ***************************************************************************/

#ifndef VIC_H
#define VIC_H

/**
 *  @defgroup onchip On-Chip Peripherals
 *
 *  @{
 */

/******************************************************************************
 *
 * Function Name: disableIRQ()
 *
 * Description:
 *    This function sets the IRQ disable bit in the status register
 *
 * Calling Sequence: 
 *    void
 *
 * Returns:
 *    previous value of CPSR
 *
 *****************************************************************************/
uint32_t disableIRQ(void);

/******************************************************************************
 *
 * Function Name: enableIRQ()
 *
 * Description:
 *    This function clears the IRQ disable bit in the status register
 *
 * Calling Sequence: 
 *    void
 *
 * Returns:
 *    previous value of CPSR
 *
 *****************************************************************************/
uint32_t enableIRQ(void);

/******************************************************************************
 *
 * Function Name: restoreIRQ()
 *
 * Description:
 *    This function restores the IRQ disable bit in the status register
 *    to the value contained within passed oldCPSR
 *
 * Calling Sequence: 
 *    void
 *
 * Returns:
 *    previous value of CPSR
 *
 *****************************************************************************/
uint32_t restoreIRQ(uint32_t oldCPSR);

/******************************************************************************
 *
 * Function Name: disableFIQ()
 *
 * Description:
 *    This function sets the FIQ disable bit in the status register
 *
 * Calling Sequence: 
 *    void
 *
 * Returns:
 *    previous value of CPSR
 *
 *****************************************************************************/
uint32_t disableFIQ(void);

/******************************************************************************
 *
 * Function Name: enableFIQ()
 *
 * Description:
 *    This function clears the FIQ disable bit in the status register
 *
 * Calling Sequence: 
 *    void
 *
 * Returns:
 *    previous value of CPSR
 *
 *****************************************************************************/
uint32_t enableFIQ(void);

/******************************************************************************
 *
 * Function Name: restoreIRQ()
 *
 * Description:
 *    This function restores the FIQ disable bit in the status register
 *    to the value contained within passed oldCPSR
 *
 * Calling Sequence: 
 *    void
 *
 * Returns:
 *    previous value of CPSR
 *
 *****************************************************************************/
uint32_t restoreFIQ(uint32_t oldCPSR);

/** @} */

#endif
