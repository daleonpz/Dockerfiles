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

/********************************************************************
*
* Standard register and bit definitions for the Texas Instruments
* MSP430 microcontroller.
*
* This file supports assembler and C development for
* MSP430AFE221 devices.
*
* Texas Instruments, Version 1.0
*
* Rev. 1.0, Setup
*
********************************************************************/

#ifndef __MSP430AFE221
#define __MSP430AFE221

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
#define U0IE                   IE1            /* UART0 Interrupt Enable Register */
#define WDTIE                  (0x01)         /* Watchdog Interrupt Enable */
#define OFIE                   (0x02)         /* Osc. Fault  Interrupt Enable */
#define NMIIE                  (0x10)         /* NMI Interrupt Enable */
#define ACCVIE                 (0x20)         /* Flash Access Violation Interrupt Enable */
#define URXIE0                 (0x40)
#define UTXIE0                 (0x80)

SFR_8BIT(IFG1);                               /* Interrupt Flag 1 */
#define U0IFG                  IFG1           /* UART0 Interrupt Flag Register */
#define WDTIFG                 (0x01)         /* Watchdog Interrupt Flag */
#define OFIFG                  (0x02)         /* Osc. Fault Interrupt Flag */
#define PORIFG                 (0x04)         /* Power On Interrupt Flag */
#define RSTIFG                 (0x08)         /* Reset Interrupt Flag */
#define NMIIFG                 (0x10)         /* NMI Interrupt Flag */
#define URXIFG0                (0x40)
#define UTXIFG0                (0x80)

SFR_8BIT(ME1);                                /* Module Enable 1 */
#define U0ME                   ME1            /* UART0 Module Enable Register */
#define URXE0                  (0x40)
#define UTXE0                  (0x80)
#define USPIE0                 (0x40)

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
* HARDWARE MULTIPLIER
************************************************************/
#define __MSP430_HAS_MPY__                    /* Definition to show that Module is available */

SFR_16BIT(MPY);                               /* Multiply Unsigned/Operand 1 */
SFR_16BIT(MPYS);                              /* Multiply Signed/Operand 1 */
SFR_16BIT(MAC);                               /* Multiply Unsigned and Accumulate/Operand 1 */
SFR_16BIT(MACS);                              /* Multiply Signed and Accumulate/Operand 1 */
SFR_16BIT(OP2);                               /* Operand 2 */
SFR_16BIT(RESLO);                             /* Result Low Word */
SFR_16BIT(RESHI);                             /* Result High Word */
SFR_16BIT(SUMEXT);                            /* Sum Extend */

/************************************************************
* DIGITAL I/O Port1/2 Pull up / Pull down Resistors
************************************************************/
#define __MSP430_HAS_PORT1_R__                /* Definition to show that Module is available */
#define __MSP430_HAS_PORT2_R__                /* Definition to show that Module is available */

#define __MSP430_HAS_P1SEL__                  /* Define for DriverLib */
#define __MSP430_HAS_P1SEL2__                 /* Define for DriverLib */
#define __MSP430_HAS_P2SEL__                  /* Define for DriverLib */
#define __MSP430_HAS_P2SEL2__                 /* Define for DriverLib */

SFR_8BIT(P1IN);                               /* Port 1 Input */
SFR_8BIT(P1OUT);                              /* Port 1 Output */
SFR_8BIT(P1DIR);                              /* Port 1 Direction */
SFR_8BIT(P1IFG);                              /* Port 1 Interrupt Flag */
SFR_8BIT(P1IES);                              /* Port 1 Interrupt Edge Select */
SFR_8BIT(P1IE);                               /* Port 1 Interrupt Enable */
SFR_8BIT(P1SEL);                              /* Port 1 Selection */
SFR_8BIT(P1SEL2);                             /* Port 1 Selection 2 */
SFR_8BIT(P1REN);                              /* Port 1 Resistor Enable */

SFR_8BIT(P2IN);                               /* Port 2 Input */
SFR_8BIT(P2OUT);                              /* Port 2 Output */
SFR_8BIT(P2DIR);                              /* Port 2 Direction */
SFR_8BIT(P2IFG);                              /* Port 2 Interrupt Flag */
SFR_8BIT(P2IES);                              /* Port 2 Interrupt Edge Select */
SFR_8BIT(P2IE);                               /* Port 2 Interrupt Enable */
SFR_8BIT(P2SEL);                              /* Port 2 Selection */
SFR_8BIT(P2SEL2);                             /* Port 2 Selection 2 */
SFR_8BIT(P2REN);                              /* Port 2 Resistor Enable */

