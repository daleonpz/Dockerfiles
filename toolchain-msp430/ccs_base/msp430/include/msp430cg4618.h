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
* MSP430xG46x devices.
*
* Texas Instruments, Version 1.7
*
* Rev. 1.0, Setup
* Rev. 1.1, Fixed Names for USCI an settings for DMA
* Rev. 1.2, Added VLD bits in SVS module
* Rev. 1.3, Removed definitions for BTRESET
*           Fixed swapped definition of RTCxxx
* Rev. 1.4, Removed unused ME1 definition
* Rev. 1.5, added definitions for Interrupt Vectors xxIV
* Rev. 1.6, changed 'void __data20 * volatile' definition
* Rev. 1.6, added LFXT1DIG
*
*
********************************************************************/

#ifndef __msp430xG46x
#define __msp430xG46x

#define __MSP430_HAS_MSP430X_CPU__                /* Definition to show that it has MSP430X CPU */

#define __MSP430_HEADER_VERSION__ 1209

#ifdef __cplusplus
extern "C" {
#endif


/*----------------------------------------------------------------------------*/
/* PERIPHERAL FILE MAP                                                        */
/*----------------------------------------------------------------------------*/

#ifndef SFR_8BIT
/* External references resolved by a device-specific linker command file */
#define SFR_8BIT(address)   extern volatile unsigned char address
#define SFR_16BIT(address)  extern volatile unsigned int address
//#define SFR_20BIT(address)  extern volatile unsigned int address
typedef void (* __SFR_FARPTR)();
#define SFR_20BIT(address) extern __SFR_FARPTR address
#define SFR_32BIT(address)  extern volatile unsigned long address

#endif


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
#define WDTIE                  (0x01)
#define OFIE                   (0x02)
#define NMIIE                  (0x10)
#define ACCVIE                 (0x20)

SFR_8BIT(IFG1);                               /* Interrupt Flag 1 */
#define WDTIFG                 (0x01)
#define OFIFG                  (0x02)
#define NMIIFG                 (0x10)

SFR_8BIT(IE2);                                /* Interrupt Enable 2 */
#define U1IE                   IE2            /* UART1 Interrupt Enable Register */
#define UC0IE                  IE2
#define UCA0RXIE               (0x01)
#define UCA0TXIE               (0x02)
#define UCB0RXIE               (0x04)
#define UCB0TXIE               (0x08)
#define URXIE1                 (0x10)
#define UTXIE1                 (0x20)
#define BTIE                   (0x80)

SFR_8BIT(IFG2);                               /* Interrupt Flag 2 */
#define U1IFG                  IFG2           /* UART1 Interrupt Flag Register */
#define UC0IFG                 IFG2
#define UCA0RXIFG              (0x01)
#define UCA0TXIFG              (0x02)
#define UCB0RXIFG              (0x04)
#define UCB0TXIFG              (0x08)
#define URXIFG1                (0x10)
#define UTXIFG1                (0x20)
#define BTIFG                  (0x80)

SFR_8BIT(ME2);                                /* Module Enable 2 */
#define U1ME                   ME2            /* UART1 Module Enable Register */
#define URXE1                  (0x10)
#define UTXE1                  (0x20)
#define USPIE1                 (0x10)

/************************************************************
* ADC12
************************************************************/
#define __MSP430_HAS_ADC12__                  /* Definition to show that Module is available */

SFR_16BIT(ADC12CTL0);                         /* ADC12 Control 0 */
SFR_16BIT(ADC12CTL1);                         /* ADC12 Control 1 */
SFR_16BIT(ADC12IFG);                          /* ADC12 Interrupt Flag */
SFR_16BIT(ADC12IE);                           /* ADC12 Interrupt Enable */
SFR_16BIT(ADC12IV);                           /* ADC12 Interrupt Vector Word */

#define ADC12MEM_              (0x0140)       /* ADC12 Conversion Memory */
#ifdef __ASM_HEADER__
#define ADC12MEM               (ADC12MEM_)    /* ADC12 Conversion Memory (for assembler) */
#else
#define ADC12MEM               ((int*)        ADC12MEM_) /* ADC12 Conversion Memory (for C) */
#endif
SFR_16BIT(ADC12MEM0);                         /* ADC12 Conversion Memory 0 */
SFR_16BIT(ADC12MEM1);                         /* ADC12 Conversion Memory 1 */
SFR_16BIT(ADC12MEM2);                         /* ADC12 Conversion Memory 2 */
SFR_16BIT(ADC12MEM3);                         /* ADC12 Conversion Memory 3 */
SFR_16BIT(ADC12MEM4);                         /* ADC12 Conversion Memory 4 */
SFR_16BIT(ADC12MEM5);                         /* ADC12 Conversion Memory 5 */
SFR_16BIT(ADC12MEM6);                         /* ADC12 Conversion Memory 6 */
SFR_16BIT(ADC12MEM7);                         /* ADC12 Conversion Memory 7 */
SFR_16BIT(ADC12MEM8);                         /* ADC12 Conversion Memory 8 */
SFR_16BIT(ADC12MEM9);                         /* ADC12 Conversion Memory 9 */
SFR_16BIT(ADC12MEM10);                        /* ADC12 Conversion Memory 10 */
SFR_16BIT(ADC12MEM11);                        /* ADC12 Conversion Memory 11 */
SFR_16BIT(ADC12MEM12);                        /* ADC12 Conversion Memory 12 */
SFR_16BIT(ADC12MEM13);                        /* ADC12 Conversion Memory 13 */
SFR_16BIT(ADC12MEM14);                        /* ADC12 Conversion Memory 14 */
SFR_16BIT(ADC12MEM15);                        /* ADC12 Conversion Memory 15 */

#define ADC12MCTL_             (0x0080)       /* ADC12 Memory Control */
#ifdef __ASM_HEADER__
#define ADC12MCTL              (ADC12MCTL_)   /* ADC12 Memory Control (for assembler) */
#else
#define ADC12MCTL              ((char*)       ADC12MCTL_) /* ADC12 Memory Control (for C) */
#endif
SFR_8BIT(ADC12MCTL0);                         /* ADC12 Memory Control 0 */
SFR_8BIT(ADC12MCTL1);                         /* ADC12 Memory Control 1 */
SFR_8BIT(ADC12MCTL2);                         /* ADC12 Memory Control 2 */
SFR_8BIT(ADC12MCTL3);                         /* ADC12 Memory Control 3 */
SFR_8BIT(ADC12MCTL4);                         /* ADC12 Memory Control 4 */
SFR_8BIT(ADC12MCTL5);                         /* ADC12 Memory Control 5 */
SFR_8BIT(ADC12MCTL6);                         /* ADC12 Memory Control 6 */
SFR_8BIT(ADC12MCTL7);                         /* ADC12 Memory Control 7 */
SFR_8BIT(ADC12MCTL8);                         /* ADC12 Memory Control 8 */
SFR_8BIT(ADC12MCTL9);                         /* ADC12 Memory Control 9 */
SFR_8BIT(ADC12MCTL10);                        /* ADC12 Memory Control 10 */
SFR_8BIT(ADC12MCTL11);                        /* ADC12 Memory Control 11 */
SFR_8BIT(ADC12MCTL12);                        /* ADC12 Memory Control 12 */
SFR_8BIT(ADC12MCTL13);                        /* ADC12 Memory Control 13 */
SFR_8BIT(ADC12MCTL14);                        /* ADC12 Memory Control 14 */
SFR_8BIT(ADC12MCTL15);                        /* ADC12 Memory Control 15 */

/* ADC12CTL0 */
#define ADC12SC                (0x001)        /* ADC12 Start Conversion */
#define ENC                    (0x002)        /* ADC12 Enable Conversion */
#define ADC12TOVIE             (0x004)        /* ADC12 Timer Overflow interrupt enable */
#define ADC12OVIE              (0x008)        /* ADC12 Overflow interrupt enable */
#define ADC12ON                (0x010)        /* ADC12 On/enable */
#define REFON                  (0x020)        /* ADC12 Reference on */
#define REF2_5V                (0x040)        /* ADC12 Ref 0:1.5V / 1:2.5V */
#define MSC                    (0x080)        /* ADC12 Multiple SampleConversion */
#define SHT00                  (0x0100)       /* ADC12 Sample Hold 0 Select 0 */
#define SHT01                  (0x0200)       /* ADC12 Sample Hold 0 Select 1 */
#define SHT02                  (0x0400)       /* ADC12 Sample Hold 0 Select 2 */
#define SHT03                  (0x0800)       /* ADC12 Sample Hold 0 Select 3 */
#define SHT10                  (0x1000)       /* ADC12 Sample Hold 0 Select 0 */
#define SHT11                  (0x2000)       /* ADC12 Sample Hold 1 Select 1 */
#define SHT12                  (0x4000)       /* ADC12 Sample Hold 2 Select 2 */
#define SHT13                  (0x8000)       /* ADC12 Sample Hold 3 Select 3 */
#define MSH                    (0x080)

#define SHT0_0                 (0*0x100u)     /* ADC12 Sample Hold 0 Select Bit: 0 */
#define SHT0_1                 (1*0x100u)     /* ADC12 Sample Hold 0 Select Bit: 1 */
#define SHT0_2                 (2*0x100u)     /* ADC12 Sample Hold 0 Select Bit: 2 */
#define SHT0_3                 (3*0x100u)     /* ADC12 Sample Hold 0 Select Bit: 3 */
#define SHT0_4                 (4*0x100u)     /* ADC12 Sample Hold 0 Select Bit: 4 */
#define SHT0_5                 (5*0x100u)     /* ADC12 Sample Hold 0 Select Bit: 5 */
#define SHT0_6                 (6*0x100u)     /* ADC12 Sample Hold 0 Select Bit: 6 */
#define SHT0_7                 (7*0x100u)     /* ADC12 Sample Hold 0 Select Bit: 7 */
#define SHT0_8                 (8*0x100u)     /* ADC12 Sample Hold 0 Select Bit: 8 */
#define SHT0_9                 (9*0x100u)     /* ADC12 Sample Hold 0 Select Bit: 9 */
#define SHT0_10                (10*0x100u)    /* ADC12 Sample Hold 0 Select Bit: 10 */
#define SHT0_11                (11*0x100u)    /* ADC12 Sample Hold 0 Select Bit: 11 */
#define SHT0_12                (12*0x100u)    /* ADC12 Sample Hold 0 Select Bit: 12 */
#define SHT0_13                (13*0x100u)    /* ADC12 Sample Hold 0 Select Bit: 13 */
#define SHT0_14                (14*0x100u)    /* ADC12 Sample Hold 0 Select Bit: 14 */
#define SHT0_15                (15*0x100u)    /* ADC12 Sample Hold 0 Select Bit: 15 */

#define SHT1_0                 (0*0x1000u)    /* ADC12 Sample Hold 1 Select Bit: 0 */
#define SHT1_1                 (1*0x1000u)    /* ADC12 Sample Hold 1 Select Bit: 1 */
#define SHT1_2                 (2*0x1000u)    /* ADC12 Sample Hold 1 Select Bit: 2 */
#define SHT1_3                 (3*0x1000u)    /* ADC12 Sample Hold 1 Select Bit: 3 */
#define SHT1_4                 (4*0x1000u)    /* ADC12 Sample Hold 1 Select Bit: 4 */
#define SHT1_5                 (5*0x1000u)    /* ADC12 Sample Hold 1 Select Bit: 5 */
#define SHT1_6                 (6*0x1000u)    /* ADC12 Sample Hold 1 Select Bit: 6 */
#define SHT1_7                 (7*0x1000u)    /* ADC12 Sample Hold 1 Select Bit: 7 */
#define SHT1_8                 (8*0x1000u)    /* ADC12 Sample Hold 1 Select Bit: 8 */
#define SHT1_9                 (9*0x1000u)    /* ADC12 Sample Hold 1 Select Bit: 9 */
#define SHT1_10                (10*0x1000u)   /* ADC12 Sample Hold 1 Select Bit: 10 */
#define SHT1_11                (11*0x1000u)   /* ADC12 Sample Hold 1 Select Bit: 11 */
#define SHT1_12                (12*0x1000u)   /* ADC12 Sample Hold 1 Select Bit: 12 */
#define SHT1_13                (13*0x1000u)   /* ADC12 Sample Hold 1 Select Bit: 13 */
#define SHT1_14                (14*0x1000u)   /* ADC12 Sample Hold 1 Select Bit: 14 */
#define SHT1_15                (15*0x1000u)   /* ADC12 Sample Hold 1 Select Bit: 15 */

/* ADC12CTL1 */
#define ADC12BUSY              (0x0001)       /* ADC12 Busy */
#define CONSEQ0                (0x0002)       /* ADC12 Conversion Sequence Select 0 */
#define CONSEQ1                (0x0004)       /* ADC12 Conversion Sequence Select 1 */
#define ADC12SSEL0             (0x0008)       /* ADC12 Clock Source Select 0 */
#define ADC12SSEL1             (0x0010)       /* ADC12 Clock Source Select 1 */
#define ADC12DIV0              (0x0020)       /* ADC12 Clock Divider Select 0 */
#define ADC12DIV1              (0x0040)       /* ADC12 Clock Divider Select 1 */
#define ADC12DIV2              (0x0080)       /* ADC12 Clock Divider Select 2 */
#define ISSH                   (0x0100)       /* ADC12 Invert Sample Hold Signal */
#define SHP                    (0x0200)       /* ADC12 Sample/Hold Pulse Mode */
#define SHS0                   (0x0400)       /* ADC12 Sample/Hold Source 0 */
#define SHS1                   (0x0800)       /* ADC12 Sample/Hold Source 1 */
#define CSTARTADD0             (0x1000)       /* ADC12 Conversion Start Address 0 */
#define CSTARTADD1             (0x2000)       /* ADC12 Conversion Start Address 1 */
#define CSTARTADD2             (0x4000)       /* ADC12 Conversion Start Address 2 */
#define CSTARTADD3             (0x8000)       /* ADC12 Conversion Start Address 3 */

#define CONSEQ_0               (0*2u)         /* ADC12 Conversion Sequence Select: 0 */
#define CONSEQ_1               (1*2u)         /* ADC12 Conversion Sequence Select: 1 */
#define CONSEQ_2               (2*2u)         /* ADC12 Conversion Sequence Select: 2 */
#define CONSEQ_3               (3*2u)         /* ADC12 Conversion Sequence Select: 3 */
#define ADC12SSEL_0            (0*8u)         /* ADC12 Clock Source Select: 0 */
#define ADC12SSEL_1            (1*8u)         /* ADC12 Clock Source Select: 1 */
#define ADC12SSEL_2            (2*8u)         /* ADC12 Clock Source Select: 2 */
#define ADC12SSEL_3            (3*8u)         /* ADC12 Clock Source Select: 3 */
#define ADC12DIV_0             (0*0x20u)      /* ADC12 Clock Divider Select: 0 */
#define ADC12DIV_1             (1*0x20u)      /* ADC12 Clock Divider Select: 1 */
#define ADC12DIV_2             (2*0x20u)      /* ADC12 Clock Divider Select: 2 */
#define ADC12DIV_3             (3*0x20u)      /* ADC12 Clock Divider Select: 3 */
#define ADC12DIV_4             (4*0x20u)      /* ADC12 Clock Divider Select: 4 */
#define ADC12DIV_5             (5*0x20u)      /* ADC12 Clock Divider Select: 5 */
#define ADC12DIV_6             (6*0x20u)      /* ADC12 Clock Divider Select: 6 */
#define ADC12DIV_7             (7*0x20u)      /* ADC12 Clock Divider Select: 7 */
#define SHS_0                  (0*0x400u)     /* ADC12 Sample/Hold Source: 0 */
#define SHS_1                  (1*0x400u)     /* ADC12 Sample/Hold Source: 1 */
#define SHS_2                  (2*0x400u)     /* ADC12 Sample/Hold Source: 2 */
#define SHS_3                  (3*0x400u)     /* ADC12 Sample/Hold Source: 3 */
#define CSTARTADD_0            (0*0x1000u)    /* ADC12 Conversion Start Address: 0 */
#define CSTARTADD_1            (1*0x1000u)    /* ADC12 Conversion Start Address: 1 */
#define CSTARTADD_2            (2*0x1000u)    /* ADC12 Conversion Start Address: 2 */
#define CSTARTADD_3            (3*0x1000u)    /* ADC12 Conversion Start Address: 3 */
#define CSTARTADD_4            (4*0x1000u)    /* ADC12 Conversion Start Address: 4 */
#define CSTARTADD_5            (5*0x1000u)    /* ADC12 Conversion Start Address: 5 */
#define CSTARTADD_6            (6*0x1000u)    /* ADC12 Conversion Start Address: 6 */
#define CSTARTADD_7            (7*0x1000u)    /* ADC12 Conversion Start Address: 7 */
#define CSTARTADD_8            (8*0x1000u)    /* ADC12 Conversion Start Address: 8 */
#define CSTARTADD_9            (9*0x1000u)    /* ADC12 Conversion Start Address: 9 */
#define CSTARTADD_10           (10*0x1000u)   /* ADC12 Conversion Start Address: 10 */
#define CSTARTADD_11           (11*0x1000u)   /* ADC12 Conversion Start Address: 11 */
#define CSTARTADD_12           (12*0x1000u)   /* ADC12 Conversion Start Address: 12 */
#define CSTARTADD_13           (13*0x1000u)   /* ADC12 Conversion Start Address: 13 */
#define CSTARTADD_14           (14*0x1000u)   /* ADC12 Conversion Start Address: 14 */
#define CSTARTADD_15           (15*0x1000u)   /* ADC12 Conversion Start Address: 15 */

/* ADC12MCTLx */
#define INCH0                  (0x0001)       /* ADC12 Input Channel Select Bit 0 */
#define INCH1                  (0x0002)       /* ADC12 Input Channel Select Bit 1 */
#define INCH2                  (0x0004)       /* ADC12 Input Channel Select Bit 2 */
#define INCH3                  (0x0008)       /* ADC12 Input Channel Select Bit 3 */
#define SREF0                  (0x0010)       /* ADC12 Select Reference Bit 0 */
#define SREF1                  (0x0020)       /* ADC12 Select Reference Bit 1 */
#define SREF2                  (0x0040)       /* ADC12 Select Reference Bit 2 */
#define EOS                    (0x0080)       /* ADC12 End of Sequence */

#define INCH_0                 (0)            /* ADC12 Input Channel 0 */
#define INCH_1                 (1)            /* ADC12 Input Channel 1 */
#define INCH_2                 (2)            /* ADC12 Input Channel 2 */
#define INCH_3                 (3)            /* ADC12 Input Channel 3 */
#define INCH_4                 (4)            /* ADC12 Input Channel 4 */
#define INCH_5                 (5)            /* ADC12 Input Channel 5 */
#define INCH_6                 (6)            /* ADC12 Input Channel 6 */
#define INCH_7                 (7)            /* ADC12 Input Channel 7 */
#define INCH_8                 (8)            /* ADC12 Input Channel 8 */
#define INCH_9                 (9)            /* ADC12 Input Channel 9 */
#define INCH_10                (10)           /* ADC12 Input Channel 10 */
#define INCH_11                (11)           /* ADC12 Input Channel 11 */
#define INCH_12                (12)           /* ADC12 Input Channel 12 */
#define INCH_13                (13)           /* ADC12 Input Channel 13 */
#define INCH_14                (14)           /* ADC12 Input Channel 14 */
#define INCH_15                (15)           /* ADC12 Input Channel 15 */

#define SREF_0                 (0*0x10u)      /* ADC12 Select Reference 0 */
#define SREF_1                 (1*0x10u)      /* ADC12 Select Reference 1 */
#define SREF_2                 (2*0x10u)      /* ADC12 Select Reference 2 */
#define SREF_3                 (3*0x10u)      /* ADC12 Select Reference 3 */
#define SREF_4                 (4*0x10u)      /* ADC12 Select Reference 4 */
#define SREF_5                 (5*0x10u)      /* ADC12 Select Reference 5 */
#define SREF_6                 (6*0x10u)      /* ADC12 Select Reference 6 */
#define SREF_7                 (7*0x10u)      /* ADC12 Select Reference 7 */

/* ADC12IV Definitions */
#define ADC12IV_NONE           (0x0000)       /* No Interrupt pending */
#define ADC12IV_ADC12OVIFG     (0x0002)       /* ADC12OVIFG */
#define ADC12IV_ADC12TOVIFG    (0x0004)       /* ADC12TOVIFG */
#define ADC12IV_ADC12IFG0      (0x0006)       /* ADC12IFG0 */
#define ADC12IV_ADC12IFG1      (0x0008)       /* ADC12IFG1 */
#define ADC12IV_ADC12IFG2      (0x000A)       /* ADC12IFG2 */
#define ADC12IV_ADC12IFG3      (0x000C)       /* ADC12IFG3 */
#define ADC12IV_ADC12IFG4      (0x000E)       /* ADC12IFG4 */
#define ADC12IV_ADC12IFG5      (0x0010)       /* ADC12IFG5 */
#define ADC12IV_ADC12IFG6      (0x0012)       /* ADC12IFG6 */
#define ADC12IV_ADC12IFG7      (0x0014)       /* ADC12IFG7 */
#define ADC12IV_ADC12IFG8      (0x0016)       /* ADC12IFG8 */
#define ADC12IV_ADC12IFG9      (0x0018)       /* ADC12IFG9 */
#define ADC12IV_ADC12IFG10     (0x001A)       /* ADC12IFG10 */
#define ADC12IV_ADC12IFG11     (0x001C)       /* ADC12IFG11 */
#define ADC12IV_ADC12IFG12     (0x001E)       /* ADC12IFG12 */
#define ADC12IV_ADC12IFG13     (0x0020)       /* ADC12IFG13 */
#define ADC12IV_ADC12IFG14     (0x0022)       /* ADC12IFG14 */
#define ADC12IV_ADC12IFG15     (0x0024)       /* ADC12IFG15 */

/************************************************************
* BASIC TIMER with Real Time Clock
************************************************************/
#define __MSP430_HAS_BT_RTC__                 /* Definition to show that Module is available */

SFR_8BIT(BTCTL);                              /* Basic Timer Control */
SFR_8BIT(RTCCTL);                             /* Real Time Clock Control */
SFR_8BIT(RTCNT1);                             /* Real Time Counter 1 */
SFR_8BIT(RTCNT2);                             /* Real Time Counter 2 */
SFR_8BIT(RTCNT3);                             /* Real Time Counter 3 */
SFR_8BIT(RTCNT4);                             /* Real Time Counter 4 */
SFR_8BIT(BTCNT1);                             /* Basic Timer Count 1 */
SFR_8BIT(BTCNT2);                             /* Basic Timer Count 2 */
SFR_8BIT(RTCDAY);                             /* Real Time Clock Day */
SFR_8BIT(RTCMON);                             /* Real Time Clock Month */
SFR_8BIT(RTCYEARL);                           /* Real Time Clock Year (Low Byte) */
SFR_8BIT(RTCYEARH);                           /* Real Time Clock Year (High Byte) */
#define RTCSEC                 RTCNT1
#define RTCMIN                 RTCNT2
#define RTCHOUR                RTCNT3
#define RTCDOW                 RTCNT4

SFR_16BIT(RTCTL);                             /* Basic/Real Timer Control */
SFR_16BIT(RTCTIM0);                           /* Real Time Clock Time 0 */
SFR_16BIT(RTCTIM1);                           /* Real Time Clock Time 1 */
SFR_16BIT(BTCNT12);                           /* Basic Timer Count 1/2 */
SFR_16BIT(RTCDATE);                           /* Real Time Clock Date */
SFR_16BIT(RTCYEAR);                           /* Real Time Clock Year */
#define RTCNT12                RTCTIM0
#define RTCNT34                RTCTIM1

#define BTSSEL                 (0x80)         /* fBT = fMCLK (main clock) */
#define BTHOLD                 (0x40)         /* BT1 is held if this bit is set */
#define BTDIV                  (0x20)         /* fCLK2 = ACLK:256 */
//#define res               (0x10)
//#define res               (0x08)
#define BTIP2                  (0x04)
#define BTIP1                  (0x02)
#define BTIP0                  (0x01)

#define RTCBCD                 (0x80)         /* RTC BCD Select */
#define RTCHOLD                (0x40)         /* RTC Hold */
#define RTCMODE1               (0x20)         /* RTC Mode 1 */
#define RTCMODE0               (0x10)         /* RTC Mode 0 */
#define RTCTEV1                (0x08)         /* RTC Time Event 1 */
#define RTCTEV0                (0x04)         /* RTC Time Event 0 */
#define RTCIE                  (0x02)         /* RTC Interrupt Enable */
#define RTCFG                  (0x01)         /* RTC Event Flag */

#define RTCTEV_0               (0x00)         /* RTC Time Event: 0 */
#define RTCTEV_1               (0x04)         /* RTC Time Event: 1 */
#define RTCTEV_2               (0x08)         /* RTC Time Event: 2 */
#define RTCTEV_3               (0x0C)         /* RTC Time Event: 3 */
#define RTCMODE_0              (0x00)         /* RTC Mode: 0 */
#define RTCMODE_1              (0x10)         /* RTC Mode: 1 */
#define RTCMODE_2              (0x20)         /* RTC Mode: 2 */
#define RTCMODE_3              (0x30)         /* RTC Mode: 3 */

/* Frequency of the BTCNT2 coded with Bit 5 and 7 in BTCTL */
#define BT_fCLK2_ACLK          (0x00)
#define BT_fCLK2_ACLK_DIV256   (BTDIV)
#define BT_fCLK2_MCLK          (BTSSEL)

/* Interrupt interval time fINT coded with Bits 0-2 in BTCTL */
#define BT_fCLK2_DIV2          (0x00)         /* fINT = fCLK2:2 (default) */
#define BT_fCLK2_DIV4          (BTIP0)        /* fINT = fCLK2:4 */
#define BT_fCLK2_DIV8          (BTIP1)        /* fINT = fCLK2:8 */
#define BT_fCLK2_DIV16         (BTIP1+BTIP0)  /* fINT = fCLK2:16 */
#define BT_fCLK2_DIV32         (BTIP2)        /* fINT = fCLK2:32 */
#define BT_fCLK2_DIV64         (BTIP2+BTIP0)  /* fINT = fCLK2:64 */
#define BT_fCLK2_DIV128        (BTIP2+BTIP1)  /* fINT = fCLK2:128 */
#define BT_fCLK2_DIV256     (BTIP2+BTIP1+BTIP0)       /* fINT = fCLK2:256 */

/* with assumed vlues of fACLK=32KHz, fMCLK=1MHz */
/* fBT=fACLK is thought for longer interval times */
#define BT_ADLY_0_064          (0x00)         /* 0.064ms interval (default) */
#define BT_ADLY_0_125          (BTIP0)        /* 0.125ms    " */
#define BT_ADLY_0_25           (BTIP1)        /* 0.25ms     " */
#define BT_ADLY_0_5            (BTIP1+BTIP0)  /* 0.5ms      " */
#define BT_ADLY_1              (BTIP2)        /* 1ms        " */
#define BT_ADLY_2              (BTIP2+BTIP0)  /* 2ms        " */
#define BT_ADLY_4              (BTIP2+BTIP1)  /* 4ms        " */
#define BT_ADLY_8           (BTIP2+BTIP1+BTIP0)       /* 8ms        " */
#define BT_ADLY_16             (BTDIV)        /* 16ms       " */
#define BT_ADLY_32             (BTDIV+BTIP0)  /* 32ms       " */
#define BT_ADLY_64             (BTDIV+BTIP1)  /* 64ms       " */
#define BT_ADLY_125         (BTDIV+BTIP1+BTIP0)       /* 125ms      " */
#define BT_ADLY_250            (BTDIV+BTIP2)  /* 250ms      " */
#define BT_ADLY_500         (BTDIV+BTIP2+BTIP0)       /* 500ms      " */
#define BT_ADLY_1000        (BTDIV+BTIP2+BTIP1)       /* 1000ms     " */
#define BT_ADLY_2000        (BTDIV+BTIP2+BTIP1+BTIP0) /* 2000ms     " */
/* fCLK2=fMCLK (1MHz) is thought for short interval times */
/* the timing for short intervals is more precise than ACLK */
/* NOTE */
/* Be sure that the SCFQCTL-Register is set to 01Fh so that fMCLK=1MHz */
/* Too low interval time results in interrupts too frequent for the processor to handle! */
#define BT_MDLY_0_002          (BTSSEL)       /* 0.002ms interval       *** interval times */
#define BT_MDLY_0_004          (BTSSEL+BTIP0) /* 0.004ms    "           *** too short for */
#define BT_MDLY_0_008          (BTSSEL+BTIP1) /* 0.008ms    "           *** interrupt */
#define BT_MDLY_0_016       (BTSSEL+BTIP1+BTIP0)      /* 0.016ms    "           *** handling */
#define BT_MDLY_0_032          (BTSSEL+BTIP2) /* 0.032ms    " */
#define BT_MDLY_0_064       (BTSSEL+BTIP2+BTIP0)      /* 0.064ms    " */
#define BT_MDLY_0_125       (BTSSEL+BTIP2+BTIP1)      /* 0.125ms    " */
#define BT_MDLY_0_25        (BTSSEL+BTIP2+BTIP1+BTIP0)/* 0.25ms     " */

/* Hold coded with Bits 6-7 in BT(1)CTL */
/* this is for BT */
#define BTHOLD_CNT1            (BTHOLD)       /* BTCNT1 is held while BTHOLD is set */
#define BTHOLD_CNT1_2          (BTHOLD+BTDIV) /* BT1CNT1 .AND. BT1CNT2 are held while ~ is set */

/* INTERRUPT CONTROL BITS */
/* #define BTIE                0x80 */
/* #define BTIFG               0x80 */

/************************************************************
* Comparator A
************************************************************/
#define __MSP430_HAS_COMPA__                  /* Definition to show that Module is available */

SFR_8BIT(CACTL1);                             /* Comparator A Control 1 */
SFR_8BIT(CACTL2);                             /* Comparator A Control 2 */
SFR_8BIT(CAPD);                               /* Comparator A Port Disable */

#define CAIFG                  (0x01)         /* Comp. A Interrupt Flag */
#define CAIE                   (0x02)         /* Comp. A Interrupt Enable */
#define CAIES                  (0x04)         /* Comp. A Int. Edge Select: 0:rising / 1:falling */
#define CAON                   (0x08)         /* Comp. A enable */
#define CAREF0                 (0x10)         /* Comp. A Internal Reference Select 0 */
#define CAREF1                 (0x20)         /* Comp. A Internal Reference Select 1 */
#define CARSEL                 (0x40)         /* Comp. A Internal Reference Enable */
#define CAEX                   (0x80)         /* Comp. A Exchange Inputs */

#define CAREF_0                (0x00)         /* Comp. A Int. Ref. Select 0 : Off */
#define CAREF_1                (0x10)         /* Comp. A Int. Ref. Select 1 : 0.25*Vcc */
#define CAREF_2                (0x20)         /* Comp. A Int. Ref. Select 2 : 0.5*Vcc */
#define CAREF_3                (0x30)         /* Comp. A Int. Ref. Select 3 : Vt*/

#define CAOUT                  (0x01)         /* Comp. A Output */
#define CAF                    (0x02)         /* Comp. A Enable Output Filter */
#define P2CA0                  (0x04)         /* Comp. A Connect External Signal to CA0 : 1 */
#define P2CA1                  (0x08)         /* Comp. A Connect External Signal to CA1 : 1 */
#define CACTL24                (0x10)
#define CACTL25                (0x20)
#define CACTL26                (0x40)
#define CACTL27                (0x80)

#define CAPD0                  (0x01)         /* Comp. A Disable Input Buffer of Port Register .0 */
#define CAPD1                  (0x02)         /* Comp. A Disable Input Buffer of Port Register .1 */
#define CAPD2                  (0x04)         /* Comp. A Disable Input Buffer of Port Register .2 */
#define CAPD3                  (0x08)         /* Comp. A Disable Input Buffer of Port Register .3 */
#define CAPD4                  (0x10)         /* Comp. A Disable Input Buffer of Port Register .4 */
#define CAPD5                  (0x20)         /* Comp. A Disable Input Buffer of Port Register .5 */
#define CAPD6                  (0x40)         /* Comp. A Disable Input Buffer of Port Register .6 */
#define CAPD7                  (0x80)         /* Comp. A Disable Input Buffer of Port Register .7 */

/************************************************************
* DAC12
************************************************************/
#define __MSP430_HAS_DAC12_2__                /* Definition to show that Module is available */

SFR_16BIT(DAC12_0CTL);                        /* DAC12_0 Control */
SFR_16BIT(DAC12_1CTL);                        /* DAC12_1 Control */

#define DAC12GRP               (0x0001)       /* DAC12 group */
#define DAC12ENC               (0x0002)       /* DAC12 enable conversion */
#define DAC12IFG               (0x0004)       /* DAC12 interrupt flag */
#define DAC12IE                (0x0008)       /* DAC12 interrupt enable */
#define DAC12DF                (0x0010)       /* DAC12 data format */
#define DAC12AMP0              (0x0020)       /* DAC12 amplifier bit 0 */
#define DAC12AMP1              (0x0040)       /* DAC12 amplifier bit 1 */
#define DAC12AMP2              (0x0080)       /* DAC12 amplifier bit 2 */
#define DAC12IR                (0x0100)       /* DAC12 input reference and output range */
#define DAC12CALON             (0x0200)       /* DAC12 calibration */
#define DAC12LSEL0             (0x0400)       /* DAC12 load select bit 0 */
#define DAC12LSEL1             (0x0800)       /* DAC12 load select bit 1 */
#define DAC12RES               (0x1000)       /* DAC12 resolution */
#define DAC12SREF0             (0x2000)       /* DAC12 reference bit 0 */
#define DAC12SREF1             (0x4000)       /* DAC12 reference bit 1 */
#define DAC12OPS               (0x8000)       /* DAC12 Operation Amp. */

#define DAC12AMP_0             (0*0x0020u)    /* DAC12 amplifier 0: off,    3-state */
#define DAC12AMP_1             (1*0x0020u)    /* DAC12 amplifier 1: off,    off */
#define DAC12AMP_2             (2*0x0020u)    /* DAC12 amplifier 2: low,    low */
#define DAC12AMP_3             (3*0x0020u)    /* DAC12 amplifier 3: low,    medium */
#define DAC12AMP_4             (4*0x0020u)    /* DAC12 amplifier 4: low,    high */
#define DAC12AMP_5             (5*0x0020u)    /* DAC12 amplifier 5: medium, medium */
#define DAC12AMP_6             (6*0x0020u)    /* DAC12 amplifier 6: medium, high */
#define DAC12AMP_7             (7*0x0020u)    /* DAC12 amplifier 7: high,   high */

#define DAC12LSEL_0            (0*0x0400u)    /* DAC12 load select 0: direct */
#define DAC12LSEL_1            (1*0x0400u)    /* DAC12 load select 1: latched with DAT */
#define DAC12LSEL_2            (2*0x0400u)    /* DAC12 load select 2: latched with pos. Timer_A3.OUT1 */
#define DAC12LSEL_3            (3*0x0400u)    /* DAC12 load select 3: latched with pos. Timer_B7.OUT1 */

#define DAC12SREF_0            (0*0x2000u)    /* DAC12 reference 0: Vref+ */
#define DAC12SREF_1            (1*0x2000u)    /* DAC12 reference 1: Vref+ */
#define DAC12SREF_2            (2*0x2000u)    /* DAC12 reference 2: Veref+ */
#define DAC12SREF_3            (3*0x2000u)    /* DAC12 reference 3: Veref+ */

SFR_16BIT(DAC12_0DAT);                        /* DAC12_0 Data */
SFR_16BIT(DAC12_1DAT);                        /* DAC12_1 Data */
/************************************************************
* DMA_X
************************************************************/
#define __MSP430_HAS_DMAX_3__                 /* Definition to show that Module is available */

SFR_16BIT(DMACTL0);                           /* DMA Module Control 0 */
#define DMA0TSEL0              (0x0001)       /* DMA channel 0 transfer select bit 0 */
#define DMA0TSEL1              (0x0002)       /* DMA channel 0 transfer select bit 1 */
#define DMA0TSEL2              (0x0004)       /* DMA channel 0 transfer select bit 2 */
#define DMA0TSEL3              (0x0008)       /* DMA channel 0 transfer select bit 3 */
#define DMA1TSEL0              (0x0010)       /* DMA channel 1 transfer select bit 0 */
#define DMA1TSEL1              (0x0020)       /* DMA channel 1 transfer select bit 1 */
#define DMA1TSEL2              (0x0040)       /* DMA channel 1 transfer select bit 2 */
#define DMA1TSEL3              (0x0080)       /* DMA channel 1 transfer select bit 3 */
#define DMA2TSEL0              (0x0100)       /* DMA channel 2 transfer select bit 0 */
#define DMA2TSEL1              (0x0200)       /* DMA channel 2 transfer select bit 1 */
#define DMA2TSEL2              (0x0400)       /* DMA channel 2 transfer select bit 2 */
#define DMA2TSEL3              (0x0800)       /* DMA channel 2 transfer select bit 3 */

#define DMA0TSEL_0             (0*0x0001u)    /* DMA channel 0 transfer select 0:  DMA_REQ (sw)*/
#define DMA0TSEL_1             (1*0x0001u)    /* DMA channel 0 transfer select 1:  Timer_A (TACCR2.IFG) */
#define DMA0TSEL_2             (2*0x0001u)    /* DMA channel 0 transfer select 2:  Timer_B (TBCCR2.IFG) */
#define DMA0TSEL_3             (3*0x0001u)    /* DMA channel 0 transfer select 3:  USCIA receive */
#define DMA0TSEL_4             (4*0x0001u)    /* DMA channel 0 transfer select 4:  USCIA transmit */
#define DMA0TSEL_5             (5*0x0001u)    /* DMA channel 0 transfer select 5:  DAC12_0CTL.DAC12IFG */
#define DMA0TSEL_6             (6*0x0001u)    /* DMA channel 0 transfer select 6:  ADC12 (ADC12IFG) */
#define DMA0TSEL_7             (7*0x0001u)    /* DMA channel 0 transfer select 7:  Timer_A (TACCR0.IFG) */
#define DMA0TSEL_8             (8*0x0001u)    /* DMA channel 0 transfer select 8:  Timer_B (TBCCR0.IFG) */
#define DMA0TSEL_9             (9*0x0001u)    /* DMA channel 0 transfer select 9:  UART1 receive */
#define DMA0TSEL_10            (10*0x0001u)   /* DMA channel 0 transfer select 10: UART1 transmit */
#define DMA0TSEL_11            (11*0x0001u)   /* DMA channel 0 transfer select 11: Multiplier ready */
#define DMA0TSEL_12            (12*0x0001u)   /* DMA channel 0 transfer select 12: USCIB receive */
#define DMA0TSEL_13            (13*0x0001u)   /* DMA channel 0 transfer select 13: USCIB transmit */
#define DMA0TSEL_14            (14*0x0001u)   /* DMA channel 0 transfer select 14: previous DMA channel DMA2IFG */
#define DMA0TSEL_15            (15*0x0001u)   /* DMA channel 0 transfer select 15: ext. Trigger (DMAE0) */

#define DMA1TSEL_0             (0*0x0010u)    /* DMA channel 1 transfer select 0:  DMA_REQ */
#define DMA1TSEL_1             (1*0x0010u)    /* DMA channel 1 transfer select 1:  Timer_A CCRIFG.2 */
#define DMA1TSEL_2             (2*0x0010u)    /* DMA channel 1 transfer select 2:  Timer_B CCRIFG.2 */
#define DMA1TSEL_3             (3*0x0010u)    /* DMA channel 1 transfer select 3:  USCIA receive */
#define DMA1TSEL_4             (4*0x0010u)    /* DMA channel 1 transfer select 4:  USCIA transmit */
#define DMA1TSEL_5             (5*0x0010u)    /* DMA channel 1 transfer select 5:  DAC12.0IFG */
#define DMA1TSEL_6             (6*0x0010u)    /* DMA channel 1 transfer select 6:  ADC12 (ADC12IFG) */
#define DMA1TSEL_7             (7*0x0010u)    /* DMA channel 1 transfer select 7:  Timer_A (TACCR0.IFG) */
#define DMA1TSEL_8             (8*0x0010u)    /* DMA channel 1 transfer select 8:  Timer_B (TBCCR0.IFG) */
#define DMA1TSEL_9             (9*0x0010u)    /* DMA channel 1 transfer select 9:  UART1 receive */
#define DMA1TSEL_10            (10*0x0010u)   /* DMA channel 1 transfer select 10: UART1 transmit */
#define DMA1TSEL_11            (11*0x0010u)   /* DMA channel 1 transfer select 11: Multiplier ready */
#define DMA1TSEL_12            (12*0x0010u)   /* DMA channel 1 transfer select 12: USCIB receive */
#define DMA1TSEL_13            (13*0x0010u)   /* DMA channel 1 transfer select 13: USCIB transmit */
#define DMA1TSEL_14            (14*0x0010u)   /* DMA channel 1 transfer select 14: previous DMA channel DMA0IFG */
#define DMA1TSEL_15            (15*0x0010u)   /* DMA channel 1 transfer select 15: ext. Trigger (DMAE0) */

#define DMA2TSEL_0             (0*0x0100u)    /* DMA channel 2 transfer select 0:  DMA_REQ */
#define DMA2TSEL_1             (1*0x0100u)    /* DMA channel 2 transfer select 1:  Timer_A CCRIFG.2 */
#define DMA2TSEL_2             (2*0x0100u)    /* DMA channel 2 transfer select 2:  Timer_B CCRIFG.2 */
#define DMA2TSEL_3             (3*0x0100u)    /* DMA channel 2 transfer select 3:  USCIA receive */
#define DMA2TSEL_4             (4*0x0100u)    /* DMA channel 2 transfer select 4:  USCIA transmit */
#define DMA2TSEL_5             (5*0x0100u)    /* DMA channel 2 transfer select 5:  DAC12.0IFG */
#define DMA2TSEL_6             (6*0x0100u)    /* DMA channel 2 transfer select 6:  ADC12 (ADC12IFG) */
#define DMA2TSEL_7             (7*0x0100u)    /* DMA channel 2 transfer select 7:  Timer_A (TACCR0.IFG) */
#define DMA2TSEL_8             (8*0x0100u)    /* DMA channel 2 transfer select 8:  Timer_B (TBCCR0.IFG) */
#define DMA2TSEL_9             (9*0x0100u)    /* DMA channel 2 transfer select 9:  UART1 receive */
#define DMA2TSEL_10            (10*0x0100u)   /* DMA channel 2 transfer select 10: UART1 transmit */
#define DMA2TSEL_11            (11*0x0100u)   /* DMA channel 2 transfer select 11: Multiplier ready */
#define DMA2TSEL_12            (12*0x0100u)   /* DMA channel 2 transfer select 12: USCIB receive */
#define DMA2TSEL_13            (13*0x0100u)   /* DMA channel 2 transfer select 13: USCIB transmit */
#define DMA2TSEL_14            (14*0x0100u)   /* DMA channel 2 transfer select 14: previous DMA channel DMA1IFG */
#define DMA2TSEL_15            (15*0x0100u)   /* DMA channel 2 transfer select 15: ext. Trigger (DMAE0) */

SFR_16BIT(DMACTL1);                           /* DMA Module Control 1 */
#define ENNMI                  (0x0001)       /* Enable NMI interruption of DMA */
#define ROUNDROBIN             (0x0002)       /* Round-Robin DMA channel priorities */
#define DMAONFETCH             (0x0004)       /* DMA transfer on instruction fetch */

SFR_16BIT(DMAIV);                             /* DMA Interrupt Vector Word */
SFR_16BIT(DMA0CTL);                           /* DMA Channel 0 Control */
SFR_16BIT(DMA1CTL);                           /* DMA Channel 1 Control */
SFR_16BIT(DMA2CTL);                           /* DMA Channel 2 Control */

#define DMAREQ                 (0x0001)       /* Initiate DMA transfer with DMATSEL */
#define DMAABORT               (0x0002)       /* DMA transfer aborted by NMI */
#define DMAIE                  (0x0004)       /* DMA interrupt enable */
#define DMAIFG                 (0x0008)       /* DMA interrupt flag */
#define DMAEN                  (0x0010)       /* DMA enable */
#define DMALEVEL               (0x0020)       /* DMA level sensitive trigger select */
#define DMASRCBYTE             (0x0040)       /* DMA source byte */
#define DMADSTBYTE             (0x0080)       /* DMA destination byte */
#define DMASRCINCR0            (0x0100)       /* DMA source increment bit 0 */
#define DMASRCINCR1            (0x0200)       /* DMA source increment bit 1 */
#define DMADSTINCR0            (0x0400)       /* DMA destination increment bit 0 */
#define DMADSTINCR1            (0x0800)       /* DMA destination increment bit 1 */
#define DMADT0                 (0x1000)       /* DMA transfer mode bit 0 */
#define DMADT1                 (0x2000)       /* DMA transfer mode bit 1 */
#define DMADT2                 (0x4000)       /* DMA transfer mode bit 2 */

#define DMASWDW                (0*0x0040u)    /* DMA transfer: source word to destination word */
#define DMASBDW                (1*0x0040u)    /* DMA transfer: source byte to destination word */
#define DMASWDB                (2*0x0040u)    /* DMA transfer: source word to destination byte */
#define DMASBDB                (3*0x0040u)    /* DMA transfer: source byte to destination byte */

#define DMASRCINCR_0           (0*0x0100u)    /* DMA source increment 0: source address unchanged */
#define DMASRCINCR_1           (1*0x0100u)    /* DMA source increment 1: source address unchanged */
#define DMASRCINCR_2           (2*0x0100u)    /* DMA source increment 2: source address decremented */
#define DMASRCINCR_3           (3*0x0100u)    /* DMA source increment 3: source address incremented */

#define DMADSTINCR_0           (0*0x0400u)    /* DMA destination increment 0: destination address unchanged */
#define DMADSTINCR_1           (1*0x0400u)    /* DMA destination increment 1: destination address unchanged */
#define DMADSTINCR_2           (2*0x0400u)    /* DMA destination increment 2: destination address decremented */
#define DMADSTINCR_3           (3*0x0400u)    /* DMA destination increment 3: destination address incremented */

#define DMADT_0                (0*0x1000u)    /* DMA transfer mode 0: single */
#define DMADT_1                (1*0x1000u)    /* DMA transfer mode 1: block */
#define DMADT_2                (2*0x1000u)    /* DMA transfer mode 2: interleaved */
#define DMADT_3                (3*0x1000u)    /* DMA transfer mode 3: interleaved */
#define DMADT_4                (4*0x1000u)    /* DMA transfer mode 4: single, repeat */
#define DMADT_5                (5*0x1000u)    /* DMA transfer mode 5: block, repeat */
#define DMADT_6                (6*0x1000u)    /* DMA transfer mode 6: interleaved, repeat */
#define DMADT_7                (7*0x1000u)    /* DMA transfer mode 7: interleaved, repeat */

SFR_20BIT(DMA0SA);                            /* DMA Channel 0 Source Address */
SFR_16BIT(DMA0SAL);                           /* DMA Channel 0 Source Address */
SFR_20BIT(DMA0DA);                            /* DMA Channel 0 Destination Address */
SFR_16BIT(DMA0DAL);                           /* DMA Channel 0 Destination Address */
SFR_16BIT(DMA0SZ);                            /* DMA Channel 0 Transfer Size */
SFR_20BIT(DMA1SA);                            /* DMA Channel 1 Source Address */
SFR_16BIT(DMA1SAL);                           /* DMA Channel 1 Source Address */
SFR_20BIT(DMA1DA);                            /* DMA Channel 1 Destination Address */
SFR_16BIT(DMA1DAL);                           /* DMA Channel 1 Destination Address */
SFR_16BIT(DMA1SZ);                            /* DMA Channel 1 Transfer Size */
SFR_20BIT(DMA2SA);                            /* DMA Channel 2 Source Address */
SFR_16BIT(DMA2SAL);                           /* DMA Channel 2 Source Address */
SFR_20BIT(DMA2DA);                            /* DMA Channel 2 Destination Address */
SFR_16BIT(DMA2DAL);                           /* DMA Channel 2 Destination Address */
SFR_16BIT(DMA2SZ);                            /* DMA Channel 2 Transfer Size */

/* DMAIV Definitions */
#define DMAIV_NONE             (0x0000)       /* No Interrupt pending */
#define DMAIV_DMA0IFG          (0x0002)       /* DMA0IFG */
#define DMAIV_DMA1IFG          (0x0004)       /* DMA1IFG */
#define DMAIV_DMA2IFG          (0x0006)       /* DMA2IFG */

/*************************************************************
* Flash Memory
*************************************************************/
#define __MSP430_HAS_FLASH__                  /* Definition to show that Module is available */
#define __MSP430_HAS_2FLASH_IP__                /* Definition to show that Module is available */

SFR_16BIT(FCTL1);                             /* FLASH Control 1 */
SFR_16BIT(FCTL2);                             /* FLASH Control 2 */
SFR_16BIT(FCTL3);                             /* FLASH Control 3 */

#define FRKEY                  (0x9600)       /* Flash key returned by read */
#define FWKEY                  (0xA500)       /* Flash key for write */
#define FXKEY                  (0x3300)       /* for use with XOR instruction */

#define ERASE                  (0x0002)       /* Enable bit for Flash segment erase */
#define MERAS                  (0x0004)       /* Enable bit for Flash mass erase */
#define GMERAS                 (0x0008)       /* Enable bit for Flash global mass erase */
#define CPUEX                  (0x0010)       /* Enable bit for CPU Execution during Flash write/erase */
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

/************************************************************
* SYSTEM CLOCK, FLL+
************************************************************/
#define __MSP430_HAS_FLLPLUS__                /* Definition to show that Module is available */

SFR_8BIT(SCFI0);                              /* System Clock Frequency Integrator 0 */
#define FN_2                   (0x04)         /* fDCOCLK =   1.4-12MHz*/
#define FN_3                   (0x08)         /* fDCOCLK =   2.2-17Mhz*/
#define FN_4                   (0x10)         /* fDCOCLK =   3.2-25Mhz*/
#define FN_8                   (0x20)         /* fDCOCLK =     5-40Mhz*/
#define FLLD0                  (0x40)         /* Loop Divider Bit : 0 */
#define FLLD1                  (0x80)         /* Loop Divider Bit : 1 */

#define FLLD_1                 (0x00)         /* Multiply Selected Loop Freq. By 1 */
#define FLLD_2                 (0x40)         /* Multiply Selected Loop Freq. By 2 */
#define FLLD_4                 (0x80)         /* Multiply Selected Loop Freq. By 4 */
#define FLLD_8                 (0xC0)         /* Multiply Selected Loop Freq. By 8 */

SFR_8BIT(SCFI1);                              /* System Clock Frequency Integrator 1 */
SFR_8BIT(SCFQCTL);                            /* System Clock Frequency Control */
/* System clock frequency values fMCLK coded with Bits 0-6 in SCFQCTL */
/* #define SCFQ_32K            0x00                        fMCLK=1*fACLK       only a range from */
#define SCFQ_64K               (0x01)         /* fMCLK=2*fACLK          1+1 to 127+1 is possible */
#define SCFQ_128K              (0x03)         /* fMCLK=4*fACLK */
#define SCFQ_256K              (0x07)         /* fMCLK=8*fACLK */
#define SCFQ_512K              (0x0F)         /* fMCLK=16*fACLK */
#define SCFQ_1M                (0x1F)         /* fMCLK=32*fACLK */
#define SCFQ_2M                (0x3F)         /* fMCLK=64*fACLK */
#define SCFQ_4M                (0x7F)         /* fMCLK=128*fACLK */
#define SCFQ_M                 (0x80)         /* Modulation Disable */

SFR_8BIT(FLL_CTL0);                           /* FLL+ Control 0 */
#define DCOF                   (0x01)         /* DCO Fault Flag */
#define LFOF                   (0x02)         /* Low Frequency Oscillator Fault Flag */
#define XT1OF                  (0x04)         /* High Frequency Oscillator 1 Fault Flag */
#define XT2OF                  (0x08)         /* High Frequency Oscillator 2 Fault Flag */
#define OSCCAP0                (0x10)         /* XIN/XOUT Cap 0 */
#define OSCCAP1                (0x20)         /* XIN/XOUT Cap 1 */
#define XTS_FLL                (0x40)         /* 1: Selects high-freq. oscillator */
#define DCOPLUS                (0x80)         /* DCO+ Enable */

#define XCAP0PF                (0x00)         /* XIN Cap = XOUT Cap = 0pf */
#define XCAP10PF               (0x10)         /* XIN Cap = XOUT Cap = 10pf */
#define XCAP14PF               (0x20)         /* XIN Cap = XOUT Cap = 14pf */
#define XCAP18PF               (0x30)         /* XIN Cap = XOUT Cap = 18pf */
#define OSCCAP_0               (0x00)         /* XIN Cap = XOUT Cap = 0pf */
#define OSCCAP_1               (0x10)         /* XIN Cap = XOUT Cap = 10pf */
#define OSCCAP_2               (0x20)         /* XIN Cap = XOUT Cap = 14pf */
#define OSCCAP_3               (0x30)         /* XIN Cap = XOUT Cap = 18pf */

SFR_8BIT(FLL_CTL1);                           /* FLL+ Control 1 */
#define FLL_DIV0               (0x01)         /* FLL+ Divide Px.x/ACLK 0 */
#define FLL_DIV1               (0x02)         /* FLL+ Divide Px.x/ACLK 1 */
#define SELS                   (0x04)         /* Peripheral Module Clock Source (0: DCO, 1: XT2) */
#define SELM0                  (0x08)         /* MCLK Source Select 0 */
#define SELM1                  (0x10)         /* MCLK Source Select 1 */
#define XT2OFF                 (0x20)         /* High Frequency Oscillator 2 (XT2) disable */
#define SMCLKOFF               (0x40)         /* Peripheral Module Clock (SMCLK) disable */
#define LFXT1DIG               (0x80)         /* Enable Digital input for LF clock */

#define FLL_DIV_1              (0x00)         /* FLL+ Divide Px.x/ACLK By 1 */
#define FLL_DIV_2              (0x01)         /* FLL+ Divide Px.x/ACLK By 2 */
#define FLL_DIV_4              (0x02)         /* FLL+ Divide Px.x/ACLK By 4 */
#define FLL_DIV_8              (0x03)         /* FLL+ Divide Px.x/ACLK By 8 */

#define SELM_DCO               (0x00)         /* Select DCO for CPU MCLK */
#define SELM_XT2               (0x10)         /* Select XT2 for CPU MCLK */
#define SELM_A                 (0x18)         /* Select A (from LFXT1) for CPU MCLK */

/* INTERRUPT CONTROL BITS */
/* These two bits are defined in the Special Function Registers */
/* #define OFIFG               0x02 */
/* #define OFIE                0x02 */

/************************************************************
* LCD_A
************************************************************/
#define __MSP430_HAS_LCD_A__                  /* Definition to show that Module is available */

SFR_8BIT(LCDACTL);                            /* LCD_A Control Register */
#define LCDON                  (0x01)
#define LCDSON                 (0x04)
#define LCDMX0                 (0x08)
#define LCDMX1                 (0x10)
#define LCDFREQ0               (0x20)
#define LCDFREQ1               (0x40)
#define LCDFREQ2               (0x80)
/* Display modes coded with Bits 2-4 */
#define LCDSTATIC              (LCDSON)
#define LCD2MUX                (LCDMX0+LCDSON)
#define LCD3MUX                (LCDMX1+LCDSON)
#define LCD4MUX                (LCDMX1+LCDMX0+LCDSON)
/* Frequency select code with Bits 5-7 */
#define LCDFREQ_32             (0x00)         /* LCD Freq: ACLK divided by 32 */
#define LCDFREQ_64             (0x20)         /* LCD Freq: ACLK divided by 64 */
#define LCDFREQ_96             (0x40)         /* LCD Freq: ACLK divided by 96 */
#define LCDFREQ_128            (0x60)         /* LCD Freq: ACLK divided by 128 */
#define LCDFREQ_192            (0x80)         /* LCD Freq: ACLK divided by 192 */
#define LCDFREQ_256            (0xA0)         /* LCD Freq: ACLK divided by 256 */
#define LCDFREQ_384            (0xC0)         /* LCD Freq: ACLK divided by 384 */
#define LCDFREQ_512            (0xE0)         /* LCD Freq: ACLK divided by 512 */

SFR_8BIT(LCDAPCTL0);                          /* LCD_A Port Control Register 0 */
#define LCDS0                  (0x01)         /* LCD Segment  0 to  3 Enable. */
#define LCDS4                  (0x02)         /* LCD Segment  4 to  7 Enable. */
#define LCDS8                  (0x04)         /* LCD Segment  8 to 11 Enable. */
#define LCDS12                 (0x08)         /* LCD Segment 12 to 15 Enable. */
#define LCDS16                 (0x10)         /* LCD Segment 16 to 19 Enable. */
#define LCDS20                 (0x20)         /* LCD Segment 20 to 23 Enable. */
#define LCDS24                 (0x40)         /* LCD Segment 24 to 27 Enable. */
#define LCDS28                 (0x80)         /* LCD Segment 28 to 31 Enable. */

SFR_8BIT(LCDAPCTL1);                          /* LCD_A Port Control Register 1 */
#define LCDS32                 (0x01)         /* LCD Segment 32 to 35 Enable. */
#define LCDS36                 (0x02)         /* LCD Segment 36 to 39 Enable. */

SFR_8BIT(LCDAVCTL0);                          /* LCD_A Voltage Control Register 0 */
#define LCD2B                  (0x01)         /* Selects 1/2 bias. */
#define VLCDREF0               (0x02)         /* Selects reference voltage for regulated charge pump: 0 */
#define VLCDREF1               (0x04)         /* Selects reference voltage for regulated charge pump: 1 */
#define LCDCPEN                (0x08)         /* LCD Voltage Charge Pump Enable. */
#define VLCDEXT                (0x10)         /* Select external source for VLCD. */
#define LCDREXT                (0x20)         /* Selects external connections for LCD mid voltages. */
#define LCDR03EXT              (0x40)         /* Selects external connection for lowest LCD voltage. */

/* Reference voltage source select for the regulated charge pump */
#define VLCDREF_0              (0<<1)         /* Internal */
#define VLCDREF_1              (1<<1)         /* External */
#define VLCDREF_2              (2<<1)         /* Reserved */
#define VLCDREF_3              (3<<1)         /* Reserved */

SFR_8BIT(LCDAVCTL1);                          /* LCD_A Voltage Control Register 1 */
#define VLCD0                  (0x02)         /* VLCD select: 0 */
#define VLCD1                  (0x04)         /* VLCD select: 1 */
#define VLCD2                  (0x08)         /* VLCD select: 2 */
#define VLCD3                  (0x10)         /* VLCD select: 3 */

/* Charge pump voltage selections */
#define VLCD_0                 (0<<1)         /* Charge pump disabled */
#define VLCD_1                 (1<<1)         /* VLCD = 2.60V */
#define VLCD_2                 (2<<1)         /* VLCD = 2.66V */
#define VLCD_3                 (3<<1)         /* VLCD = 2.72V */
#define VLCD_4                 (4<<1)         /* VLCD = 2.78V */
#define VLCD_5                 (5<<1)         /* VLCD = 2.84V */
#define VLCD_6                 (6<<1)         /* VLCD = 2.90V */
#define VLCD_7                 (7<<1)         /* VLCD = 2.96V */
#define VLCD_8                 (8<<1)         /* VLCD = 3.02V */
#define VLCD_9                 (9<<1)         /* VLCD = 3.08V */
#define VLCD_10                (10<<1)        /* VLCD = 3.14V */
#define VLCD_11                (11<<1)        /* VLCD = 3.20V */
#define VLCD_12                (12<<1)        /* VLCD = 3.26V */
#define VLCD_13                (13<<1)        /* VLCD = 3.32V */
#define VLCD_14                (14<<1)        /* VLCD = 3.38V */
#define VLCD_15                (15<<1)        /* VLCD = 3.44V */

#define VLCD_DISABLED          (0<<1)         /* Charge pump disabled */
#define VLCD_2_60              (1<<1)         /* VLCD = 2.60V */
#define VLCD_2_66              (2<<1)         /* VLCD = 2.66V */
#define VLCD_2_72              (3<<1)         /* VLCD = 2.72V */
#define VLCD_2_78              (4<<1)         /* VLCD = 2.78V */
#define VLCD_2_84              (5<<1)         /* VLCD = 2.84V */
#define VLCD_2_90              (6<<1)         /* VLCD = 2.90V */
#define VLCD_2_96              (7<<1)         /* VLCD = 2.96V */
#define VLCD_3_02              (8<<1)         /* VLCD = 3.02V */
#define VLCD_3_08              (9<<1)         /* VLCD = 3.08V */
#define VLCD_3_14              (10<<1)        /* VLCD = 3.14V */
#define VLCD_3_20              (11<<1)        /* VLCD = 3.20V */
#define VLCD_3_26              (12<<1)        /* VLCD = 3.26V */
#define VLCD_3_32              (13<<1)        /* VLCD = 3.32V */
#define VLCD_3_38              (14<<1)        /* VLCD = 3.38V */
#define VLCD_3_44              (15<<1)        /* VLCD = 3.44V */

#define LCDMEM_                (0x0091)       /* LCD Memory */
#ifdef __ASM_HEADER__
#define LCDMEM                 (LCDMEM_)      /* LCD Memory (for assembler) */
#else
#define LCDMEM                 ((char*)       LCDMEM_) /* LCD Memory (for C) */
#endif
SFR_8BIT(LCDM1);                              /* LCD Memory 1 */
SFR_8BIT(LCDM2);                              /* LCD Memory 2 */
SFR_8BIT(LCDM3);                              /* LCD Memory 3 */
SFR_8BIT(LCDM4);                              /* LCD Memory 4 */
SFR_8BIT(LCDM5);                              /* LCD Memory 5 */
SFR_8BIT(LCDM6);                              /* LCD Memory 6 */
SFR_8BIT(LCDM7);                              /* LCD Memory 7 */
SFR_8BIT(LCDM8);                              /* LCD Memory 8 */
SFR_8BIT(LCDM9);                              /* LCD Memory 9 */
SFR_8BIT(LCDM10);                             /* LCD Memory 10 */
SFR_8BIT(LCDM11);                             /* LCD Memory 11 */
SFR_8BIT(LCDM12);                             /* LCD Memory 12 */
SFR_8BIT(LCDM13);                             /* LCD Memory 13 */
SFR_8BIT(LCDM14);                             /* LCD Memory 14 */
SFR_8BIT(LCDM15);                             /* LCD Memory 15 */
SFR_8BIT(LCDM16);                             /* LCD Memory 16 */
SFR_8BIT(LCDM17);                             /* LCD Memory 17 */
SFR_8BIT(LCDM18);                             /* LCD Memory 18 */
SFR_8BIT(LCDM19);                             /* LCD Memory 19 */
SFR_8BIT(LCDM20);                             /* LCD Memory 20 */

#define LCDMA                  (LCDM10)       /* LCD Memory A */
#define LCDMB                  (LCDM11)       /* LCD Memory B */
#define LCDMC                  (LCDM12)       /* LCD Memory C */
#define LCDMD                  (LCDM13)       /* LCD Memory D */
#define LCDME                  (LCDM14)       /* LCD Memory E */
#define LCDMF                  (LCDM15)       /* LCD Memory F */

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
* Operational Amplifier
************************************************************/
#define __MSP430_HAS_OA_3__                   /* Definition to show that Module is available */

SFR_8BIT(OA0CTL0);                            /* OA0 Control register 0 */
SFR_8BIT(OA0CTL1);                            /* OA0 Control register 1 */
SFR_8BIT(OA1CTL0);                            /* OA1 Control register 0 */
SFR_8BIT(OA1CTL1);                            /* OA1 Control register 1 */
SFR_8BIT(OA2CTL0);                            /* OA2 Control register 0 */
SFR_8BIT(OA2CTL1);                            /* OA2 Control register 1 */

#define OAADC0                 (0x01)         /* OAx output to ADC12 input channel select 0 */
#define OAADC1                 (0x02)         /* OAx output to ADC12 input channel select 1 */
#define OAPM0                  (0x04)         /* OAx Power mode select 0 */
#define OAPM1                  (0x08)         /* OAx Power mode select 1 */
#define OAP0                   (0x10)         /* OAx Non-inverting input select 0 */
#define OAP1                   (0x20)         /* OAx Non-inverting input select 1 */
#define OAN0                   (0x40)         /* OAx Inverting input select 0 */
#define OAN1                   (0x80)         /* OAx Inverting input select 1 */

#define OAPM_0                 (0x00)         /* OAx Power mode select: off */
#define OAPM_1                 (0x04)         /* OAx Power mode select: slow */
#define OAPM_2                 (0x08)         /* OAx Power mode select: meduim */
#define OAPM_3                 (0x0C)         /* OAx Power mode select: fast */
#define OAP_0                  (0x00)         /* OAx Non-inverting input select 00 */
#define OAP_1                  (0x10)         /* OAx Non-inverting input select 01 */
#define OAP_2                  (0x20)         /* OAx Non-inverting input select 10 */
#define OAP_3                  (0x30)         /* OAx Non-inverting input select 11 */
#define OAN_0                  (0x00)         /* OAx Inverting input select 00 */
#define OAN_1                  (0x40)         /* OAx Inverting input select 01 */
#define OAN_2                  (0x80)         /* OAx Inverting input select 10 */
#define OAN_3                  (0xC0)         /* OAx Inverting input select 11 */

#define OARRIP                 (0x01)         /* OAx Rail-to-Rail Input off */
//#define Reserved          (0x02)    /* */
#define OAFC0                  (0x04)         /* OAx Function control 0 */
#define OAFC1                  (0x08)         /* OAx Function control 1 */
#define OAFC2                  (0x10)         /* OAx Function control 2 */
#define OAFBR0                 (0x20)         /* OAx Feedback resistor select 0 */
#define OAFBR1                 (0x40)         /* OAx Feedback resistor select 1 */
#define OAFBR2                 (0x80)         /* OAx Feedback resistor select 2 */

#define OAFC_0                 (0x00)         /* OAx Function: Gen. Purpose */
#define OAFC_1                 (0x04)         /* OAx Function: Unity gain buffer */
#define OAFC_2                 (0x08)         /* OAx Function: Reserved */
#define OAFC_3                 (0x0C)         /* OAx Function: Comparator */
#define OAFC_4                 (0x10)         /* OAx Function: Non-Inverting PGA */
#define OAFC_5                 (0x14)         /* OAx Function: Reserved */
#define OAFC_6                 (0x18)         /* OAx Function: Inverting PGA */
#define OAFC_7                 (0x1C)         /* OAx Function: Differential PGA */
#define OAFBR_0                (0x00)         /* OAx Feedback resistor: Tap 0 */
#define OAFBR_1                (0x20)         /* OAx Feedback resistor: Tap 1 */
#define OAFBR_2                (0x40)         /* OAx Feedback resistor: Tap 2 */
#define OAFBR_3                (0x60)         /* OAx Feedback resistor: Tap 3 */
#define OAFBR_4                (0x80)         /* OAx Feedback resistor: Tap 4 */
#define OAFBR_5                (0xA0)         /* OAx Feedback resistor: Tap 5 */
#define OAFBR_6                (0xC0)         /* OAx Feedback resistor: Tap 6 */
#define OAFBR_7                (0xE0)         /* OAx Feedback resistor: Tap 7 */

/************************************************************
* DIGITAL I/O Port1/2
************************************************************/
#define __MSP430_HAS_PORT1__                  /* Definition to show that Module is available */
#define __MSP430_HAS_PORT2__                  /* Definition to show that Module is available */

#define __MSP430_HAS_P1SEL__                  /* Define for DriverLib */
#define __MSP430_HAS_P2SEL__                  /* Define for DriverLib */

SFR_8BIT(P1IN);                               /* Port 1 Input */
SFR_8BIT(P1OUT);                              /* Port 1 Output */
SFR_8BIT(P1DIR);                              /* Port 1 Direction */
SFR_8BIT(P1IFG);                              /* Port 1 Interrupt Flag */
SFR_8BIT(P1IES);                              /* Port 1 Interrupt Edge Select */
SFR_8BIT(P1IE);                               /* Port 1 Interrupt Enable */
SFR_8BIT(P1SEL);                              /* Port 1 Selection */

SFR_8BIT(P2IN);                               /* Port 2 Input */
SFR_8BIT(P2OUT);                              /* Port 2 Output */
SFR_8BIT(P2DIR);                              /* Port 2 Direction */
SFR_8BIT(P2IFG);                              /* Port 2 Interrupt Flag */
SFR_8BIT(P2IES);                              /* Port 2 Interrupt Edge Select */
SFR_8BIT(P2IE);                               /* Port 2 Interrupt Enable */
SFR_8BIT(P2SEL);                              /* Port 2 Selection */

/************************************************************
* DIGITAL I/O Port3/4
************************************************************/
#define __MSP430_HAS_PORT3__                  /* Definition to show that Module is available */
#define __MSP430_HAS_PORT4__                  /* Definition to show that Module is available */

#define __MSP430_HAS_P3SEL__                  /* Define for DriverLib */
#define __MSP430_HAS_P4SEL__                  /* Define for DriverLib */

SFR_8BIT(P3IN);                               /* Port 3 Input */
SFR_8BIT(P3OUT);                              /* Port 3 Output */
SFR_8BIT(P3DIR);                              /* Port 3 Direction */
SFR_8BIT(P3SEL);                              /* Port 3 Selection */

SFR_8BIT(P4IN);                               /* Port 4 Input */
SFR_8BIT(P4OUT);                              /* Port 4 Output */
SFR_8BIT(P4DIR);                              /* Port 4 Direction */
SFR_8BIT(P4SEL);                              /* Port 4 Selection */

/************************************************************
* DIGITAL I/O Port5/6
************************************************************/
#define __MSP430_HAS_PORT5__                  /* Definition to show that Module is available */
#define __MSP430_HAS_PORT6__                  /* Definition to show that Module is available */

#define __MSP430_HAS_P5SEL__                  /* Define for DriverLib */
#define __MSP430_HAS_P6SEL__                  /* Define for DriverLib */

SFR_8BIT(P5IN);                               /* Port 5 Input */
SFR_8BIT(P5OUT);                              /* Port 5 Output */
SFR_8BIT(P5DIR);                              /* Port 5 Direction */
SFR_8BIT(P5SEL);                              /* Port 5 Selection */

SFR_8BIT(P6IN);                               /* Port 6 Input */
SFR_8BIT(P6OUT);                              /* Port 6 Output */
SFR_8BIT(P6DIR);                              /* Port 6 Direction */
SFR_8BIT(P6SEL);                              /* Port 6 Selection */

/************************************************************
* DIGITAL I/O Port7/8
************************************************************/
#define __MSP430_HAS_PORT7__                  /* Definition to show that Module is available */
#define __MSP430_HAS_PORT8__                  /* Definition to show that Module is available */
#define __MSP430_HAS_PORTA__                  /* Definition to show that Module is available */

#define __MSP430_HAS_P7SEL__                  /* Define for DriverLib */
#define __MSP430_HAS_P8SEL__                  /* Define for DriverLib */
#define __MSP430_HAS_PASEL__                  /* Define for DriverLib */

SFR_8BIT(P7IN);                               /* Port 7 Input */
SFR_8BIT(P7OUT);                              /* Port 7 Output */
SFR_8BIT(P7DIR);                              /* Port 7 Direction */
SFR_8BIT(P7SEL);                              /* Port 7 Selection */

SFR_8BIT(P8IN);                               /* Port 8 Input */
SFR_8BIT(P8OUT);                              /* Port 8 Output */
SFR_8BIT(P8DIR);                              /* Port 8 Direction */
SFR_8BIT(P8SEL);                              /* Port 8 Selection */

SFR_16BIT(PAIN);                              /* Port A Input */
SFR_16BIT(PAOUT);                             /* Port A Output */
SFR_16BIT(PADIR);                             /* Port A Direction */
SFR_16BIT(PASEL);                             /* Port A Selection */

/************************************************************
* DIGITAL I/O Port9/10
************************************************************/
#define __MSP430_HAS_PORT9__                  /* Definition to show that Module is available */
#define __MSP430_HAS_PORT10__                 /* Definition to show that Module is available */
#define __MSP430_HAS_PORTB__                  /* Definition to show that Module is available */

#define __MSP430_HAS_P9SEL__                  /* Define for DriverLib */
#define __MSP430_HAS_P10SEL__                 /* Define for DriverLib */
#define __MSP430_HAS_PBSEL__                  /* Define for DriverLib */

SFR_8BIT(P9IN);                               /* Port 9 Input */
SFR_8BIT(P9OUT);                              /* Port 9 Output */
SFR_8BIT(P9DIR);                              /* Port 9 Direction */
SFR_8BIT(P9SEL);                              /* Port 9 Selection */

SFR_8BIT(P10IN);                              /* Port 10 Input */
SFR_8BIT(P10OUT);                             /* Port 10 Output */
SFR_8BIT(P10DIR);                             /* Port 10 Direction */
SFR_8BIT(P10SEL);                             /* Port 10 Selection */

SFR_16BIT(PBIN);                              /* Port B Input */
SFR_16BIT(PBOUT);                             /* Port B Output */
SFR_16BIT(PBDIR);                             /* Port B Direction */
SFR_16BIT(PBSEL);                             /* Port B Selection */

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
* Timer B7
************************************************************/
#define __MSP430_HAS_TB7__                    /* Definition to show that Module is available */

SFR_16BIT(TBIV);                              /* Timer B Interrupt Vector Word */
SFR_16BIT(TBCTL);                             /* Timer B Control */
SFR_16BIT(TBCCTL0);                           /* Timer B Capture/Compare Control 0 */
SFR_16BIT(TBCCTL1);                           /* Timer B Capture/Compare Control 1 */
SFR_16BIT(TBCCTL2);                           /* Timer B Capture/Compare Control 2 */
SFR_16BIT(TBCCTL3);                           /* Timer B Capture/Compare Control 3 */
SFR_16BIT(TBCCTL4);                           /* Timer B Capture/Compare Control 4 */
SFR_16BIT(TBCCTL5);                           /* Timer B Capture/Compare Control 5 */
SFR_16BIT(TBCCTL6);                           /* Timer B Capture/Compare Control 6 */
SFR_16BIT(TBR);                               /* Timer B Counter Register */
SFR_16BIT(TBCCR0);                            /* Timer B Capture/Compare 0 */
SFR_16BIT(TBCCR1);                            /* Timer B Capture/Compare 1 */
SFR_16BIT(TBCCR2);                            /* Timer B Capture/Compare 2 */
SFR_16BIT(TBCCR3);                            /* Timer B Capture/Compare 3 */
SFR_16BIT(TBCCR4);                            /* Timer B Capture/Compare 4 */
SFR_16BIT(TBCCR5);                            /* Timer B Capture/Compare 5 */
SFR_16BIT(TBCCR6);                            /* Timer B Capture/Compare 6 */

/* Alternate register names - 5xx style */
#define TB0IV                  TBIV           /* Timer B Interrupt Vector Word */
#define TB0CTL                 TBCTL          /* Timer B Control */
#define TB0CCTL0               TBCCTL0        /* Timer B Capture/Compare Control 0 */
#define TB0CCTL1               TBCCTL1        /* Timer B Capture/Compare Control 1 */
#define TB0CCTL2               TBCCTL2        /* Timer B Capture/Compare Control 2 */
#define TB0CCTL3               TBCCTL3        /* Timer B Capture/Compare Control 3 */
#define TB0CCTL4               TBCCTL4        /* Timer B Capture/Compare Control 4 */
#define TB0CCTL5               TBCCTL5        /* Timer B Capture/Compare Control 5 */
#define TB0CCTL6               TBCCTL6        /* Timer B Capture/Compare Control 6 */
#define TB0R                   TBR            /* Timer B Counter Register */
#define TB0CCR0                TBCCR0         /* Timer B Capture/Compare 0 */
#define TB0CCR1                TBCCR1         /* Timer B Capture/Compare 1 */
#define TB0CCR2                TBCCR2         /* Timer B Capture/Compare 2 */
#define TB0CCR3                TBCCR3         /* Timer B Capture/Compare 3 */
#define TB0CCR4                TBCCR4         /* Timer B Capture/Compare 4 */
#define TB0CCR5                TBCCR5         /* Timer B Capture/Compare 5 */
#define TB0CCR6                TBCCR6         /* Timer B Capture/Compare 6 */
#define TB0IV_                 TBIV_          /* Timer B Interrupt Vector Word */
#define TB0CTL_                TBCTL_         /* Timer B Control */
#define TB0CCTL0_              TBCCTL0_       /* Timer B Capture/Compare Control 0 */
#define TB0CCTL1_              TBCCTL1_       /* Timer B Capture/Compare Control 1 */
#define TB0CCTL2_              TBCCTL2_       /* Timer B Capture/Compare Control 2 */
#define TB0CCTL3_              TBCCTL3_       /* Timer B Capture/Compare Control 3 */
#define TB0CCTL4_              TBCCTL4_       /* Timer B Capture/Compare Control 4 */
#define TB0CCTL5_              TBCCTL5_       /* Timer B Capture/Compare Control 5 */
#define TB0CCTL6_              TBCCTL6_       /* Timer B Capture/Compare Control 6 */
#define TB0R_                  TBR_           /* Timer B Counter Register */
#define TB0CCR0_               TBCCR0_        /* Timer B Capture/Compare 0 */
#define TB0CCR1_               TBCCR1_        /* Timer B Capture/Compare 1 */
#define TB0CCR2_               TBCCR2_        /* Timer B Capture/Compare 2 */
#define TB0CCR3_               TBCCR3_        /* Timer B Capture/Compare 3 */
#define TB0CCR4_               TBCCR4_        /* Timer B Capture/Compare 4 */
#define TB0CCR5_               TBCCR5_        /* Timer B Capture/Compare 5 */
#define TB0CCR6_               TBCCR6_        /* Timer B Capture/Compare 6 */
#define TIMER0_B1_VECTOR       TIMERB1_VECTOR /* Int. Vector: Timer B CC1-6, TB */
#define TIMER0_B0_VECTOR       TIMERB0_VECTOR /* Int. Vector: Timer B CC0 */

#define TBCLGRP1               (0x4000)       /* Timer B Compare latch load group 1 */
#define TBCLGRP0               (0x2000)       /* Timer B Compare latch load group 0 */
#define CNTL1                  (0x1000)       /* Counter lenght 1 */
#define CNTL0                  (0x0800)       /* Counter lenght 0 */
#define TBSSEL1                (0x0200)       /* Clock source 1 */
#define TBSSEL0                (0x0100)       /* Clock source 0 */
#define TBCLR                  (0x0004)       /* Timer B counter clear */
#define TBIE                   (0x0002)       /* Timer B interrupt enable */
#define TBIFG                  (0x0001)       /* Timer B interrupt flag */

#define SHR1                   (0x4000)       /* Timer B Compare latch load group 1 */
#define SHR0                   (0x2000)       /* Timer B Compare latch load group 0 */

#define TBSSEL_0               (0*0x0100u)    /* Clock Source: TBCLK */
#define TBSSEL_1               (1*0x0100u)    /* Clock Source: ACLK  */
#define TBSSEL_2               (2*0x0100u)    /* Clock Source: SMCLK */
#define TBSSEL_3               (3*0x0100u)    /* Clock Source: INCLK */
#define CNTL_0                 (0*0x0800u)    /* Counter lenght: 16 bit */
#define CNTL_1                 (1*0x0800u)    /* Counter lenght: 12 bit */
#define CNTL_2                 (2*0x0800u)    /* Counter lenght: 10 bit */
#define CNTL_3                 (3*0x0800u)    /* Counter lenght:  8 bit */
#define SHR_0                  (0*0x2000u)    /* Timer B Group: 0 - individually */
#define SHR_1                  (1*0x2000u)    /* Timer B Group: 1 - 3 groups (1-2, 3-4, 5-6) */
#define SHR_2                  (2*0x2000u)    /* Timer B Group: 2 - 2 groups (1-3, 4-6)*/
#define SHR_3                  (3*0x2000u)    /* Timer B Group: 3 - 1 group (all) */
#define TBCLGRP_0              (0*0x2000u)    /* Timer B Group: 0 - individually */
#define TBCLGRP_1              (1*0x2000u)    /* Timer B Group: 1 - 3 groups (1-2, 3-4, 5-6) */
#define TBCLGRP_2              (2*0x2000u)    /* Timer B Group: 2 - 2 groups (1-3, 4-6)*/
#define TBCLGRP_3              (3*0x2000u)    /* Timer B Group: 3 - 1 group (all) */

/* Additional Timer B Control Register bits are defined in Timer A */
#define CLLD1                  (0x0400)       /* Compare latch load source 1 */
#define CLLD0                  (0x0200)       /* Compare latch load source 0 */

#define SLSHR1                 (0x0400)       /* Compare latch load source 1 */
#define SLSHR0                 (0x0200)       /* Compare latch load source 0 */

#define SLSHR_0                (0*0x0200u)    /* Compare latch load sourec : 0 - immediate */
#define SLSHR_1                (1*0x0200u)    /* Compare latch load sourec : 1 - TBR counts to 0 */
#define SLSHR_2                (2*0x0200u)    /* Compare latch load sourec : 2 - up/down */
#define SLSHR_3                (3*0x0200u)    /* Compare latch load sourec : 3 - TBR counts to TBCTL0 */

#define CLLD_0                 (0*0x0200u)    /* Compare latch load sourec : 0 - immediate */
#define CLLD_1                 (1*0x0200u)    /* Compare latch load sourec : 1 - TBR counts to 0 */
#define CLLD_2                 (2*0x0200u)    /* Compare latch load sourec : 2 - up/down */
#define CLLD_3                 (3*0x0200u)    /* Compare latch load sourec : 3 - TBR counts to TBCTL0 */

/* TB7IV Definitions */
#define TBIV_NONE              (0x0000)       /* No Interrupt pending */
#define TBIV_TBCCR1            (0x0002)       /* TBCCR1_CCIFG */
#define TBIV_TBCCR2            (0x0004)       /* TBCCR2_CCIFG */
#define TBIV_TBCCR3            (0x0006)       /* TBCCR3_CCIFG */
#define TBIV_TBCCR4            (0x0008)       /* TBCCR4_CCIFG */
#define TBIV_TBCCR5            (0x000A)       /* TBCCR3_CCIFG */
#define TBIV_TBCCR6            (0x000C)       /* TBCCR4_CCIFG */
#define TBIV_TBIFG             (0x000E)       /* TBIFG */

/* Alternate register names - 5xx style */
#define TB0IV_NONE             (0x0000)       /* No Interrupt pending */
#define TB0IV_TBCCR1           (0x0002)       /* TB0CCR1_CCIFG */
#define TB0IV_TBCCR2           (0x0004)       /* TB0CCR2_CCIFG */
#define TB0IV_TBCCR3           (0x0006)       /* TB0CCR3_CCIFG */
#define TB0IV_TBCCR4           (0x0008)       /* TB0CCR4_CCIFG */
#define TB0IV_TBCCR5           (0x000A)       /* TB0CCR3_CCIFG */
#define TB0IV_TBCCR6           (0x000C)       /* TB0CCR4_CCIFG */
#define TB0IV_TBIFG            (0x000E)       /* TB0IFG */

/************************************************************
* USCI
************************************************************/
#define __MSP430_HAS_USCI__                   /* Definition to show that Module is available */

SFR_8BIT(UCA0CTL0);                           /* USCI A0 Control Register 0 */
SFR_8BIT(UCA0CTL1);                           /* USCI A0 Control Register 1 */
SFR_8BIT(UCA0BR0);                            /* USCI A0 Baud Rate 0 */
SFR_8BIT(UCA0BR1);                            /* USCI A0 Baud Rate 1 */
SFR_8BIT(UCA0MCTL);                           /* USCI A0 Modulation Control */
SFR_8BIT(UCA0STAT);                           /* USCI A0 Status Register */
SFR_8BIT(UCA0RXBUF);                          /* USCI A0 Receive Buffer */
SFR_8BIT(UCA0TXBUF);                          /* USCI A0 Transmit Buffer */
SFR_8BIT(UCA0ABCTL);                          /* USCI A0 LIN Control */
SFR_8BIT(UCA0IRTCTL);                         /* USCI A0 IrDA Transmit Control */
SFR_8BIT(UCA0IRRCTL);                         /* USCI A0 IrDA Receive Control */



SFR_8BIT(UCB0CTL0);                           /* USCI B0 Control Register 0 */
SFR_8BIT(UCB0CTL1);                           /* USCI B0 Control Register 1 */
SFR_8BIT(UCB0BR0);                            /* USCI B0 Baud Rate 0 */
SFR_8BIT(UCB0BR1);                            /* USCI B0 Baud Rate 1 */
SFR_8BIT(UCB0I2CIE);                          /* USCI B0 I2C Interrupt Enable Register */
SFR_8BIT(UCB0STAT);                           /* USCI B0 Status Register */
SFR_8BIT(UCB0RXBUF);                          /* USCI B0 Receive Buffer */
SFR_8BIT(UCB0TXBUF);                          /* USCI B0 Transmit Buffer */
SFR_16BIT(UCB0I2COA);                         /* USCI B0 I2C Own Address */
SFR_16BIT(UCB0I2CSA);                         /* USCI B0 I2C Slave Address */

// UART-Mode Bits
#define UCPEN                  (0x80)         /* Async. Mode: Parity enable */
#define UCPAR                  (0x40)         /* Async. Mode: Parity     0:odd / 1:even */
#define UCMSB                  (0x20)         /* Async. Mode: MSB first  0:LSB / 1:MSB */
#define UC7BIT                 (0x10)         /* Async. Mode: Data Bits  0:8-bits / 1:7-bits */
#define UCSPB                  (0x08)         /* Async. Mode: Stop Bits  0:one / 1: two */
#define UCMODE1                (0x04)         /* Async. Mode: USCI Mode 1 */
#define UCMODE0                (0x02)         /* Async. Mode: USCI Mode 0 */
#define UCSYNC                 (0x01)         /* Sync-Mode  0:UART-Mode / 1:SPI-Mode */

// SPI-Mode Bits
#define UCCKPH                 (0x80)         /* Sync. Mode: Clock Phase */
#define UCCKPL                 (0x40)         /* Sync. Mode: Clock Polarity */
#define UCMST                  (0x08)         /* Sync. Mode: Master Select */

// I2C-Mode Bits
#define UCA10                  (0x80)         /* 10-bit Address Mode */
#define UCSLA10                (0x40)         /* 10-bit Slave Address Mode */
#define UCMM                   (0x20)         /* Multi-Master Environment */
//#define res               (0x10)    /* reserved */
#define UCMODE_0               (0x00)         /* Sync. Mode: USCI Mode: 0 */
#define UCMODE_1               (0x02)         /* Sync. Mode: USCI Mode: 1 */
#define UCMODE_2               (0x04)         /* Sync. Mode: USCI Mode: 2 */
#define UCMODE_3               (0x06)         /* Sync. Mode: USCI Mode: 3 */

// UART-Mode Bits
#define UCSSEL1                (0x80)         /* USCI 0 Clock Source Select 1 */
#define UCSSEL0                (0x40)         /* USCI 0 Clock Source Select 0 */
#define UCRXEIE                (0x20)         /* RX Error interrupt enable */
#define UCBRKIE                (0x10)         /* Break interrupt enable */
#define UCDORM                 (0x08)         /* Dormant (Sleep) Mode */
#define UCTXADDR               (0x04)         /* Send next Data as Address */
#define UCTXBRK                (0x02)         /* Send next Data as Break */
#define UCSWRST                (0x01)         /* USCI Software Reset */

// SPI-Mode Bits
//#define res               (0x20)    /* reserved */
//#define res               (0x10)    /* reserved */
//#define res               (0x08)    /* reserved */
//#define res               (0x04)    /* reserved */
//#define res               (0x02)    /* reserved */

// I2C-Mode Bits
//#define res               (0x20)    /* reserved */
#define UCTR                   (0x10)         /* Transmit/Receive Select/Flag */
#define UCTXNACK               (0x08)         /* Transmit NACK */
#define UCTXSTP                (0x04)         /* Transmit STOP */
#define UCTXSTT                (0x02)         /* Transmit START */
#define UCSSEL_0               (0x00)         /* USCI 0 Clock Source: 0 */
#define UCSSEL_1               (0x40)         /* USCI 0 Clock Source: 1 */
#define UCSSEL_2               (0x80)         /* USCI 0 Clock Source: 2 */
#define UCSSEL_3               (0xC0)         /* USCI 0 Clock Source: 3 */

#define UCBRF3                 (0x80)         /* USCI First Stage Modulation Select 3 */
#define UCBRF2                 (0x40)         /* USCI First Stage Modulation Select 2 */
#define UCBRF1                 (0x20)         /* USCI First Stage Modulation Select 1 */
#define UCBRF0                 (0x10)         /* USCI First Stage Modulation Select 0 */
#define UCBRS2                 (0x08)         /* USCI Second Stage Modulation Select 2 */
#define UCBRS1                 (0x04)         /* USCI Second Stage Modulation Select 1 */
#define UCBRS0                 (0x02)         /* USCI Second Stage Modulation Select 0 */
#define UCOS16                 (0x01)         /* USCI 16-times Oversampling enable */

#define UCBRF_0                (0x00)         /* USCI First Stage Modulation: 0 */
#define UCBRF_1                (0x10)         /* USCI First Stage Modulation: 1 */
#define UCBRF_2                (0x20)         /* USCI First Stage Modulation: 2 */
#define UCBRF_3                (0x30)         /* USCI First Stage Modulation: 3 */
#define UCBRF_4                (0x40)         /* USCI First Stage Modulation: 4 */
#define UCBRF_5                (0x50)         /* USCI First Stage Modulation: 5 */
#define UCBRF_6                (0x60)         /* USCI First Stage Modulation: 6 */
#define UCBRF_7                (0x70)         /* USCI First Stage Modulation: 7 */
#define UCBRF_8                (0x80)         /* USCI First Stage Modulation: 8 */
#define UCBRF_9                (0x90)         /* USCI First Stage Modulation: 9 */
#define UCBRF_10               (0xA0)         /* USCI First Stage Modulation: A */
#define UCBRF_11               (0xB0)         /* USCI First Stage Modulation: B */
#define UCBRF_12               (0xC0)         /* USCI First Stage Modulation: C */
#define UCBRF_13               (0xD0)         /* USCI First Stage Modulation: D */
#define UCBRF_14               (0xE0)         /* USCI First Stage Modulation: E */
#define UCBRF_15               (0xF0)         /* USCI First Stage Modulation: F */

#define UCBRS_0                (0x00)         /* USCI Second Stage Modulation: 0 */
#define UCBRS_1                (0x02)         /* USCI Second Stage Modulation: 1 */
#define UCBRS_2                (0x04)         /* USCI Second Stage Modulation: 2 */
#define UCBRS_3                (0x06)         /* USCI Second Stage Modulation: 3 */
#define UCBRS_4                (0x08)         /* USCI Second Stage Modulation: 4 */
#define UCBRS_5                (0x0A)         /* USCI Second Stage Modulation: 5 */
#define UCBRS_6                (0x0C)         /* USCI Second Stage Modulation: 6 */
#define UCBRS_7                (0x0E)         /* USCI Second Stage Modulation: 7 */

#define UCLISTEN               (0x80)         /* USCI Listen mode */
#define UCFE                   (0x40)         /* USCI Frame Error Flag */
#define UCOE                   (0x20)         /* USCI Overrun Error Flag */
#define UCPE                   (0x10)         /* USCI Parity Error Flag */
#define UCBRK                  (0x08)         /* USCI Break received */
#define UCRXERR                (0x04)         /* USCI RX Error Flag */
#define UCADDR                 (0x02)         /* USCI Address received Flag */
#define UCBUSY                 (0x01)         /* USCI Busy Flag */
#define UCIDLE                 (0x02)         /* USCI Idle line detected Flag */

//#define res               (0x80)    /* reserved */
//#define res               (0x40)    /* reserved */
//#define res               (0x20)    /* reserved */
//#define res               (0x10)    /* reserved */
#define UCNACKIE               (0x08)         /* NACK Condition interrupt enable */
#define UCSTPIE                (0x04)         /* STOP Condition interrupt enable */
#define UCSTTIE                (0x02)         /* START Condition interrupt enable */
#define UCALIE                 (0x01)         /* Arbitration Lost interrupt enable */

#define UCSCLLOW               (0x40)         /* SCL low */
#define UCGC                   (0x20)         /* General Call address received Flag */
#define UCBBUSY                (0x10)         /* Bus Busy Flag */
#define UCNACKIFG              (0x08)         /* NAK Condition interrupt Flag */
#define UCSTPIFG               (0x04)         /* STOP Condition interrupt Flag */
#define UCSTTIFG               (0x02)         /* START Condition interrupt Flag */
#define UCALIFG                (0x01)         /* Arbitration Lost interrupt Flag */

#define UCIRTXPL5              (0x80)         /* IRDA Transmit Pulse Length 5 */
#define UCIRTXPL4              (0x40)         /* IRDA Transmit Pulse Length 4 */
#define UCIRTXPL3              (0x20)         /* IRDA Transmit Pulse Length 3 */
#define UCIRTXPL2              (0x10)         /* IRDA Transmit Pulse Length 2 */
#define UCIRTXPL1              (0x08)         /* IRDA Transmit Pulse Length 1 */
#define UCIRTXPL0              (0x04)         /* IRDA Transmit Pulse Length 0 */
#define UCIRTXCLK              (0x02)         /* IRDA Transmit Pulse Clock Select */
#define UCIREN                 (0x01)         /* IRDA Encoder/Decoder enable */

#define UCIRRXFL5              (0x80)         /* IRDA Receive Filter Length 5 */
#define UCIRRXFL4              (0x40)         /* IRDA Receive Filter Length 4 */
#define UCIRRXFL3              (0x20)         /* IRDA Receive Filter Length 3 */
#define UCIRRXFL2              (0x10)         /* IRDA Receive Filter Length 2 */
#define UCIRRXFL1              (0x08)         /* IRDA Receive Filter Length 1 */
#define UCIRRXFL0              (0x04)         /* IRDA Receive Filter Length 0 */
#define UCIRRXPL               (0x02)         /* IRDA Receive Input Polarity */
#define UCIRRXFE               (0x01)         /* IRDA Receive Filter enable */

//#define res               (0x80)    /* reserved */
//#define res               (0x40)    /* reserved */
#define UCDELIM1               (0x20)         /* Break Sync Delimiter 1 */
#define UCDELIM0               (0x10)         /* Break Sync Delimiter 0 */
#define UCSTOE                 (0x08)         /* Sync-Field Timeout error */
#define UCBTOE                 (0x04)         /* Break Timeout error */
//#define res               (0x02)    /* reserved */
#define UCABDEN                (0x01)         /* Auto Baud Rate detect enable */

#define UCGCEN                 (0x8000)       /* I2C General Call enable */
#define UCOA9                  (0x0200)       /* I2C Own Address 9 */
#define UCOA8                  (0x0100)       /* I2C Own Address 8 */
#define UCOA7                  (0x0080)       /* I2C Own Address 7 */
#define UCOA6                  (0x0040)       /* I2C Own Address 6 */
#define UCOA5                  (0x0020)       /* I2C Own Address 5 */
#define UCOA4                  (0x0010)       /* I2C Own Address 4 */
#define UCOA3                  (0x0008)       /* I2C Own Address 3 */
#define UCOA2                  (0x0004)       /* I2C Own Address 2 */
#define UCOA1                  (0x0002)       /* I2C Own Address 1 */
#define UCOA0                  (0x0001)       /* I2C Own Address 0 */

#define UCSA9                  (0x0200)       /* I2C Slave Address 9 */
#define UCSA8                  (0x0100)       /* I2C Slave Address 8 */
#define UCSA7                  (0x0080)       /* I2C Slave Address 7 */
#define UCSA6                  (0x0040)       /* I2C Slave Address 6 */
#define UCSA5                  (0x0020)       /* I2C Slave Address 5 */
#define UCSA4                  (0x0010)       /* I2C Slave Address 4 */
#define UCSA3                  (0x0008)       /* I2C Slave Address 3 */
#define UCSA2                  (0x0004)       /* I2C Slave Address 2 */
#define UCSA1                  (0x0002)       /* I2C Slave Address 1 */
#define UCSA0                  (0x0001)       /* I2C Slave Address 0 */

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
* USART 1
************************************************************/
#define __MSP430_HAS_UART1__                  /* Definition to show that Module is available */

SFR_8BIT(U1CTL);                              /* USART 1 Control */
SFR_8BIT(U1TCTL);                             /* USART 1 Transmit Control */
SFR_8BIT(U1RCTL);                             /* USART 1 Receive Control */
SFR_8BIT(U1MCTL);                             /* USART 1 Modulation Control */
SFR_8BIT(U1BR0);                              /* USART 1 Baud Rate 0 */
SFR_8BIT(U1BR1);                              /* USART 1 Baud Rate 1 */
SFR_8BIT(U1RXBUF);                            /* USART 1 Receive Buffer */
SFR_8BIT(U1TXBUF);                            /* USART 1 Transmit Buffer */

/* Alternate register names */

#define UCTL1                  U1CTL          /* USART 1 Control */
#define UTCTL1                 U1TCTL         /* USART 1 Transmit Control */
#define URCTL1                 U1RCTL         /* USART 1 Receive Control */
#define UMCTL1                 U1MCTL         /* USART 1 Modulation Control */
#define UBR01                  U1BR0          /* USART 1 Baud Rate 0 */
#define UBR11                  U1BR1          /* USART 1 Baud Rate 1 */
#define RXBUF1                 U1RXBUF        /* USART 1 Receive Buffer */
#define TXBUF1                 U1TXBUF        /* USART 1 Transmit Buffer */
#define UCTL1_                 U1CTL_         /* USART 1 Control */
#define UTCTL1_                U1TCTL_        /* USART 1 Transmit Control */
#define URCTL1_                U1RCTL_        /* USART 1 Receive Control */
#define UMCTL1_                U1MCTL_        /* USART 1 Modulation Control */
#define UBR01_                 U1BR0_         /* USART 1 Baud Rate 0 */
#define UBR11_                 U1BR1_         /* USART 1 Baud Rate 1 */
#define RXBUF1_                U1RXBUF_       /* USART 1 Receive Buffer */
#define TXBUF1_                U1TXBUF_       /* USART 1 Transmit Buffer */
#define UCTL_1                 U1CTL          /* USART 1 Control */
#define UTCTL_1                U1TCTL         /* USART 1 Transmit Control */
#define URCTL_1                U1RCTL         /* USART 1 Receive Control */
#define UMCTL_1                U1MCTL         /* USART 1 Modulation Control */
#define UBR0_1                 U1BR0          /* USART 1 Baud Rate 0 */
#define UBR1_1                 U1BR1          /* USART 1 Baud Rate 1 */
#define RXBUF_1                U1RXBUF        /* USART 1 Receive Buffer */
#define TXBUF_1                U1TXBUF        /* USART 1 Transmit Buffer */
#define UCTL_1_                U1CTL_         /* USART 1 Control */
#define UTCTL_1_               U1TCTL_        /* USART 1 Transmit Control */
#define URCTL_1_               U1RCTL_        /* USART 1 Receive Control */
#define UMCTL_1_               U1MCTL_        /* USART 1 Modulation Control */
#define UBR0_1_                U1BR0_         /* USART 1 Baud Rate 0 */
#define UBR1_1_                U1BR1_         /* USART 1 Baud Rate 1 */
#define RXBUF_1_               U1RXBUF_       /* USART 1 Receive Buffer */
#define TXBUF_1_               U1TXBUF_       /* USART 1 Transmit Buffer */

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
* Interrupt Vectors (offset from 0xFFC0)
************************************************************/

#pragma diag_suppress 1107
#define VECTOR_NAME(name)             name##_ptr
#define EMIT_PRAGMA(x)                _Pragma(#x)
#define CREATE_VECTOR(name)           void * const VECTOR_NAME(name) = (void *)(long)&name
#define PLACE_VECTOR(vector,section)  EMIT_PRAGMA(DATA_SECTION(vector,section))
#define PLACE_INTERRUPT(func)         EMIT_PRAGMA(CODE_SECTION(func,".text:_isr"))
#define ISR_VECTOR(func,offset)       CREATE_VECTOR(func); \
                                      PLACE_VECTOR(VECTOR_NAME(func), offset) \
                                      PLACE_INTERRUPT(func)


#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define DAC12_VECTOR            ".int14"                     /* 0xFFDC DAC 12 */
#else
#define DAC12_VECTOR            (14 * 1u)                    /* 0xFFDC DAC 12 */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define DMA_VECTOR              ".int15"                     /* 0xFFDE DMA */
#else
#define DMA_VECTOR              (15 * 1u)                    /* 0xFFDE DMA */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define BASICTIMER_VECTOR       ".int16"                     /* 0xFFE0 Basic Timer / RTC */
#else
#define BASICTIMER_VECTOR       (16 * 1u)                    /* 0xFFE0 Basic Timer / RTC */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define PORT2_VECTOR            ".int17"                     /* 0xFFE2 Port 2 */
#else
#define PORT2_VECTOR            (17 * 1u)                    /* 0xFFE2 Port 2 */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define USART1TX_VECTOR         ".int18"                     /* 0xFFE4 USART 1 Transmit */
#else
#define USART1TX_VECTOR         (18 * 1u)                    /* 0xFFE4 USART 1 Transmit */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define USART1RX_VECTOR         ".int19"                     /* 0xFFE6 USART 1 Receive */
#else
#define USART1RX_VECTOR         (19 * 1u)                    /* 0xFFE6 USART 1 Receive */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define PORT1_VECTOR            ".int20"                     /* 0xFFE8 Port 1 */
#else
#define PORT1_VECTOR            (20 * 1u)                    /* 0xFFE8 Port 1 */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define TIMERA1_VECTOR          ".int21"                     /* 0xFFEA Timer A CC1-2, TA */
#else
#define TIMERA1_VECTOR          (21 * 1u)                    /* 0xFFEA Timer A CC1-2, TA */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define TIMERA0_VECTOR          ".int22"                     /* 0xFFEC Timer A CC0 */
#else
#define TIMERA0_VECTOR          (22 * 1u)                    /* 0xFFEC Timer A CC0 */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define ADC12_VECTOR            ".int23"                     /* 0xFFEE ADC */
#else
#define ADC12_VECTOR            (23 * 1u)                    /* 0xFFEE ADC */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define USCIAB0TX_VECTOR        ".int24"                     /* 0xFFF0 USCI A0/B0 Transmit */
#else
#define USCIAB0TX_VECTOR        (24 * 1u)                    /* 0xFFF0 USCI A0/B0 Transmit */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define USCIAB0RX_VECTOR        ".int25"                     /* 0xFFF2 USCI A0/B0 Receive */
#else
#define USCIAB0RX_VECTOR        (25 * 1u)                    /* 0xFFF2 USCI A0/B0 Receive */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define WDT_VECTOR              ".int26"                     /* 0xFFF4 Watchdog Timer */
#else
#define WDT_VECTOR              (26 * 1u)                    /* 0xFFF4 Watchdog Timer */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define COMPARATORA_VECTOR      ".int27"                     /* 0xFFF6 Comparator A */
#else
#define COMPARATORA_VECTOR      (27 * 1u)                    /* 0xFFF6 Comparator A */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define TIMERB1_VECTOR          ".int28"                     /* 0xFFF8 Timer B CC1-2, TB */
#else
#define TIMERB1_VECTOR          (28 * 1u)                    /* 0xFFF8 Timer B CC1-2, TB */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define TIMERB0_VECTOR          ".int29"                     /* 0xFFFA Timer B CC0 */
#else
#define TIMERB0_VECTOR          (29 * 1u)                    /* 0xFFFA Timer B CC0 */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define NMI_VECTOR              ".int30"                     /* 0xFFFC Non-maskable */
#else
#define NMI_VECTOR              (30 * 1u)                    /* 0xFFFC Non-maskable */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define RESET_VECTOR            ".reset"                     /* 0xFFFE Reset [Highest Priority] */
#else
#define RESET_VECTOR            (31 * 1u)                    /* 0xFFFE Reset [Highest Priority] */
#endif

/************************************************************
* End of Modules
************************************************************/

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* #ifndef __msp430xG46x */

