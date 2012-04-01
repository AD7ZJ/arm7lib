###########################################################################
#                                                                         #
#                              ESS, Inc.                                  #
#                                                                         #
#    ESS, Inc. CONFIDENTIAL AND PROPRIETARY.  This source is the sole     #
#    property of ESS, Inc.  Reproduction or utilization of this source    # 
#    in whole or in part is forbidden without the written consent of      #
#    ESS, Inc.                                                            #
#                                                                         #
###########################################################################
#                                                                         #
#            (c) Copyright 1997-2008 -- All Rights Reserved               #
#                                                                         #
###########################################################################
#                                                                         #
#  Filename:     makefile                                                 #
#                                                                         #
###########################################################################


##########################################################################
# Start of default section
#

TRGT = arm-none-eabi-
CC   = $(TRGT)gcc
CPP  = $(TRGT)g++
CP   = $(TRGT)objcopy
AS   = $(TRGT)gcc -x assembler-with-cpp
AR   = $(TRGT)ar

MCU  = arm7tdmi

# List all default C defines here, like -D_DEBUG=1
DDEFS = 

# List all default ASM defines here, like -D_DEBUG=1
DADEFS = 

# List all default directories to look for include files here
DINCDIR = ../usblib

# List the default directory to look for the libraries here
DLIBDIR =

# USB Library directory
USBLIBDIR =
#../usblib/*.o

#
# End of default section
##########################################################################

##########################################################################
# Start of user section
#

# Define project name here
PROJECT = libarm7lib

# List all user C define here, like -D_DEBUG=1
UDEFS = 

# Define ASM defines here
UADEFS = 

# List C source files here
CSRC  = fonts/Tahoma_10_n_nnnn_0_nh.c fonts/Tahoma_10_n_bnnn_0_nh.c fonts/Tahoma_12_n_nnnn_0_nh.c fonts/Tahoma_14_n_bnnn_0_nh.c 

# List CPP source files here
CPPSRC = ADC.cpp DAC.cpp I2C0.cpp I2C1.cpp PWM.cpp SPIBase.cpp SPI0.cpp SPI1.cpp RTC.cpp SystemControl.cpp TimerBase.cpp Timer0.cpp Timer1.cpp 
CPPSRC += UART0.cpp UART1.cpp UARTBase.cpp USB.cpp USBFIFO.cpp USBHIDReport.cpp VIC.cpp WatchDogTimer.cpp
CPPSRC += AD9832.cpp AD9954.cpp AT26DF161A.cpp CC1020.cpp CMX808A.cpp CMX867A.cpp GPSLassen.cpp GPSNavman.cpp GSM0308.cpp ISL12026.cpp LIS302DL.cpp LM73.cpp
CPPSRC += LM92.cpp M25P80.cpp MuxSwitch.cpp NavSwitch.cpp RTCBase.cpp RV8564C2.cpp STX2.cpp SHT11.cpp S1V30120.cpp
CPPSRC += GUI.cpp GUIBase.cpp Optrex15.cpp Optrex19.cpp OSD0201QILK.cpp
CPPSRC += AES.cpp AESKey.cpp Base64Encoder.cpp CRC16.cpp CRC32.cpp FlashBlock.cpp GPSData.cpp MIC-E.cpp Navigation.cpp NMEA.cpp RTCTime.cpp 
CPPSRC += FIFO.cpp UUEncoder.cpp
CPPSRC += AX25.cpp IAP.cpp

# List ASM source files here
ASRC = 

# Define optimisation level here
OPT = -O2

#
# End of user defines
##########################################################################

INCDIR  = $(patsubst %,-I%,$(DINCDIR))
LIBDIR  = $(patsubst %,-L%,$(DLIBDIR))
DEFS    = $(DDEFS) $(UDEFS)
ADEFS   = $(DADEFS) $(UADEFS)
OBJS    = $(ASRC:.s=.o) $(CSRC:.c=.o) $(CPPSRC:.cpp=.o)
MCFLAGS = -mcpu=$(MCU)

ASFLAGS = $(MCFLAGS) -g -gdwarf-2 -Wa,-amhls=$(<:.s=.lst) $(ADEFS)
CPFLAGS = $(MCFLAGS) $(OPT) -gdwarf-2 -fomit-frame-pointer -ffunction-sections -Wall -Wstrict-prototypes -fverbose-asm -Wa,-ahlms=$(<:.c=.lst) $(DEFS)
CPPFLAGS = $(MCFLAGS) $(OPT) -gdwarf-2 -fno-rtti -fno-exceptions -fomit-frame-pointer -ffunction-sections -Wall -fverbose-asm -Wa,-ahlms=$(<:.cpp=.lst) $(DEFS)
ARFLAGS = rcs

# Generate dependency information
CPFLAGS += -MD -MP -MF .dep/$(@F).d
CPPFLAGS += -MD -MP -MF .dep/$(@F).d


##########################################################################
# Start of makefile rules
#
all: $(OBJS) $(PROJECT).a

%o : %c
	$(CC) -c $(CPFLAGS) -I . $(INCDIR) $< -o $@

%o : %cpp
	$(CPP) -c $(CPPFLAGS) -I . $(INCDIR) $< -o $@

%o : %s
	$(AS) -c $(ASFLAGS) $< -o $@

%a: $(OBJS) makefile
	$(AR) $(ARFLAGS) $@ $(OBJS) 
	$(AR) $(ARFLAGS) $@ $(USBLIBDIR)
	
docs:
	doxygen arm7lib.dox
	
loc:
	loc
	
clean:
	-rm -f $(OBJS)
	-rm -f $(PROJECT).a
	-rm -f $(CSRC:.c=.lst)
	-rm -f $(CPPSRC:.cpp=.lst)
	-rm -f $(ASRC:.s=.lst)
	-rm -fR .dep
	-rm -fR html

# 
# Include the dependency files, should be the last of the makefile
#
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)

#
# End of makefile rules
##########################################################################