/************************************************************
* SD24_A1 - Sigma Delta 24 Bit
************************************************************/
#define __MSP430_HAS_SD24_A1__                /* Definition to show that Module is available */

SFR_8BIT(SD24INCTL0);                         /* SD24 Input Control Register Channel 0 */
SFR_8BIT(SD24PRE0);                           /* SD24 Preload Register Channel 0 */
SFR_8BIT(SD24CONF1);                          /* SD24 Internal Configuration Register 1 */
                                      /* Please use only the recommended settings */

SFR_16BIT(SD24CTL);                           /* Sigma Delta ADC 24 Control Register */
SFR_16BIT(SD24CCTL0);                         /* SD24 Channel 0 Control Register */
SFR_16BIT(SD24MEM0);                          /* SD24 Channel 0 Conversion Memory */
SFR_16BIT(SD24IV);                            /* SD24 Interrupt Vector Register */

/* SD24INCTLx */
#define SD24INCH0              (0x0001)       /* SD24 Input Channel select 0 */
#define SD24INCH1              (0x0002)       /* SD24 Input Channel select 1 */
#define SD24INCH2              (0x0004)       /* SD24 Input Channel select 2 */
#define SD24GAIN0              (0x0008)       /* SD24 Input Pre-Amplifier Gain Select 0 */
#define SD24GAIN1              (0x0010)       /* SD24 Input Pre-Amplifier Gain Select 1 */
#define SD24GAIN2              (0x0020)       /* SD24 Input Pre-Amplifier Gain Select 2 */
#define SD24INTDLY0            (0x0040)       /* SD24 Interrupt Delay after 1.Conversion 0 */
#define SD24INTDLY1            (0x0080)       /* SD24 Interrupt Delay after 1.Conversion 1 */

#define SD24GAIN_1             (0x0000)       /* SD24 Input Pre-Amplifier Gain Select *1  */
#define SD24GAIN_2             (0x0008)       /* SD24 Input Pre-Amplifier Gain Select *2  */
#define SD24GAIN_4             (0x0010)       /* SD24 Input Pre-Amplifier Gain Select *4  */
#define SD24GAIN_8             (0x0018)       /* SD24 Input Pre-Amplifier Gain Select *8  */
#define SD24GAIN_16            (0x0020)       /* SD24 Input Pre-Amplifier Gain Select *16 */
#define SD24GAIN_32            (0x0028)       /* SD24 Input Pre-Amplifier Gain Select *32 */

#define SD24INCH_0             (0x0000)       /* SD24 Input Channel select input */
#define SD24INCH_1             (0x0001)       /* SD24 Input Channel select input */
#define SD24INCH_2             (0x0002)       /* SD24 Input Channel select input */
#define SD24INCH_3             (0x0003)       /* SD24 Input Channel select input */
#define SD24INCH_4             (0x0004)       /* SD24 Input Channel select input */
#define SD24INCH_5             (0x0005)       /* SD24 Input Channel select Vcc divider */
#define SD24INCH_6             (0x0006)       /* SD24 Input Channel select Temp */
#define SD24INCH_7             (0x0007)       /* SD24 Input Channel select Offset */

#define SD24INTDLY_0           (0x0000)       /* SD24 Interrupt Delay: Int. after 4.Conversion  */
#define SD24INTDLY_1           (0x0040)       /* SD24 Interrupt Delay: Int. after 3.Conversion  */
#define SD24INTDLY_2           (0x0080)       /* SD24 Interrupt Delay: Int. after 2.Conversion  */
#define SD24INTDLY_3           (0x00C0)       /* SD24 Interrupt Delay: Int. after 1.Conversion  */

