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
 * Filename:     CVIC.cpp                                                  *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

#define IRQ_MASK 0x00000080
#define FIQ_MASK 0x00000040
#define INT_MASK (IRQ_MASK | FIQ_MASK)

static inline unsigned __get_cpsr(void)
{
  unsigned long retval;
  asm volatile (" mrs  %0, cpsr" : "=r" (retval) : /* no inputs */  );
  return retval;
}

static inline void __set_cpsr(unsigned val)
{
  asm volatile (" msr  cpsr, %0" : /* no outputs */ : "r" (val)  );
}

/**
 * Disable the IRQ interrupts.
 * 
 * @return the IRQ mask status before disabling the interrupts
 */
uint32_t disableIRQ(void)
{
    uint32_t _cpsr;

  _cpsr = __get_cpsr();
  __set_cpsr(_cpsr | IRQ_MASK);
  return _cpsr;
}

/**
 * Set the IRQ to the desired state.
 * 
 * @param oldCPSR desired IRQ state
 */
uint32_t restoreIRQ(uint32_t oldCPSR)
{
    uint32_t _cpsr;
    
    _cpsr = __get_cpsr();
    __set_cpsr((_cpsr & ~IRQ_MASK) | (oldCPSR & IRQ_MASK));
    return _cpsr;
}

/**
 * Enable the IRQ interrupts.
 * 
 * @return the IRQ mask status before enabling the interrupts
 */
uint32_t enableIRQ(void)
{
    uint32_t _cpsr;

  _cpsr = __get_cpsr();
  __set_cpsr(_cpsr & ~IRQ_MASK);
  return _cpsr;
}

/**
 * Disable the FIQ interrupt.
 * 
 * @return the FIQ mask status before disabling the interrupt
 */
uint32_t disableFIQ(void)
{
    uint32_t _cpsr;

  _cpsr = __get_cpsr();
  __set_cpsr(_cpsr | FIQ_MASK);
  return _cpsr;
}

/**
 * Set the FIQ to the desired state.
 * 
 * @param oldCPSR desired FIQ state
 */
uint32_t restoreFIQ(uint32_t oldCPSR)
{
    uint32_t _cpsr;

    _cpsr = __get_cpsr();
    __set_cpsr((_cpsr & ~FIQ_MASK) | (oldCPSR & FIQ_MASK));
    return _cpsr;
}
/**
 * Enable the FIQ interrupt.
 * 
 * @return the FIQ mask status before enabling the interrupt
 */
uint32_t enableFIQ(void)
{
    uint32_t _cpsr;

    _cpsr = __get_cpsr();
    __set_cpsr(_cpsr & ~FIQ_MASK);
    return _cpsr;
}
