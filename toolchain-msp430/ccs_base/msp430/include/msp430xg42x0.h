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
* MSP430xG42x0 devices.
*
* Texas Instruments, Version 1.3
*
*
* Rev. 1.0, Inital Setup
* Rev. 1.1, Added some definitons for LCD_A Module
* Rev. 1.2, Removed definitions for BTRESET
* Rev. 1.3, added definitions for Interrupt Vectors xxIV
*
********************************************************************/

#ifndef __msp430xG42x0
#define __msp430xG42x0

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
#define WDTIE                  (0x01)
#define OFIE                   (0x02)
#define NMIIE                  (0x10)
#define ACCVIE                 (0x20)

SFR_8BIT(IFG1);                               /* Interrupt Flag 1 */
#define WDTIFG                 (0x01)         /* Watchdog Interrupt Flag */
#define OFIFG                  (0x02)         /* Osc. Fault Interrupt Flag */
#define PORIFG                 (0x04)         /* Power On Interrupt Flag */
#define RSTIFG                 (0x08)         /* Reset Interrupt Flag */
#define NMIIFG                 (0x10)         /* NMI Interrupt Flag */

SFR_8BIT(IE2);                                /* Interrupt Enable 2 */
#define BTIE                   (0x80)

SFR_8BIT(IFG2);                               /* Interrupt Flag 2 */
#define BTIFG                  (0x80)

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
* BASIC TIMER
************************************************************/
#define __MSP430_HAS_BT__                     /* Definition to show that Module is available */

SFR_8BIT(BTCTL);                              /* Basic Timer Control */
/* The bit names have been prefixed with "BT" */
#define BTIP0                  (0x01)
#define BTIP1                  (0x02)
#define BTIP2                  (0x04)
#define BTFRFQ0                (0x08)
#define BTFRFQ1                (0x10)
#define BTDIV                  (0x20)         /* fCLK2 = ACLK:256 */
#define BTHOLD                 (0x40)         /* BT1 is held if this bit is set */
#define BTSSEL                 (0x80)         /* fBT = fMCLK (main clock) */

SFR_8BIT(BTCNT1);                             /* Basic Timer Count 1 */
SFR_8BIT(BTCNT2);                             /* Basic Timer Count 2 */

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
/* Frequency of LCD coded with Bits 3-4 */
#define BT_fLCD_DIV32          (0x00)         /* fLCD = fACLK:32 (default) */
#define BT_fLCD_DIV64          (BTFRFQ0)      /* fLCD = fACLK:64 */
#define BT_fLCD_DIV128         (BTFRFQ1)      /* fLCD = fACLK:128 */
#define BT_fLCD_DIV256      (BTFRFQ1+BTFRFQ0)         /* fLCD = fACLK:256 */
/* LCD frequency values with fBT=fACLK */
#define BT_fLCD_1K             (0x00)         /* fACLK:32 (default) */
#define BT_fLCD_512            (BTFRFQ0)      /* fACLK:64 */
#define BT_fLCD_256            (BTFRFQ1)      /* fACLK:128 */
#define BT_fLCD_128         (BTFRFQ1+BTFRFQ0)         /* fACLK:256 */
/* LCD frequency values with fBT=fMCLK */
#define BT_fLCD_31K            (BTSSEL)       /* fMCLK:32 */
#define BT_fLCD_15_5K       (BTSSEL+BTFRFQ0)          /* fMCLK:64 */
#define BT_fLCD_7_8K        (BTSSEL+BTFRFQ1+BTFRFQ0)  /* fMCLK:256 */
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

/* Reset/Hold coded with Bits 6-7 in BT(1)CTL */
/* this is for BT */
//#define BTRESET_CNT1        (BTRESET)           /* BTCNT1 is reset while BTRESET is set */
//#define BTRESET_CNT1_2      (BTRESET+BTDIV)     /* BTCNT1 .AND. BTCNT2 are reset while ~ is set */
/* this is for BT1 */
#define BTHOLD_CNT1            (BTHOLD)       /* BTCNT1 is held while BTHOLD is set */
#define BTHOLD_CNT1_2          (BTHOLD+BTDIV) /* BT1CNT1 .AND. BT1CNT2 are held while ~ is set */

/* INTERRUPT CONTROL BITS */
/* #define BTIE                0x80 */
/* #define BTIFG               0x80 */

/************************************************************
* SYSTEM CLOCK, FLL+ (x41x)
************************************************************/
#define __MSP430_HAS_FLLPLUS_SMALL__                /* Definition to show that Module is available */

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
#define XT1OF                  (0x04)         /* High Frequency Oscillator Fault Flag */
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

#define FLL_DIV_1              (0x00)         /* FLL+ Divide Px.x/ACLK By 1 */
#define FLL_DIV_2              (0x01)         /* FLL+ Divide Px.x/ACLK By 2 */
#define FLL_DIV_4              (0x02)         /* FLL+ Divide Px.x/ACLK By 4 */
#define FLL_DIV_8              (0x03)         /* FLL+ Divide Px.x/ACLK By 8 */

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

/*************************************************************
* Flash Memory
*************************************************************/
#define __MSP430_HAS_FLASH__                  /* Definition to show that Module is available */

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
#define SD16BUF0               (0x2000)       /* SD16 Channel x High Impedance Input Buffer Select: 0 */
#define SD16BUF1               (0x4000)       /* SD16 Channel x High Impedance Input Buffer Select: 1 */
#define SD16BUFG               (0x8000)       /* SD16 Channel x Buffer Gain 0:Gain=1 / 1:Gain=2 */

