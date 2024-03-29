/* ============================================================================ */
/* Copyright (c) 2020, Texas Instruments Incorporated                           */
/*  All rights reserved.                                                        */
/*                                                                              */
/*  Redistribution and use in source and binary forms, with or without          */
/*  modification, are permitted provided that the following conditions          */
/*  are met:                                                                    */
/*                                                                              */
/*  *  Redistributions of source code must retain the above copyright           */
/*     notice, this list of conditions and the following disclaimer.            */
/*                                                                              */
/*  *  Redistributions in binary form must reproduce the above copyright        */
/*     notice, this list of conditions and the following disclaimer in the      */
/*     documentation and/or other materials provided with the distribution.     */
/*                                                                              */
/*  *  Neither the name of Texas Instruments Incorporated nor the names of      */
/*     its contributors may be used to endorse or promote products derived      */
/*     from this software without specific prior written permission.            */
/*                                                                              */
/*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" */
/*  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,       */
/*  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR      */
/*  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR            */
/*  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,       */
/*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,         */
/*  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; */
/*  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,    */
/*  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR     */
/*  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,              */
/*  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                          */
/* ============================================================================ */

/******************************************************************************/
/* Legacy Header File                                                         */
/* Not recommended for use in new projects.                                   */
/* Please use the msp430.h file or the device specific header file            */
/******************************************************************************/

/********************************************************************
*
* Standard register and bit definitions for the Texas Instruments
* MSP430 microcontroller.
*
* This file supports assembler and C development for
* MSP430x20x3 devices.
*
* Texas Instruments, Version 1.3
*
* Rev. 1.0, Setup
* Rev. 1.1, Removed some TACCx2 definition on TA2 module
* Rev. 1.2, Replaced USIIFGDC with USIIFGCC
* Rev. 1.3, added definitions for Interrupt Vectors xxIV
*
********************************************************************/

#ifndef __msp430x20x3
#define __msp430x20x3

#define __MSP430_HEADER_VERSION__ 1209