/* SD24CTL */
#define SD24OVIE               (0x0002)       /* SD24 Overflow Interupt Enable */
#define SD24REFON              (0x0004)       /* SD24 Switch internal Reference on */
#define SD24VMIDON             (0x0008)       /* SD24 Switch Vmid Buffer on */
#define SD24SSEL0              (0x0010)       /* SD24 Clock Source Select 0 */
#define SD24SSEL1              (0x0020)       /* SD24 Clock Source Select 1 */
#define SD24DIV0               (0x0040)       /* SD24 Clock Divider Select 0 */
#define SD24DIV1               (0x0080)       /* SD24 Clock Divider Select 1 */
#define SD24LP                 (0x0100)       /* SD24 Low Power Mode Enable */
#define SD24XDIV0              (0x0200)       /* SD24 2.Clock Divider Select 0 */
#define SD24XDIV1              (0x0400)       /* SD24 2.Clock Divider Select 1 */
//#define SD24XDIV2           (0x0800)  /* SD24 2.Clock Divider Select 2 */

#define SD24DIV_0              (0x0000)       /* SD24 Clock Divider Select /1 */
#define SD24DIV_1              (SD24DIV0)     /* SD24 Clock Divider Select /2 */
#define SD24DIV_2              (SD24DIV1)     /* SD24 Clock Divider Select /4 */
#define SD24DIV_3            (SD24DIV0+SD24DIV1)    /* SD24 Clock Divider Select /8 */

#define SD24XDIV_0             (0x0000)       /* SD24 2.Clock Divider Select /1 */
#define SD24XDIV_1             (SD24XDIV0)    /* SD24 2.Clock Divider Select /3 */
#define SD24XDIV_2             (SD24XDIV1)    /* SD24 2.Clock Divider Select /16 */
#define SD24XDIV_3          (SD24XDIV0+SD24XDIV1)  /* SD24 2.Clock Divider Select /48 */

#define SD24SSEL_0             (0x0000)       /* SD24 Clock Source Select MCLK  */
#define SD24SSEL_1             (SD24SSEL0)    /* SD24 Clock Source Select SMCLK */
#define SD24SSEL_2             (SD24SSEL1)    /* SD24 Clock Source Select ACLK  */
#define SD24SSEL_3           (SD24SSEL0+SD24SSEL1)  /* SD24 Clock Source Select TACLK */

/* SD24CCTLx */
#define SD24GRP                (0x0001)       /* SD24 Grouping of Channels: 0:Off/1:On */
#define SD24SC                 (0x0002)       /* SD24 Start Conversion */
#define SD24IFG                (0x0004)       /* SD24 Channel x Interrupt Flag */
#define SD24IE                 (0x0008)       /* SD24 Channel x Interrupt Enable */
#define SD24DF                 (0x0010)       /* SD24 Channel x Data Format: 0:Unipolar/1:Bipolar */
#define SD24OVIFG              (0x0020)       /* SD24 Channel x Overflow Interrupt Flag */
#define SD24LSBACC             (0x0040)       /* SD24 Channel x Access LSB of ADC */
#define SD24LSBTOG             (0x0080)       /* SD24 Channel x Toggle LSB Output of ADC */
#define SD24OSR0               (0x0100)       /* SD24 Channel x OverSampling Ratio 0 */
#define SD24OSR1               (0x0200)       /* SD24 Channel x OverSampling Ratio 1 */
#define SD24SNGL               (0x0400)       /* SD24 Channel x Single Conversion On/Off */
#define SD24XOSR               (0x0800)       /* SD24 Channel x Extended OverSampling Ratio */
#define SD24UNI                (0x1000)       /* SD24 Channel x Bipolar(0) / Unipolar(1) Mode */

#define SD24OSR_1024        (SD24OSR0+SD24XOSR)     /* SD24 Channel x OverSampling Ratio 1024 */
#define SD24OSR_512            (SD24XOSR)     /* SD24 Channel x OverSampling Ratio 512 */
#define SD24OSR_256            (0x0000)       /* SD24 Channel x OverSampling Ratio 256 */
#define SD24OSR_128            (0x0100)       /* SD24 Channel x OverSampling Ratio 128 */
#define SD24OSR_64             (0x0200)       /* SD24 Channel x OverSampling Ratio  64 */
#define SD24OSR_32             (0x0300)       /* SD24 Channel x OverSampling Ratio  32 */

/* SD24IV Definitions */
#define SD24IV_NONE            (0x0000)       /* No Interrupt pending */
#define SD24IV_SD24OVIFG       (0x0002)       /* SD24OVIFG */
#define SD24IV_SD24MEM0        (0x0004)       /* SD24MEM0 SD24IFG */