#define SD16OSR_1024        (SD16OSR0+SD16XOSR)     /* SD16 Channel x OverSampling Ratio 1024 */
#define SD16OSR_512            (SD16XOSR)     /* SD16 Channel x OverSampling Ratio 512 */
#define SD16OSR_256            (0x0000)       /* SD16 Channel x OverSampling Ratio 256 */
#define SD16OSR_128            (SD16OSR0)     /* SD16 Channel x OverSampling Ratio 128 */
#define SD16OSR_64             (SD16OSR1)     /* SD16 Channel x OverSampling Ratio  64 */
#define SD16OSR_32          (SD16OSR0+SD16OSR1)     /* SD16 Channel x OverSampling Ratio  32 */

#define SD16BUF_0              (0x0000)       /* SD16 High Imp. Input Buffer: Disabled */
#define SD16BUF_1              (SD16BUF0)     /* SD16 High Imp. Input Buffer: Slow */
#define SD16BUF_2              (SD16BUF1)     /* SD16 High Imp. Input Buffer: Meduim */
#define SD16BUF_3           (SD16BUF0+SD16BUF1)     /* SD16 High Imp. Input Buffer: Fast */

/* SD16IV Definitions */
#define SD16IV_NONE            (0x0000)       /* No Interrupt pending */
#define SD16IV_SD16OVIFG       (0x0002)       /* SD16OVIFG */
#define SD16IV_SD16MEM0        (0x0004)       /* SD16MEM0 SD16IFG */

/************************************************************
* DAC12
************************************************************/
#define __MSP430_HAS_DAC12_1__                /* Definition to show that Module is available */

SFR_16BIT(DAC12_0CTL);                        /* DAC12_0 Control */

#define DAC12GRP               (0x0001)       /* DAC12 group (not used) */
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
/************************************************************
* Operational Amplifier
************************************************************/
#define __MSP430_HAS_OA_2__                   /* Definition to show that Module is available */

SFR_8BIT(OA0CTL0);                            /* OA0 Control register 0 */
SFR_8BIT(OA0CTL1);                            /* OA0 Control register 1 */
SFR_8BIT(OA1CTL0);                            /* OA1 Control register 0 */
SFR_8BIT(OA1CTL1);                            /* OA1 Control register 1 */
SFR_8BIT(SWCTL);                              /* OA  Analog Switches Control Register */

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

#define OACAL                  (0x02)         /* OAx Offset Calibration */
#define OAFC0                  (0x04)         /* OAx Function control 0 */
#define OAFC1                  (0x08)         /* OAx Function control 1 */
#define OAFC2                  (0x10)         /* OAx Function control 2 */

#define OAFC_0                 (0x00)         /* OAx Function: Gen. Purpose */
#define OAFC_1                 (0x04)         /* OAx Function: Unity gain buffer */
#define OAFC_2                 (0x08)         /* OAx Function: Reserved */
#define OAFC_3                 (0x0C)         /* OAx Function: Reserved */
#define OAFC_4                 (0x10)         /* OAx Function: Reserved */
#define OAFC_5                 (0x14)         /* OAx Function: Reserved */
#define OAFC_6                 (0x18)         /* OAx Function: Inverting PGA */
#define OAFC_7                 (0x1C)         /* OAx Function: Reserved */

#define SWCTL0                 (0x01)         /* OA  Analog Switch Control 0 */
#define SWCTL1                 (0x02)         /* OA  Analog Switch Control 1 */
#define SWCTL2                 (0x04)         /* OA  Analog Switch Control 2 */
#define SWCTL3                 (0x08)         /* OA  Analog Switch Control 3 */
#define SWCTL4                 (0x10)         /* OA  Analog Switch Control 4 */
#define SWCTL5                 (0x20)         /* OA  Analog Switch Control 5 */
#define SWCTL6                 (0x40)         /* OA  Analog Switch Control 6 */
#define SWCTL7                 (0x80)         /* OA  Analog Switch Control 7 */

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
#define BASICTIMER_VECTOR       ".int00"                     /* 0xFFE0 Basic Timer */
#else
#define BASICTIMER_VECTOR       (0 * 1u)                     /* 0xFFE0 Basic Timer */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define PORT2_VECTOR            ".int01"                     /* 0xFFE2 Port 2 */
#else
#define PORT2_VECTOR            (1 * 1u)                     /* 0xFFE2 Port 2 */
#endif

#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define DAC12_VECTOR            ".int03"                     /* 0xFFE6 DAC 12 */
#else
#define DAC12_VECTOR            (3 * 1u)                     /* 0xFFE6 DAC 12 */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define PORT1_VECTOR            ".int04"                     /* 0xFFE8 Port 1 */
#else
#define PORT1_VECTOR            (4 * 1u)                     /* 0xFFE8 Port 1 */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define TIMERA1_VECTOR          ".int05"                     /* 0xFFEA Timer A CC1-2, TA */
#else
#define TIMERA1_VECTOR          (5 * 1u)                     /* 0xFFEA Timer A CC1-2, TA */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define TIMERA0_VECTOR          ".int06"                     /* 0xFFEC Timer A CC0 */
#else
#define TIMERA0_VECTOR          (6 * 1u)                     /* 0xFFEC Timer A CC0 */
#endif

#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define WDT_VECTOR              ".int10"                     /* 0xFFF4 Watchdog Timer */
#else
#define WDT_VECTOR              (10 * 1u)                    /* 0xFFF4 Watchdog Timer */
#endif

#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define SD16_VECTOR             ".int12"                     /* 0xFFF8 Sigma Delta ADC */
#else
#define SD16_VECTOR             (12 * 1u)                    /* 0xFFF8 Sigma Delta ADC */
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

#endif /* #ifndef __msp430xG42x0 */