#ifdef __cplusplus
extern "C" {
#endif


/*----------------------------------------------------------------------------*/
/* PERIPHERAL FILE MAP                                                        */
/*----------------------------------------------------------------------------*/

/* External references resolved by a device-specific linker command file */
#define SFR_8BIT(address)   extern volatile unsigned char address
#define SFR_16BIT(address)  extern volatile unsigned int address
#define SFR_32BIT(address)  extern volatile unsigned long address


/************************************************************
* STANDARD BITS
************************************************************/

#define BIT0                   (0x0001)
#define BIT1                   (0x0002)
#define BIT2                   (0x0004)
#define BIT3                   (0x0008)
#define BIT4                   (0x0010)
#define BIT5                   (0x0020)
#define BIT6                   (0x0040)
#define BIT7                   (0x0080)
#define BIT8                   (0x0100)
#define BIT9                   (0x0200)
#define BITA                   (0x0400)
#define BITB                   (0x0800)
#define BITC                   (0x1000)
#define BITD                   (0x2000)
#define BITE                   (0x4000)
#define BITF                   (0x8000)

/************************************************************
* STATUS REGISTER BITS
************************************************************/

#define C                      (0x0001)
#define Z                      (0x0002)
#define N                      (0x0004)
#define V                      (0x0100)
#define GIE                    (0x0008)
#define CPUOFF                 (0x0010)
#define OSCOFF                 (0x0020)
#define SCG0                   (0x0040)
#define SCG1                   (0x0080)

/* Low Power Modes coded with Bits 4-7 in SR */

#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define LPM0                   (CPUOFF)
#define LPM1                   (SCG0+CPUOFF)
#define LPM2                   (SCG1+CPUOFF)
#define LPM3                   (SCG1+SCG0+CPUOFF)
#define LPM4                   (SCG1+SCG0+OSCOFF+CPUOFF)
/* End #defines for assembler */

#else /* Begin #defines for C */
#define LPM0_bits              (CPUOFF)
#define LPM1_bits              (SCG0+CPUOFF)
#define LPM2_bits              (SCG1+CPUOFF)
#define LPM3_bits              (SCG1+SCG0+CPUOFF)
#define LPM4_bits              (SCG1+SCG0+OSCOFF+CPUOFF)

#include "in430.h"
#include <intrinsics.h>

#define LPM0      __bis_SR_register(LPM0_bits)         /* Enter Low Power Mode 0 */
#define LPM0_EXIT __bic_SR_register_on_exit(LPM0_bits) /* Exit Low Power Mode 0 */
#define LPM1      __bis_SR_register(LPM1_bits)         /* Enter Low Power Mode 1 */
#define LPM1_EXIT __bic_SR_register_on_exit(LPM1_bits) /* Exit Low Power Mode 1 */
#define LPM2      __bis_SR_register(LPM2_bits)         /* Enter Low Power Mode 2 */
#define LPM2_EXIT __bic_SR_register_on_exit(LPM2_bits) /* Exit Low Power Mode 2 */
#define LPM3      __bis_SR_register(LPM3_bits)         /* Enter Low Power Mode 3 */
#define LPM3_EXIT __bic_SR_register_on_exit(LPM3_bits) /* Exit Low Power Mode 3 */
#define LPM4      __bis_SR_register(LPM4_bits)         /* Enter Low Power Mode 4 */
#define LPM4_EXIT __bic_SR_register_on_exit(LPM4_bits) /* Exit Low Power Mode 4 */
#endif /* End #defines for C */

/************************************************************
* PERIPHERAL FILE MAP
************************************************************/

/************************************************************
* SPECIAL FUNCTION REGISTER ADDRESSES + CONTROL BITS
************************************************************/

SFR_8BIT(IE1);                                /* Interrupt Enable 1 */
#define WDTIE                  (0x01)         /* Watchdog Interrupt Enable */
#define OFIE                   (0x02)         /* Osc. Fault  Interrupt Enable */
#define NMIIE                  (0x10)         /* NMI Interrupt Enable */
#define ACCVIE                 (0x20)         /* Flash Access Violation Interrupt Enable */

SFR_8BIT(IFG1);                               /* Interrupt Flag 1 */
#define WDTIFG                 (0x01)         /* Watchdog Interrupt Flag */
#define OFIFG                  (0x02)         /* Osc. Fault Interrupt Flag */
#define PORIFG                 (0x04)         /* Power On Interrupt Flag */
#define RSTIFG                 (0x08)         /* Reset Interrupt Flag */
#define NMIIFG                 (0x10)         /* NMI Interrupt Flag */

/************************************************************
* Basic Clock Module
************************************************************/
#define __MSP430_HAS_BC2__                    /* Definition to show that Module is available */

SFR_8BIT(DCOCTL);                             /* DCO Clock Frequency Control */
SFR_8BIT(BCSCTL1);                            /* Basic Clock System Control 1 */
SFR_8BIT(BCSCTL2);                            /* Basic Clock System Control 2 */
SFR_8BIT(BCSCTL3);                            /* Basic Clock System Control 3 */

#define MOD0                   (0x01)         /* Modulation Bit 0 */
#define MOD1                   (0x02)         /* Modulation Bit 1 */
#define MOD2                   (0x04)         /* Modulation Bit 2 */
#define MOD3                   (0x08)         /* Modulation Bit 3 */
#define MOD4                   (0x10)         /* Modulation Bit 4 */
#define DCO0                   (0x20)         /* DCO Select Bit 0 */
#define DCO1                   (0x40)         /* DCO Select Bit 1 */
#define DCO2                   (0x80)         /* DCO Select Bit 2 */

#define RSEL0                  (0x01)         /* Range Select Bit 0 */
#define RSEL1                  (0x02)         /* Range Select Bit 1 */
#define RSEL2                  (0x04)         /* Range Select Bit 2 */
#define RSEL3                  (0x08)         /* Range Select Bit 3 */
#define DIVA0                  (0x10)         /* ACLK Divider 0 */
#define DIVA1                  (0x20)         /* ACLK Divider 1 */
#define XTS                    (0x40)         /* LFXTCLK 0:Low Freq. / 1: High Freq. */
#define XT2OFF                 (0x80)         /* Enable XT2CLK */

#define DIVA_0                 (0x00)         /* ACLK Divider 0: /1 */
#define DIVA_1                 (0x10)         /* ACLK Divider 1: /2 */
#define DIVA_2                 (0x20)         /* ACLK Divider 2: /4 */
#define DIVA_3                 (0x30)         /* ACLK Divider 3: /8 */

#define DIVS0                  (0x02)         /* SMCLK Divider 0 */
#define DIVS1                  (0x04)         /* SMCLK Divider 1 */
#define SELS                   (0x08)         /* SMCLK Source Select 0:DCOCLK / 1:XT2CLK/LFXTCLK */
#define DIVM0                  (0x10)         /* MCLK Divider 0 */
#define DIVM1                  (0x20)         /* MCLK Divider 1 */
#define SELM0                  (0x40)         /* MCLK Source Select 0 */
#define SELM1                  (0x80)         /* MCLK Source Select 1 */

#define DIVS_0                 (0x00)         /* SMCLK Divider 0: /1 */
#define DIVS_1                 (0x02)         /* SMCLK Divider 1: /2 */
#define DIVS_2                 (0x04)         /* SMCLK Divider 2: /4 */
#define DIVS_3                 (0x06)         /* SMCLK Divider 3: /8 */

#define DIVM_0                 (0x00)         /* MCLK Divider 0: /1 */
#define DIVM_1                 (0x10)         /* MCLK Divider 1: /2 */
#define DIVM_2                 (0x20)         /* MCLK Divider 2: /4 */
#define DIVM_3                 (0x30)         /* MCLK Divider 3: /8 */

#define SELM_0                 (0x00)         /* MCLK Source Select 0: DCOCLK */
#define SELM_1                 (0x40)         /* MCLK Source Select 1: DCOCLK */
#define SELM_2                 (0x80)         /* MCLK Source Select 2: XT2CLK/LFXTCLK */
#define SELM_3                 (0xC0)         /* MCLK Source Select 3: LFXTCLK */

#define LFXT1OF                (0x01)         /* Low/high Frequency Oscillator Fault Flag */
#define XT2OF                  (0x02)         /* High frequency oscillator 2 fault flag */
#define XCAP0                  (0x04)         /* XIN/XOUT Cap 0 */
#define XCAP1                  (0x08)         /* XIN/XOUT Cap 1 */
#define LFXT1S0                (0x10)         /* Mode 0 for LFXT1 (XTS = 0) */
#define LFXT1S1                (0x20)         /* Mode 1 for LFXT1 (XTS = 0) */
#define XT2S0                  (0x40)         /* Mode 0 for XT2 */
#define XT2S1                  (0x80)         /* Mode 1 for XT2 */

#define XCAP_0                 (0x00)         /* XIN/XOUT Cap : 0 pF */
#define XCAP_1                 (0x04)         /* XIN/XOUT Cap : 6 pF */
#define XCAP_2                 (0x08)         /* XIN/XOUT Cap : 10 pF */
#define XCAP_3                 (0x0C)         /* XIN/XOUT Cap : 12.5 pF */

#define LFXT1S_0               (0x00)         /* Mode 0 for LFXT1 : Normal operation */
#define LFXT1S_1               (0x10)         /* Mode 1 for LFXT1 : Reserved */
#define LFXT1S_2               (0x20)         /* Mode 2 for LFXT1 : VLO */
#define LFXT1S_3               (0x30)         /* Mode 3 for LFXT1 : Digital input signal */

#define XT2S_0                 (0x00)         /* Mode 0 for XT2 : 0.4 - 1 MHz */
#define XT2S_1                 (0x40)         /* Mode 1 for XT2 : 1 - 4 MHz */
#define XT2S_2                 (0x80)         /* Mode 2 for XT2 : 2 - 16 MHz */
#define XT2S_3                 (0xC0)         /* Mode 3 for XT2 : Digital input signal */

/*************************************************************
* Flash Memory
*************************************************************/
#define __MSP430_HAS_FLASH2__                 /* Definition to show that Module is available */

SFR_16BIT(FCTL1);                             /* FLASH Control 1 */
SFR_16BIT(FCTL2);                             /* FLASH Control 2 */
SFR_16BIT(FCTL3);                             /* FLASH Control 3 */

#define FRKEY                  (0x9600)       /* Flash key returned by read */
#define FWKEY                  (0xA500)       /* Flash key for write */
#define FXKEY                  (0x3300)       /* for use with XOR instruction */

#define ERASE                  (0x0002)       /* Enable bit for Flash segment erase */
#define MERAS                  (0x0004)       /* Enable bit for Flash mass erase */
#define WRT                    (0x0040)       /* Enable bit for Flash write */
#define BLKWRT                 (0x0080)       /* Enable bit for Flash segment write */
#define SEGWRT                 (0x0080)       /* old definition */ /* Enable bit for Flash segment write */

#define FN0                    (0x0001)       /* Divide Flash clock by 1 to 64 using FN0 to FN5 according to: */
#define FN1                    (0x0002)       /*  32*FN5 + 16*FN4 + 8*FN3 + 4*FN2 + 2*FN1 + FN0 + 1 */
#ifndef FN2
#define FN2                    (0x0004)
#endif
#ifndef FN3
#define FN3                    (0x0008)
#endif
#ifndef FN4
#define FN4                    (0x0010)
#endif
#define FN5                    (0x0020)
#define FSSEL0                 (0x0040)       /* Flash clock select 0 */        /* to distinguish from USART SSELx */
#define FSSEL1                 (0x0080)       /* Flash clock select 1 */

#define FSSEL_0                (0x0000)       /* Flash clock select: 0 - ACLK */
#define FSSEL_1                (0x0040)       /* Flash clock select: 1 - MCLK */
#define FSSEL_2                (0x0080)       /* Flash clock select: 2 - SMCLK */
#define FSSEL_3                (0x00C0)       /* Flash clock select: 3 - SMCLK */

#define BUSY                   (0x0001)       /* Flash busy: 1 */
#define KEYV                   (0x0002)       /* Flash Key violation flag */
#define ACCVIFG                (0x0004)       /* Flash Access violation flag */
#define WAIT                   (0x0008)       /* Wait flag for segment write */
#define LOCK                   (0x0010)       /* Lock bit: 1 - Flash is locked (read only) */
#define EMEX                   (0x0020)       /* Flash Emergency Exit */
#define LOCKA                  (0x0040)       /* Segment A Lock bit: read = 1 - Segment is locked (read only) */
#define FAIL                   (0x0080)       /* Last Program or Erase failed */

/************************************************************
* DIGITAL I/O Port1/2 Pull up / Pull down Resistors
************************************************************/
#define __MSP430_HAS_PORT1_R__                /* Definition to show that Module is available */
#define __MSP430_HAS_PORT2_R__                /* Definition to show that Module is available */

#define __MSP430_HAS_P1SEL__                  /* Define for DriverLib */
#define __MSP430_HAS_P2SEL__                  /* Define for DriverLib */

SFR_8BIT(P1IN);                               /* Port 1 Input */
SFR_8BIT(P1OUT);                              /* Port 1 Output */
SFR_8BIT(P1DIR);                              /* Port 1 Direction */
SFR_8BIT(P1IFG);                              /* Port 1 Interrupt Flag */
SFR_8BIT(P1IES);                              /* Port 1 Interrupt Edge Select */
SFR_8BIT(P1IE);                               /* Port 1 Interrupt Enable */
SFR_8BIT(P1SEL);                              /* Port 1 Selection */
SFR_8BIT(P1REN);                              /* Port 1 Resistor Enable */

SFR_8BIT(P2IN);                               /* Port 2 Input */
SFR_8BIT(P2OUT);                              /* Port 2 Output */
SFR_8BIT(P2DIR);                              /* Port 2 Direction */
SFR_8BIT(P2IFG);                              /* Port 2 Interrupt Flag */
SFR_8BIT(P2IES);                              /* Port 2 Interrupt Edge Select */
SFR_8BIT(P2IE);                               /* Port 2 Interrupt Enable */
SFR_8BIT(P2SEL);                              /* Port 2 Selection */
SFR_8BIT(P2REN);                              /* Port 2 Resistor Enable */

/************************************************************
* SD16_A1 - Sigma Delta 16 Bit
************************************************************/
#define __MSP430_HAS_SD16_A1__                /* Definition to show that Module is available */

SFR_8BIT(SD16INCTL0);                         /* SD16 Input Control Register Channel 0 */
SFR_8BIT(SD16AE);                             /* SD16 Analog Input Enable Register */
SFR_8BIT(SD16CONF0);                          /* SD16 Internal Configuration Register 0 */
SFR_8BIT(SD16CONF1);                          /* SD16 Internal Configuration Register 1 */
                                      /* Please use only the recommended settings */

SFR_16BIT(SD16CTL);                           /* Sigma Delta ADC 16 Control Register */
SFR_16BIT(SD16CCTL0);                         /* SD16 Channel 0 Control Register */
SFR_16BIT(SD16IV);                            /* SD16 Interrupt Vector Register */
SFR_16BIT(SD16MEM0);                          /* SD16 Channel 0 Conversion Memory */

/* SD16AE */
#define SD16AE0                (0x0001)       /* SD16 External Input Enable 0 */
#define SD16AE1                (0x0002)       /* SD16 External Input Enable 1 */
#define SD16AE2                (0x0004)       /* SD16 External Input Enable 2 */
#define SD16AE3                (0x0008)       /* SD16 External Input Enable 3 */
#define SD16AE4                (0x0010)       /* SD16 External Input Enable 4 */
#define SD16AE5                (0x0020)       /* SD16 External Input Enable 5 */
#define SD16AE6                (0x0040)       /* SD16 External Input Enable 6 */
#define SD16AE7                (0x0080)       /* SD16 External Input Enable 7 */

/* SD16INCTLx */
#define SD16INCH0              (0x0001)       /* SD16 Input Channel select 0 */
#define SD16INCH1              (0x0002)       /* SD16 Input Channel select 1 */
#define SD16INCH2              (0x0004)       /* SD16 Input Channel select 2 */
#define SD16GAIN0              (0x0008)       /* SD16 Input Pre-Amplifier Gain Select 0 */
#define SD16GAIN1              (0x0010)       /* SD16 Input Pre-Amplifier Gain Select 1 */
#define SD16GAIN2              (0x0020)       /* SD16 Input Pre-Amplifier Gain Select 2 */
#define SD16INTDLY0            (0x0040)       /* SD16 Interrupt Delay after 1.Conversion 0 */
#define SD16INTDLY1            (0x0080)       /* SD16 Interrupt Delay after 1.Conversion 1 */

#define SD16GAIN_1             (0x0000)       /* SD16 Input Pre-Amplifier Gain Select *1  */
#define SD16GAIN_2             (0x0008)       /* SD16 Input Pre-Amplifier Gain Select *2  */
#define SD16GAIN_4             (0x0010)       /* SD16 Input Pre-Amplifier Gain Select *4  */
#define SD16GAIN_8             (0x0018)       /* SD16 Input Pre-Amplifier Gain Select *8  */
#define SD16GAIN_16            (0x0020)       /* SD16 Input Pre-Amplifier Gain Select *16 */
#define SD16GAIN_32            (0x0028)       /* SD16 Input Pre-Amplifier Gain Select *32 */

#define SD16INCH_0             (0x0000)       /* SD16 Input Channel select A0 */
#define SD16INCH_1             (0x0001)       /* SD16 Input Channel select A1 */
#define SD16INCH_2             (0x0002)       /* SD16 Input Channel select A2 */
#define SD16INCH_3             (0x0003)       /* SD16 Input Channel select A3 */
#define SD16INCH_4             (0x0004)       /* SD16 Input Channel select A4 */
#define SD16INCH_5             (0x0005)       /* SD16 Input Channel select Vcc divider */
#define SD16INCH_6             (0x0006)       /* SD16 Input Channel select Temp */
#define SD16INCH_7             (0x0007)       /* SD16 Input Channel select Offset */

#define SD16INTDLY_0           (0x0000)       /* SD16 Interrupt Delay: Int. after 4.Conversion  */
#define SD16INTDLY_1           (0x0040)       /* SD16 Interrupt Delay: Int. after 3.Conversion  */
#define SD16INTDLY_2           (0x0080)       /* SD16 Interrupt Delay: Int. after 2.Conversion  */
#define SD16INTDLY_3           (0x00C0)       /* SD16 Interrupt Delay: Int. after 1.Conversion  */

/* SD16CTL */
#define SD16OVIE               (0x0002)       /* SD16 Overflow Interupt Enable */
#define SD16REFON              (0x0004)       /* SD16 Switch internal Reference on */
#define SD16VMIDON             (0x0008)       /* SD16 Switch Vmid Buffer on */
#define SD16SSEL0              (0x0010)       /* SD16 Clock Source Select 0 */
#define SD16SSEL1              (0x0020)       /* SD16 Clock Source Select 1 */
#define SD16DIV0               (0x0040)       /* SD16 Clock Divider Select 0 */
#define SD16DIV1               (0x0080)       /* SD16 Clock Divider Select 1 */
#define SD16LP                 (0x0100)       /* SD16 Low Power Mode Enable */
#define SD16XDIV0              (0x0200)       /* SD16 2.Clock Divider Select 0 */
#define SD16XDIV1              (0x0400)       /* SD16 2.Clock Divider Select 1 */
//#define SD16XDIV2           (0x0800)  /* SD16 2.Clock Divider Select 2 */

#define SD16DIV_0              (0x0000)       /* SD16 Clock Divider Select /1 */
#define SD16DIV_1              (SD16DIV0)     /* SD16 Clock Divider Select /2 */
#define SD16DIV_2              (SD16DIV1)     /* SD16 Clock Divider Select /4 */
#define SD16DIV_3           (SD16DIV0+SD16DIV1)    /* SD16 Clock Divider Select /8 */

#define SD16XDIV_0             (0x0000)       /* SD16 2.Clock Divider Select /1 */
#define SD16XDIV_1             (SD16XDIV0)    /* SD16 2.Clock Divider Select /3 */
#define SD16XDIV_2             (SD16XDIV1)    /* SD16 2.Clock Divider Select /16 */
#define SD16XDIV_3          (SD16XDIV0+SD16XDIV1)  /* SD16 2.Clock Divider Select /48 */

#define SD16SSEL_0             (0x0000)       /* SD16 Clock Source Select MCLK  */
#define SD16SSEL_1             (SD16SSEL0)    /* SD16 Clock Source Select SMCLK */
#define SD16SSEL_2             (SD16SSEL1)    /* SD16 Clock Source Select ACLK  */
#define SD16SSEL_3          (SD16SSEL0+SD16SSEL1)  /* SD16 Clock Source Select TACLK */

/* SD16CCTLx */
//#define RESERVED            (0x0001)  /* RESERVED */
#define SD16SC                 (0x0002)       /* SD16 Start Conversion */
#define SD16IFG                (0x0004)       /* SD16 Channel x Interrupt Flag */
#define SD16IE                 (0x0008)       /* SD16 Channel x Interrupt Enable */
#define SD16DF                 (0x0010)       /* SD16 Channel x Data Format: 0:Unipolar/1:Bipolar */
#define SD16OVIFG              (0x0020)       /* SD16 Channel x Overflow Interrupt Flag */
#define SD16LSBACC             (0x0040)       /* SD16 Channel x Access LSB of ADC */
#define SD16LSBTOG             (0x0080)       /* SD16 Channel x Toggle LSB Output of ADC */
#define SD16OSR0               (0x0100)       /* SD16 Channel x OverSampling Ratio 0 */
#define SD16OSR1               (0x0200)       /* SD16 Channel x OverSampling Ratio 1 */
#define SD16SNGL               (0x0400)       /* SD16 Channel x Single Conversion On/Off */
#define SD16XOSR               (0x0800)       /* SD16 Channel x Extended OverSampling Ratio */
#define SD16UNI                (0x1000)       /* SD16 Channel x Bipolar(0) / Unipolar(1) Mode */

#define SD16OSR_1024        (SD16OSR0+SD16XOSR)     /* SD16 Channel x OverSampling Ratio 1024 */
#define SD16OSR_512            (SD16XOSR)     /* SD16 Channel x OverSampling Ratio 512 */
#define SD16OSR_256            (0x0000)       /* SD16 Channel x OverSampling Ratio 256 */
#define SD16OSR_128            (SD16OSR0)     /* SD16 Channel x OverSampling Ratio 128 */
#define SD16OSR_64             (SD16OSR1)     /* SD16 Channel x OverSampling Ratio  64 */
#define SD16OSR_32          (SD16OSR0+SD16OSR1)     /* SD16 Channel x OverSampling Ratio  32 */

/* SD16IV Definitions */
#define SD16IV_NONE            (0x0000)       /* No Interrupt pending */
#define SD16IV_SD16OVIFG       (0x0002)       /* SD16OVIFG */
#define SD16IV_SD16MEM0        (0x0004)       /* SD16MEM0 SD16IFG */

/************************************************************
* Timer A2
************************************************************/
#define __MSP430_HAS_TA2__                    /* Definition to show that Module is available */

SFR_16BIT(TAIV);                              /* Timer A Interrupt Vector Word */
SFR_16BIT(TACTL);                             /* Timer A Control */
SFR_16BIT(TACCTL0);                           /* Timer A Capture/Compare Control 0 */
SFR_16BIT(TACCTL1);                           /* Timer A Capture/Compare Control 1 */
SFR_16BIT(TAR);                               /* Timer A Counter Register */
SFR_16BIT(TACCR0);                            /* Timer A Capture/Compare 0 */
SFR_16BIT(TACCR1);                            /* Timer A Capture/Compare 1 */

/* Alternate register names */
#define CCTL0                  TACCTL0        /* Timer A Capture/Compare Control 0 */
#define CCTL1                  TACCTL1        /* Timer A Capture/Compare Control 1 */
#define CCR0                   TACCR0         /* Timer A Capture/Compare 0 */
#define CCR1                   TACCR1         /* Timer A Capture/Compare 1 */
#define CCTL0_                 TACCTL0_       /* Timer A Capture/Compare Control 0 */
#define CCTL1_                 TACCTL1_       /* Timer A Capture/Compare Control 1 */
#define CCR0_                  TACCR0_        /* Timer A Capture/Compare 0 */
#define CCR1_                  TACCR1_        /* Timer A Capture/Compare 1 */
/* Alternate register names - 5xx style */
#define TA0IV                  TAIV           /* Timer A Interrupt Vector Word */
#define TA0CTL                 TACTL          /* Timer A Control */
#define TA0CCTL0               TACCTL0        /* Timer A Capture/Compare Control 0 */
#define TA0CCTL1               TACCTL1        /* Timer A Capture/Compare Control 1 */
#define TA0R                   TAR            /* Timer A Counter Register */
#define TA0CCR0                TACCR0         /* Timer A Capture/Compare 0 */
#define TA0CCR1                TACCR1         /* Timer A Capture/Compare 1 */
#define TA0IV_                 TAIV_          /* Timer A Interrupt Vector Word */
#define TA0CTL_                TACTL_         /* Timer A Control */
#define TA0CCTL0_              TACCTL0_       /* Timer A Capture/Compare Control 0 */
#define TA0CCTL1_              TACCTL1_       /* Timer A Capture/Compare Control 1 */
#define TA0R_                  TAR_           /* Timer A Counter Register */
#define TA0CCR0_               TACCR0_        /* Timer A Capture/Compare 0 */
#define TA0CCR1_               TACCR1_        /* Timer A Capture/Compare 1 */
#define TIMER0_A1_VECTOR       TIMERA1_VECTOR /* Int. Vector: Timer A CC1-2, TA */
#define TIMER0_A0_VECTOR       TIMERA0_VECTOR /* Int. Vector: Timer A CC0 */

#define TASSEL1                (0x0200)       /* Timer A clock source select 1 */
#define TASSEL0                (0x0100)       /* Timer A clock source select 0 */
#define ID1                    (0x0080)       /* Timer A clock input divider 1 */
#define ID0                    (0x0040)       /* Timer A clock input divider 0 */
#define MC1                    (0x0020)       /* Timer A mode control 1 */
#define MC0                    (0x0010)       /* Timer A mode control 0 */
#define TACLR                  (0x0004)       /* Timer A counter clear */
#define TAIE                   (0x0002)       /* Timer A counter interrupt enable */
#define TAIFG                  (0x0001)       /* Timer A counter interrupt flag */

#define MC_0                   (0*0x10u)      /* Timer A mode control: 0 - Stop */
#define MC_1                   (1*0x10u)      /* Timer A mode control: 1 - Up to CCR0 */
#define MC_2                   (2*0x10u)      /* Timer A mode control: 2 - Continous up */
#define MC_3                   (3*0x10u)      /* Timer A mode control: 3 - Up/Down */
#define ID_0                   (0*0x40u)      /* Timer A input divider: 0 - /1 */
#define ID_1                   (1*0x40u)      /* Timer A input divider: 1 - /2 */
#define ID_2                   (2*0x40u)      /* Timer A input divider: 2 - /4 */
#define ID_3                   (3*0x40u)      /* Timer A input divider: 3 - /8 */
#define TASSEL_0               (0*0x100u)     /* Timer A clock source select: 0 - TACLK */
#define TASSEL_1               (1*0x100u)     /* Timer A clock source select: 1 - ACLK  */
#define TASSEL_2               (2*0x100u)     /* Timer A clock source select: 2 - SMCLK */
#define TASSEL_3               (3*0x100u)     /* Timer A clock source select: 3 - INCLK */

#define CM1                    (0x8000)       /* Capture mode 1 */
#define CM0                    (0x4000)       /* Capture mode 0 */
#define CCIS1                  (0x2000)       /* Capture input select 1 */
#define CCIS0                  (0x1000)       /* Capture input select 0 */
#define SCS                    (0x0800)       /* Capture sychronize */
#define SCCI                   (0x0400)       /* Latched capture signal (read) */
#define CAP                    (0x0100)       /* Capture mode: 1 /Compare mode : 0 */
#define OUTMOD2                (0x0080)       /* Output mode 2 */
#define OUTMOD1                (0x0040)       /* Output mode 1 */
#define OUTMOD0                (0x0020)       /* Output mode 0 */
#define CCIE                   (0x0010)       /* Capture/compare interrupt enable */
#define CCI                    (0x0008)       /* Capture input signal (read) */
#define OUT                    (0x0004)       /* PWM Output signal if output mode 0 */
#define COV                    (0x0002)       /* Capture/compare overflow flag */
#define CCIFG                  (0x0001)       /* Capture/compare interrupt flag */

#define OUTMOD_0               (0*0x20u)      /* PWM output mode: 0 - output only */
#define OUTMOD_1               (1*0x20u)      /* PWM output mode: 1 - set */
#define OUTMOD_2               (2*0x20u)      /* PWM output mode: 2 - PWM toggle/reset */
#define OUTMOD_3               (3*0x20u)      /* PWM output mode: 3 - PWM set/reset */
#define OUTMOD_4               (4*0x20u)      /* PWM output mode: 4 - toggle */
#define OUTMOD_5               (5*0x20u)      /* PWM output mode: 5 - Reset */
#define OUTMOD_6               (6*0x20u)      /* PWM output mode: 6 - PWM toggle/set */
#define OUTMOD_7               (7*0x20u)      /* PWM output mode: 7 - PWM reset/set */
#define CCIS_0                 (0*0x1000u)    /* Capture input select: 0 - CCIxA */
#define CCIS_1                 (1*0x1000u)    /* Capture input select: 1 - CCIxB */
#define CCIS_2                 (2*0x1000u)    /* Capture input select: 2 - GND */
#define CCIS_3                 (3*0x1000u)    /* Capture input select: 3 - Vcc */
#define CM_0                   (0*0x4000u)    /* Capture mode: 0 - disabled */
#define CM_1                   (1*0x4000u)    /* Capture mode: 1 - pos. edge */
#define CM_2                   (2*0x4000u)    /* Capture mode: 1 - neg. edge */
#define CM_3                   (3*0x4000u)    /* Capture mode: 1 - both edges */

/* TA2IV Definitions */
#define TAIV_NONE              (0x0000)       /* No Interrupt pending */
#define TAIV_TACCR1            (0x0002)       /* TACCR1_CCIFG */
#define TAIV_2                 (0x0004)       /* Reserved */
#define TAIV_6                 (0x0006)       /* Reserved */
#define TAIV_8                 (0x0008)       /* Reserved */
#define TAIV_TAIFG             (0x000A)       /* TAIFG */

/* Alternate register names - 5xx style */
#define TA0IV_NONE             (0x0000)       /* No Interrupt pending */
#define TA0IV_TACCR1           (0x0002)       /* TA0CCR1_CCIFG */
#define TA0IV_2                (0x0004)       /* Reserved */
#define TA0IV_6                (0x0006)       /* Reserved */
#define TA0IV_8                (0x0008)       /* Reserved */
#define TA0IV_TAIFG            (0x000A)       /* TA0IFG */

/************************************************************
* USI
************************************************************/
#define __MSP430_HAS_USI__                    /* Definition to show that Module is available */

SFR_8BIT(USICTL0);                            /* USI  Control Register 0 */
SFR_8BIT(USICTL1);                            /* USI  Control Register 1 */
SFR_8BIT(USICKCTL);                           /* USI  Clock Control Register */
SFR_8BIT(USICNT);                             /* USI  Bit Counter Register */
SFR_8BIT(USISRL);                             /* USI  Low Byte Shift Register */
SFR_8BIT(USISRH);                             /* USI  High Byte Shift Register */
SFR_16BIT(USICTL);                            /* USI  Control Register */
SFR_16BIT(USICCTL);                           /* USI  Clock and Counter Control Register */
SFR_16BIT(USISR);                             /* USI  Shift Register */

#define USIPE7                 (0x80)         /* USI  Port Enable Px.7 */
#define USIPE6                 (0x40)         /* USI  Port Enable Px.6 */
#define USIPE5                 (0x20)         /* USI  Port Enable Px.5 */
#define USILSB                 (0x10)         /* USI  LSB first  1:LSB / 0:MSB */
#define USIMST                 (0x08)         /* USI  Master Select  0:Slave / 1:Master */
#define USIGE                  (0x04)         /* USI  General Output Enable Latch */
#define USIOE                  (0x02)         /* USI  Output Enable */
#define USISWRST               (0x01)         /* USI  Software Reset */

#define USICKPH                (0x80)         /* USI  Sync. Mode: Clock Phase */
#define USII2C                 (0x40)         /* USI  I2C Mode */
#define USISTTIE               (0x20)         /* USI  START Condition interrupt enable */
#define USIIE                  (0x10)         /* USI  Counter Interrupt enable */
#define USIAL                  (0x08)         /* USI  Arbitration Lost */
#define USISTP                 (0x04)         /* USI  STOP Condition received */
#define USISTTIFG              (0x02)         /* USI  START Condition interrupt Flag */
#define USIIFG                 (0x01)         /* USI  Counter Interrupt Flag */

#define USIDIV2                (0x80)         /* USI  Clock Divider 2 */
#define USIDIV1                (0x40)         /* USI  Clock Divider 1 */
#define USIDIV0                (0x20)         /* USI  Clock Divider 0 */
#define USISSEL2               (0x10)         /* USI  Clock Source Select 2 */
#define USISSEL1               (0x08)         /* USI  Clock Source Select 1 */
#define USISSEL0               (0x04)         /* USI  Clock Source Select 0 */
#define USICKPL                (0x02)         /* USI  Clock Polarity 0:Inactive=Low / 1:Inactive=High */
#define USISWCLK               (0x01)         /* USI  Software Clock */

#define USIDIV_0               (0x00)         /* USI  Clock Divider: 0 */
#define USIDIV_1               (0x20)         /* USI  Clock Divider: 1 */
#define USIDIV_2               (0x40)         /* USI  Clock Divider: 2 */
#define USIDIV_3               (0x60)         /* USI  Clock Divider: 3 */
#define USIDIV_4               (0x80)         /* USI  Clock Divider: 4 */
#define USIDIV_5               (0xA0)         /* USI  Clock Divider: 5 */
#define USIDIV_6               (0xC0)         /* USI  Clock Divider: 6 */
#define USIDIV_7               (0xE0)         /* USI  Clock Divider: 7 */

#define USISSEL_0              (0x00)         /* USI  Clock Source: 0 */
#define USISSEL_1              (0x04)         /* USI  Clock Source: 1 */
#define USISSEL_2              (0x08)         /* USI  Clock Source: 2 */
#define USISSEL_3              (0x0C)         /* USI  Clock Source: 3 */
#define USISSEL_4              (0x10)         /* USI  Clock Source: 4 */
#define USISSEL_5              (0x14)         /* USI  Clock Source: 5 */
#define USISSEL_6              (0x18)         /* USI  Clock Source: 6 */
#define USISSEL_7              (0x1C)         /* USI  Clock Source: 7 */

#define USISCLREL              (0x80)         /* USI  SCL Released */
#define USI16B                 (0x40)         /* USI  16 Bit Shift Register Enable */
#define USIIFGCC               (0x20)         /* USI  Interrupt Flag Clear Control */
#define USICNT4                (0x10)         /* USI  Bit Count 4 */
#define USICNT3                (0x08)         /* USI  Bit Count 3 */
#define USICNT2                (0x04)         /* USI  Bit Count 2 */
#define USICNT1                (0x02)         /* USI  Bit Count 1 */
#define USICNT0                (0x01)         /* USI  Bit Count 0 */
/************************************************************
* WATCHDOG TIMER
************************************************************/
#define __MSP430_HAS_WDT__                    /* Definition to show that Module is available */

SFR_16BIT(WDTCTL);                            /* Watchdog Timer Control */
/* The bit names have been prefixed with "WDT" */
#define WDTIS0                 (0x0001)
#define WDTIS1                 (0x0002)
#define WDTSSEL                (0x0004)
#define WDTCNTCL               (0x0008)
#define WDTTMSEL               (0x0010)
#define WDTNMI                 (0x0020)
#define WDTNMIES               (0x0040)
#define WDTHOLD                (0x0080)

#define WDTPW                  (0x5A00)

/* WDT-interval times [1ms] coded with Bits 0-2 */
/* WDT is clocked by fSMCLK (assumed 1MHz) */
#define WDT_MDLY_32         (WDTPW+WDTTMSEL+WDTCNTCL)                         /* 32ms interval (default) */
#define WDT_MDLY_8          (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS0)                  /* 8ms     " */
#define WDT_MDLY_0_5        (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS1)                  /* 0.5ms   " */
#define WDT_MDLY_0_064      (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS1+WDTIS0)           /* 0.064ms " */
/* WDT is clocked by fACLK (assumed 32KHz) */
#define WDT_ADLY_1000       (WDTPW+WDTTMSEL+WDTCNTCL+WDTSSEL)                 /* 1000ms  " */
#define WDT_ADLY_250        (WDTPW+WDTTMSEL+WDTCNTCL+WDTSSEL+WDTIS0)          /* 250ms   " */
#define WDT_ADLY_16         (WDTPW+WDTTMSEL+WDTCNTCL+WDTSSEL+WDTIS1)          /* 16ms    " */
#define WDT_ADLY_1_9        (WDTPW+WDTTMSEL+WDTCNTCL+WDTSSEL+WDTIS1+WDTIS0)   /* 1.9ms   " */
/* Watchdog mode -> reset after expired time */
/* WDT is clocked by fSMCLK (assumed 1MHz) */
#define WDT_MRST_32         (WDTPW+WDTCNTCL)                                  /* 32ms interval (default) */
#define WDT_MRST_8          (WDTPW+WDTCNTCL+WDTIS0)                           /* 8ms     " */
#define WDT_MRST_0_5        (WDTPW+WDTCNTCL+WDTIS1)                           /* 0.5ms   " */
#define WDT_MRST_0_064      (WDTPW+WDTCNTCL+WDTIS1+WDTIS0)                    /* 0.064ms " */
/* WDT is clocked by fACLK (assumed 32KHz) */
#define WDT_ARST_1000       (WDTPW+WDTCNTCL+WDTSSEL)                          /* 1000ms  " */
#define WDT_ARST_250        (WDTPW+WDTCNTCL+WDTSSEL+WDTIS0)                   /* 250ms   " */
#define WDT_ARST_16         (WDTPW+WDTCNTCL+WDTSSEL+WDTIS1)                   /* 16ms    " */
#define WDT_ARST_1_9        (WDTPW+WDTCNTCL+WDTSSEL+WDTIS1+WDTIS0)            /* 1.9ms   " */

/* INTERRUPT CONTROL */
/* These two bits are defined in the Special Function Registers */
/* #define WDTIE               0x01 */
/* #define WDTIFG              0x01 */

/************************************************************
* Calibration Data in Info Mem
************************************************************/

#ifndef __DisableCalData

SFR_8BIT(CALDCO_16MHZ);                       /* DCOCTL  Calibration Data for 16MHz */
SFR_8BIT(CALBC1_16MHZ);                       /* BCSCTL1 Calibration Data for 16MHz */
SFR_8BIT(CALDCO_12MHZ);                       /* DCOCTL  Calibration Data for 12MHz */
SFR_8BIT(CALBC1_12MHZ);                       /* BCSCTL1 Calibration Data for 12MHz */
SFR_8BIT(CALDCO_8MHZ);                        /* DCOCTL  Calibration Data for 8MHz */
SFR_8BIT(CALBC1_8MHZ);                        /* BCSCTL1 Calibration Data for 8MHz */
SFR_8BIT(CALDCO_1MHZ);                        /* DCOCTL  Calibration Data for 1MHz */
SFR_8BIT(CALBC1_1MHZ);                        /* BCSCTL1 Calibration Data for 1MHz */

#endif /* #ifndef __DisableCalData */

/************************************************************
* Interrupt Vectors (offset from 0xFFE0)
************************************************************/

#define VECTOR_NAME(name)       name##_ptr
#define EMIT_PRAGMA(x)          _Pragma(#x)
#define CREATE_VECTOR(name)     void (* const VECTOR_NAME(name))(void) = &name
#define PLACE_VECTOR(vector,section) EMIT_PRAGMA(DATA_SECTION(vector,section))
#define ISR_VECTOR(func,offset) CREATE_VECTOR(func); \
                                PLACE_VECTOR(VECTOR_NAME(func), offset)

#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define PORT1_VECTOR            ".int02"                     /* 0xFFE4 Port 1 */
#else
#define PORT1_VECTOR            (2 * 1u)                     /* 0xFFE4 Port 1 */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define PORT2_VECTOR            ".int03"                     /* 0xFFE6 Port 2 */
#else
#define PORT2_VECTOR            (3 * 1u)                     /* 0xFFE6 Port 2 */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define USI_VECTOR              ".int04"                     /* 0xFFE8 USI */
#else
#define USI_VECTOR              (4 * 1u)                     /* 0xFFE8 USI */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define SD16_VECTOR             ".int05"                     /* 0xFFEA Sigma Delta ADC */
#else
#define SD16_VECTOR             (5 * 1u)                     /* 0xFFEA Sigma Delta ADC */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define TIMERA1_VECTOR          ".int08"                     /* 0xFFF0 Timer A CC1, TA */
#else
#define TIMERA1_VECTOR          (8 * 1u)                     /* 0xFFF0 Timer A CC1, TA */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define TIMERA0_VECTOR          ".int09"                     /* 0xFFF2 Timer A CC0 */
#else
#define TIMERA0_VECTOR          (9 * 1u)                     /* 0xFFF2 Timer A CC0 */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define WDT_VECTOR              ".int10"                     /* 0xFFF4 Watchdog Timer */
#else
#define WDT_VECTOR              (10 * 1u)                    /* 0xFFF4 Watchdog Timer */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define NMI_VECTOR              ".int14"                     /* 0xFFFC Non-maskable */
#else
#define NMI_VECTOR              (14 * 1u)                    /* 0xFFFC Non-maskable */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define RESET_VECTOR            ".reset"                     /* 0xFFFE Reset [Highest Priority] */
#else
#define RESET_VECTOR            (15 * 1u)                    /* 0xFFFE Reset [Highest Priority] */
#endif

/************************************************************
* End of Modules
************************************************************/

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* #ifndef __msp430x20x3 */