/************************************************************
* Brown-Out, Supply Voltage Supervision (SVS)
************************************************************/
#define __MSP430_HAS_SVS__                    /* Definition to show that Module is available */

SFR_8BIT(SVSCTL);                             /* SVS Control */
#define SVSFG                  (0x01)         /* SVS Flag */
#define SVSOP                  (0x02)         /* SVS output (read only) */
#define SVSON                  (0x04)         /* Switches the SVS on/off */
#define PORON                  (0x08)         /* Enable POR Generation if Low Voltage */
#define VLD0                   (0x10)
#define VLD1                   (0x20)
#define VLD2                   (0x40)
#define VLD3                   (0x80)

#define VLDON                  (0x10)
#define VLDOFF                 (0x00)
#define VLD_1_8V               (0x10)

/************************************************************
* Timer A3
************************************************************/
#define __MSP430_HAS_TA3__                    /* Definition to show that Module is available */

SFR_16BIT(TAIV);                              /* Timer A Interrupt Vector Word */
SFR_16BIT(TACTL);                             /* Timer A Control */
SFR_16BIT(TACCTL0);                           /* Timer A Capture/Compare Control 0 */
SFR_16BIT(TACCTL1);                           /* Timer A Capture/Compare Control 1 */
SFR_16BIT(TACCTL2);                           /* Timer A Capture/Compare Control 2 */
SFR_16BIT(TAR);                               /* Timer A Counter Register */
SFR_16BIT(TACCR0);                            /* Timer A Capture/Compare 0 */
SFR_16BIT(TACCR1);                            /* Timer A Capture/Compare 1 */
SFR_16BIT(TACCR2);                            /* Timer A Capture/Compare 2 */

/* Alternate register names */
#define CCTL0                  TACCTL0        /* Timer A Capture/Compare Control 0 */
#define CCTL1                  TACCTL1        /* Timer A Capture/Compare Control 1 */
#define CCTL2                  TACCTL2        /* Timer A Capture/Compare Control 2 */
#define CCR0                   TACCR0         /* Timer A Capture/Compare 0 */
#define CCR1                   TACCR1         /* Timer A Capture/Compare 1 */
#define CCR2                   TACCR2         /* Timer A Capture/Compare 2 */
#define CCTL0_                 TACCTL0_       /* Timer A Capture/Compare Control 0 */
#define CCTL1_                 TACCTL1_       /* Timer A Capture/Compare Control 1 */
#define CCTL2_                 TACCTL2_       /* Timer A Capture/Compare Control 2 */
#define CCR0_                  TACCR0_        /* Timer A Capture/Compare 0 */
#define CCR1_                  TACCR1_        /* Timer A Capture/Compare 1 */
#define CCR2_                  TACCR2_        /* Timer A Capture/Compare 2 */
/* Alternate register names - 5xx style */
#define TA0IV                  TAIV           /* Timer A Interrupt Vector Word */
#define TA0CTL                 TACTL          /* Timer A Control */
#define TA0CCTL0               TACCTL0        /* Timer A Capture/Compare Control 0 */
#define TA0CCTL1               TACCTL1        /* Timer A Capture/Compare Control 1 */
#define TA0CCTL2               TACCTL2        /* Timer A Capture/Compare Control 2 */
#define TA0R                   TAR            /* Timer A Counter Register */
#define TA0CCR0                TACCR0         /* Timer A Capture/Compare 0 */
#define TA0CCR1                TACCR1         /* Timer A Capture/Compare 1 */
#define TA0CCR2                TACCR2         /* Timer A Capture/Compare 2 */
#define TA0IV_                 TAIV_          /* Timer A Interrupt Vector Word */
#define TA0CTL_                TACTL_         /* Timer A Control */
#define TA0CCTL0_              TACCTL0_       /* Timer A Capture/Compare Control 0 */
#define TA0CCTL1_              TACCTL1_       /* Timer A Capture/Compare Control 1 */
#define TA0CCTL2_              TACCTL2_       /* Timer A Capture/Compare Control 2 */
#define TA0R_                  TAR_           /* Timer A Counter Register */
#define TA0CCR0_               TACCR0_        /* Timer A Capture/Compare 0 */
#define TA0CCR1_               TACCR1_        /* Timer A Capture/Compare 1 */
#define TA0CCR2_               TACCR2_        /* Timer A Capture/Compare 2 */
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

/* TA3IV Definitions */
#define TAIV_NONE              (0x0000)       /* No Interrupt pending */
#define TAIV_TACCR1            (0x0002)       /* TACCR1_CCIFG */
#define TAIV_TACCR2            (0x0004)       /* TACCR2_CCIFG */
#define TAIV_6                 (0x0006)       /* Reserved */
#define TAIV_8                 (0x0008)       /* Reserved */
#define TAIV_TAIFG             (0x000A)       /* TAIFG */

/* Alternate register names - 5xx style */
#define TA0IV_NONE             (0x0000)       /* No Interrupt pending */
#define TA0IV_TACCR1           (0x0002)       /* TA0CCR1_CCIFG */
#define TA0IV_TACCR2           (0x0004)       /* TA0CCR2_CCIFG */
#define TA0IV_6                (0x0006)       /* Reserved */
#define TA0IV_8                (0x0008)       /* Reserved */
#define TA0IV_TAIFG            (0x000A)       /* TA0IFG */

/************************************************************
* USART
************************************************************/

/* UxCTL */
#define PENA                   (0x80)         /* Parity enable */
#define PEV                    (0x40)         /* Parity 0:odd / 1:even */
#define SPB                    (0x20)         /* Stop Bits 0:one / 1: two */
#define CHAR                   (0x10)         /* Data 0:7-bits / 1:8-bits */
#define LISTEN                 (0x08)         /* Listen mode */
#define SYNC                   (0x04)         /* UART / SPI mode */
#define MM                     (0x02)         /* Master Mode off/on */
#define SWRST                  (0x01)         /* USART Software Reset */

/* UxTCTL */
#define CKPH                   (0x80)         /* SPI: Clock Phase */
#define CKPL                   (0x40)         /* Clock Polarity */
#define SSEL1                  (0x20)         /* Clock Source Select 1 */
#define SSEL0                  (0x10)         /* Clock Source Select 0 */
#define URXSE                  (0x08)         /* Receive Start edge select */
#define TXWAKE                 (0x04)         /* TX Wake up mode */
#define STC                    (0x02)         /* SPI: STC enable 0:on / 1:off */
#define TXEPT                  (0x01)         /* TX Buffer empty */

/* UxRCTL */
#define FE                     (0x80)         /* Frame Error */
#define PE                     (0x40)         /* Parity Error */
#define OE                     (0x20)         /* Overrun Error */
#define BRK                    (0x10)         /* Break detected */
#define URXEIE                 (0x08)         /* RX Error interrupt enable */
#define URXWIE                 (0x04)         /* RX Wake up interrupt enable */
#define RXWAKE                 (0x02)         /* RX Wake up detect */
#define RXERR                  (0x01)         /* RX Error Error */

/************************************************************
* USART 0
************************************************************/
#define __MSP430_HAS_UART0__                  /* Definition to show that Module is available */

SFR_8BIT(U0CTL);                              /* USART 0 Control */
SFR_8BIT(U0TCTL);                             /* USART 0 Transmit Control */
SFR_8BIT(U0RCTL);                             /* USART 0 Receive Control */
SFR_8BIT(U0MCTL);                             /* USART 0 Modulation Control */
SFR_8BIT(U0BR0);                              /* USART 0 Baud Rate 0 */
SFR_8BIT(U0BR1);                              /* USART 0 Baud Rate 1 */
SFR_8BIT(U0RXBUF);                            /* USART 0 Receive Buffer */
SFR_8BIT(U0TXBUF);                            /* USART 0 Transmit Buffer */

/* Alternate register names */

#define UCTL0                  U0CTL          /* USART 0 Control */
#define UTCTL0                 U0TCTL         /* USART 0 Transmit Control */
#define URCTL0                 U0RCTL         /* USART 0 Receive Control */
#define UMCTL0                 U0MCTL         /* USART 0 Modulation Control */
#define UBR00                  U0BR0          /* USART 0 Baud Rate 0 */
#define UBR10                  U0BR1          /* USART 0 Baud Rate 1 */
#define RXBUF0                 U0RXBUF        /* USART 0 Receive Buffer */
#define TXBUF0                 U0TXBUF        /* USART 0 Transmit Buffer */
#define UCTL0_                 U0CTL_         /* USART 0 Control */
#define UTCTL0_                U0TCTL_        /* USART 0 Transmit Control */
#define URCTL0_                U0RCTL_        /* USART 0 Receive Control */
#define UMCTL0_                U0MCTL_        /* USART 0 Modulation Control */
#define UBR00_                 U0BR0_         /* USART 0 Baud Rate 0 */
#define UBR10_                 U0BR1_         /* USART 0 Baud Rate 1 */
#define RXBUF0_                U0RXBUF_       /* USART 0 Receive Buffer */
#define TXBUF0_                U0TXBUF_       /* USART 0 Transmit Buffer */
#define UCTL_0                 U0CTL          /* USART 0 Control */
#define UTCTL_0                U0TCTL         /* USART 0 Transmit Control */
#define URCTL_0                U0RCTL         /* USART 0 Receive Control */
#define UMCTL_0                U0MCTL         /* USART 0 Modulation Control */
#define UBR0_0                 U0BR0          /* USART 0 Baud Rate 0 */
#define UBR1_0                 U0BR1          /* USART 0 Baud Rate 1 */
#define RXBUF_0                U0RXBUF        /* USART 0 Receive Buffer */
#define TXBUF_0                U0TXBUF        /* USART 0 Transmit Buffer */
#define UCTL_0_                U0CTL_         /* USART 0 Control */
#define UTCTL_0_               U0TCTL_        /* USART 0 Transmit Control */
#define URCTL_0_               U0RCTL_        /* USART 0 Receive Control */
#define UMCTL_0_               U0MCTL_        /* USART 0 Modulation Control */
#define UBR0_0_                U0BR0_         /* USART 0 Baud Rate 0 */
#define UBR1_0_                U0BR1_         /* USART 0 Baud Rate 1 */
#define RXBUF_0_               U0RXBUF_       /* USART 0 Receive Buffer */
#define TXBUF_0_               U0TXBUF_       /* USART 0 Transmit Buffer */

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

SFR_8BIT(CALDCO_12MHZ);                       /* DCOCTL  Calibration Data for 12MHz */
SFR_8BIT(CALBC1_12MHZ);                       /* BCSCTL1 Calibration Data for 12MHz */
SFR_8BIT(CALDCO_8MHZ);                        /* DCOCTL  Calibration Data for 8MHz */
SFR_8BIT(CALBC1_8MHZ);                        /* BCSCTL1 Calibration Data for 8MHz */

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
#define PORT2_VECTOR            ".int01"                     /* 0xFFE2 Port 2 */
#else
#define PORT2_VECTOR            (1 * 1u)                     /* 0xFFE2 Port 2 */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define PORT1_VECTOR            ".int04"                     /* 0xFFE8 Port 1 */
#else
#define PORT1_VECTOR            (4 * 1u)                     /* 0xFFE8 Port 1 */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define TIMERA1_VECTOR          ".int05"                     /* 0xFFEA Timer A CC1, TA */
#else
#define TIMERA1_VECTOR          (5 * 1u)                     /* 0xFFEA Timer A CC1, TA */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define TIMERA0_VECTOR          ".int06"                     /* 0xFFEC Timer A CC0 */
#else
#define TIMERA0_VECTOR          (6 * 1u)                     /* 0xFFEC Timer A CC0 */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define USART0TX_VECTOR         ".int08"                     /* 0xFFF0 USART 0 Transmit */
#else
#define USART0TX_VECTOR         (8 * 1u)                     /* 0xFFF0 USART 0 Transmit */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define USART0RX_VECTOR         ".int09"                     /* 0xFFF2 USART 0 Receive */
#else
#define USART0RX_VECTOR         (9 * 1u)                     /* 0xFFF2 USART 0 Receive */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define WDT_VECTOR              ".int10"                     /* 0xFFF4 Watchdog Timer */
#else
#define WDT_VECTOR              (10 * 1u)                    /* 0xFFF4 Watchdog Timer */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define SD24_VECTOR             ".int12"                     /* 0xFFF8 Sigma Delta ADC */
#else
#define SD24_VECTOR             (12 * 1u)                    /* 0xFFF8 Sigma Delta ADC */
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

#endif /* #ifndef __MSP430AFE221 */
