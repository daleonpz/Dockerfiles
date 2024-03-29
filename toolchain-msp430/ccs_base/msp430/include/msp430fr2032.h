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
* MSP430FR2032 devices.
*
* Texas Instruments, Version 1.1
*
* Rev. 1.0, Setup
* Rev. 1.1, replaced UCSSEL__ACLK with UCSSEL__MODCLK
*
********************************************************************/

#ifndef __MSP430FR2032
#define __MSP430FR2032

#define __MSP430_HAS_MSP430XV2_CPU__                /* Definition to show that it has MSP430XV2 CPU */
#define __MSP430FR2XX_4XX_FAMILY__

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
* ADC
************************************************************/
#define __MSP430_HAS_ADC__                    /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_ADC__ 0x0700
#define ADC_BASE               __MSP430_BASEADDRESS_ADC__
#define __MSP430_HAS_ADC_CHANNELS_10__

SFR_16BIT(ADCCTL0);                           /* ADC Control 0 */
SFR_8BIT(ADCCTL0_L);                          /* ADC Control 0 */
SFR_8BIT(ADCCTL0_H);                          /* ADC Control 0 */
SFR_16BIT(ADCCTL1);                           /* ADC Control 1 */
SFR_8BIT(ADCCTL1_L);                          /* ADC Control 1 */
SFR_8BIT(ADCCTL1_H);                          /* ADC Control 1 */
SFR_16BIT(ADCCTL2);                           /* ADC Control 2 */
SFR_8BIT(ADCCTL2_L);                          /* ADC Control 2 */
SFR_8BIT(ADCCTL2_H);                          /* ADC Control 2 */
SFR_16BIT(ADCLO);                             /* ADC Window Comparator High Threshold */
SFR_8BIT(ADCLO_L);                            /* ADC Window Comparator High Threshold */
SFR_8BIT(ADCLO_H);                            /* ADC Window Comparator High Threshold */
SFR_16BIT(ADCHI);                             /* ADC Window Comparator High Threshold */
SFR_8BIT(ADCHI_L);                            /* ADC Window Comparator High Threshold */
SFR_8BIT(ADCHI_H);                            /* ADC Window Comparator High Threshold */
SFR_16BIT(ADCMCTL0);                          /* ADC Memory Control 0 */
SFR_8BIT(ADCMCTL0_L);                         /* ADC Memory Control 0 */
SFR_8BIT(ADCMCTL0_H);                         /* ADC Memory Control 0 */
SFR_16BIT(ADCMEM0);                           /* ADC Conversion Memory 0 */
SFR_8BIT(ADCMEM0_L);                          /* ADC Conversion Memory 0 */
SFR_8BIT(ADCMEM0_H);                          /* ADC Conversion Memory 0 */
SFR_16BIT(ADCIE);                             /* ADC Interrupt Enable */
SFR_8BIT(ADCIE_L);                            /* ADC Interrupt Enable */
SFR_8BIT(ADCIE_H);                            /* ADC Interrupt Enable */
SFR_16BIT(ADCIFG);                            /* ADC Interrupt Flag */
SFR_8BIT(ADCIFG_L);                           /* ADC Interrupt Flag */
SFR_8BIT(ADCIFG_H);                           /* ADC Interrupt Flag */
SFR_16BIT(ADCIV);                             /* ADC Interrupt Vector Word */
SFR_8BIT(ADCIV_L);                            /* ADC Interrupt Vector Word */
SFR_8BIT(ADCIV_H);                            /* ADC Interrupt Vector Word */

/* ADCCTL0 Control Bits */
#define ADCSC                  (0x0001)       /* ADC Start Conversion */
#define ADCENC                 (0x0002)       /* ADC Enable Conversion */
#define ADCON                  (0x0010)       /* ADC On/enable */
#define ADCMSC                 (0x0080)       /* ADC Multiple SampleConversion */
#define ADCSHT0                (0x0100)       /* ADC Sample Hold Select Bit: 0 */
#define ADCSHT1                (0x0200)       /* ADC Sample Hold Select Bit: 1 */
#define ADCSHT2                (0x0400)       /* ADC Sample Hold Select Bit: 2 */
#define ADCSHT3                (0x0800)       /* ADC Sample Hold Select Bit: 3 */

/* ADCCTL0 Control Bits */
#define ADCSC_L                (0x0001)       /* ADC Start Conversion */
#define ADCENC_L               (0x0002)       /* ADC Enable Conversion */
#define ADCON_L                (0x0010)       /* ADC On/enable */
#define ADCMSC_L               (0x0080)       /* ADC Multiple SampleConversion */

/* ADCCTL0 Control Bits */
#define ADCSHT0_H              (0x0001)       /* ADC Sample Hold Select Bit: 0 */
#define ADCSHT1_H              (0x0002)       /* ADC Sample Hold Select Bit: 1 */
#define ADCSHT2_H              (0x0004)       /* ADC Sample Hold Select Bit: 2 */
#define ADCSHT3_H              (0x0008)       /* ADC Sample Hold Select Bit: 3 */

#define ADCSHT_0               (0*0x100u)     /* ADC Sample Hold Select 0 */
#define ADCSHT_1               (1*0x100u)     /* ADC Sample Hold Select 1 */
#define ADCSHT_2               (2*0x100u)     /* ADC Sample Hold Select 2 */
#define ADCSHT_3               (3*0x100u)     /* ADC Sample Hold Select 3 */
#define ADCSHT_4               (4*0x100u)     /* ADC Sample Hold Select 4 */
#define ADCSHT_5               (5*0x100u)     /* ADC Sample Hold Select 5 */
#define ADCSHT_6               (6*0x100u)     /* ADC Sample Hold Select 6 */
#define ADCSHT_7               (7*0x100u)     /* ADC Sample Hold Select 7 */
#define ADCSHT_8               (8*0x100u)     /* ADC Sample Hold Select 8 */
#define ADCSHT_9               (9*0x100u)     /* ADC Sample Hold Select 9 */
#define ADCSHT_10              (10*0x100u)    /* ADC Sample Hold Select 10 */
#define ADCSHT_11              (11*0x100u)    /* ADC Sample Hold Select 11 */
#define ADCSHT_12              (12*0x100u)    /* ADC Sample Hold Select 12 */
#define ADCSHT_13              (13*0x100u)    /* ADC Sample Hold Select 13 */
#define ADCSHT_14              (14*0x100u)    /* ADC Sample Hold Select 14 */
#define ADCSHT_15              (15*0x100u)    /* ADC Sample Hold Select 15 */

/* ADCCTL1 Control Bits */
#define ADCBUSY                (0x0001)       /* ADC Busy */
#define ADCCONSEQ0             (0x0002)       /* ADC Conversion Sequence Select 0 */
#define ADCCONSEQ1             (0x0004)       /* ADC Conversion Sequence Select 1 */
#define ADCSSEL0               (0x0008)       /* ADC Clock Source Select 0 */
#define ADCSSEL1               (0x0010)       /* ADC Clock Source Select 1 */
#define ADCDIV0                (0x0020)       /* ADC Clock Divider Select 0 */
#define ADCDIV1                (0x0040)       /* ADC Clock Divider Select 1 */
#define ADCDIV2                (0x0080)       /* ADC Clock Divider Select 2 */
#define ADCISSH                (0x0100)       /* ADC Invert Sample Hold Signal */
#define ADCSHP                 (0x0200)       /* ADC Sample/Hold Pulse Mode */
#define ADCSHS0                (0x0400)       /* ADC Sample/Hold Source 0 */
#define ADCSHS1                (0x0800)       /* ADC Sample/Hold Source 1 */

/* ADCCTL1 Control Bits */
#define ADCBUSY_L              (0x0001)       /* ADC Busy */
#define ADCCONSEQ0_L           (0x0002)       /* ADC Conversion Sequence Select 0 */
#define ADCCONSEQ1_L           (0x0004)       /* ADC Conversion Sequence Select 1 */
#define ADCSSEL0_L             (0x0008)       /* ADC Clock Source Select 0 */
#define ADCSSEL1_L             (0x0010)       /* ADC Clock Source Select 1 */
#define ADCDIV0_L              (0x0020)       /* ADC Clock Divider Select 0 */
#define ADCDIV1_L              (0x0040)       /* ADC Clock Divider Select 1 */
#define ADCDIV2_L              (0x0080)       /* ADC Clock Divider Select 2 */

/* ADCCTL1 Control Bits */
#define ADCISSH_H              (0x0001)       /* ADC Invert Sample Hold Signal */
#define ADCSHP_H               (0x0002)       /* ADC Sample/Hold Pulse Mode */
#define ADCSHS0_H              (0x0004)       /* ADC Sample/Hold Source 0 */
#define ADCSHS1_H              (0x0008)       /* ADC Sample/Hold Source 1 */

#define ADCCONSEQ              (0x0006)       /* ADC Conversion Sequence Select */
#define ADCCONSEQ_0            (0*2u)         /* ADC Conversion Sequence Select: 0 */
#define ADCCONSEQ_1            (1*2u)         /* ADC Conversion Sequence Select: 1 */
#define ADCCONSEQ_2            (2*2u)         /* ADC Conversion Sequence Select: 2 */
#define ADCCONSEQ_3            (3*2u)         /* ADC Conversion Sequence Select: 3 */

#define ADCSSEL_0              (0*8u)         /* ADC Clock Source Select: 0 */
#define ADCSSEL_1              (1*8u)         /* ADC Clock Source Select: 1 */
#define ADCSSEL_2              (2*8u)         /* ADC Clock Source Select: 2 */
#define ADCSSEL_3              (3*8u)         /* ADC Clock Source Select: 3 */

#define ADCDIV_0               (0*0x20u)      /* ADC Clock Divider Select: 0 */
#define ADCDIV_1               (1*0x20u)      /* ADC Clock Divider Select: 1 */
#define ADCDIV_2               (2*0x20u)      /* ADC Clock Divider Select: 2 */
#define ADCDIV_3               (3*0x20u)      /* ADC Clock Divider Select: 3 */
#define ADCDIV_4               (4*0x20u)      /* ADC Clock Divider Select: 4 */
#define ADCDIV_5               (5*0x20u)      /* ADC Clock Divider Select: 5 */
#define ADCDIV_6               (6*0x20u)      /* ADC Clock Divider Select: 6 */
#define ADCDIV_7               (7*0x20u)      /* ADC Clock Divider Select: 7 */

#define ADCSHS_0               (0*0x400u)     /* ADC Sample/Hold Source: 0 */
#define ADCSHS_1               (1*0x400u)     /* ADC Sample/Hold Source: 1 */
#define ADCSHS_2               (2*0x400u)     /* ADC Sample/Hold Source: 2 */
#define ADCSHS_3               (3*0x400u)     /* ADC Sample/Hold Source: 3 */

/* ADCCTL2 Control Bits */
#define ADCSR                  (0x0004)       /* ADC Sampling Rate */
#define ADCDF                  (0x0008)       /* ADC Data Format */
#define ADCRES0                (0x0010)       /* ADC Resolution */
#define ADCRES1                (0x0020)       /* ADC Resolution */
#define ADCPDIV0               (0x0100)       /* ADC predivider Bit: 0 */
#define ADCPDIV1               (0x0200)       /* ADC predivider Bit: 1 */

/* ADCCTL2 Control Bits */
#define ADCSR_L                (0x0004)       /* ADC Sampling Rate */
#define ADCDF_L                (0x0008)       /* ADC Data Format */
#define ADCRES0_L              (0x0010)       /* ADC Resolution */
#define ADCRES1_L              (0x0020)       /* ADC Resolution */

/* ADCCTL2 Control Bits */
#define ADCPDIV0_H             (0x0001)       /* ADC predivider Bit: 0 */
#define ADCPDIV1_H             (0x0002)       /* ADC predivider Bit: 1 */

#define ADCRES_0               (0x0000)       /* 8 bit */
#define ADCRES_1               (0x0010)       /* 10 bit */
#define ADCRES_2               (0x0020)       /* Reserved */
#define ADCRES_3               (0x0030)       /* Reserved */

#define ADCRES                 (0x0010)       /* Legacy define */
#define ADCRES_L               (0x0010)       /* Legacy define */

#define ADCPDIV_0              (0x0000)       /* ADC predivider /1 */
#define ADCPDIV_1              (0x0100)       /* ADC predivider /2 */
#define ADCPDIV_2              (0x0200)       /* ADC predivider /64 */
#define ADCPDIV_3              (0x0300)       /* ADC predivider reserved */

#define ADCPDIV__1             (0x0000)       /* ADC predivider /1 */
#define ADCPDIV__4             (0x0100)       /* ADC predivider /2 */
#define ADCPDIV__64            (0x0200)       /* ADC predivider /64 */

/* ADCMCTL0 Control Bits */
#define ADCINCH0               (0x0001)       /* ADC Input Channel Select Bit 0 */
#define ADCINCH1               (0x0002)       /* ADC Input Channel Select Bit 1 */
#define ADCINCH2               (0x0004)       /* ADC Input Channel Select Bit 2 */
#define ADCINCH3               (0x0008)       /* ADC Input Channel Select Bit 3 */
#define ADCSREF0               (0x0010)       /* ADC Select Reference Bit 0 */
#define ADCSREF1               (0x0020)       /* ADC Select Reference Bit 1 */
#define ADCSREF2               (0x0040)       /* ADC Select Reference Bit 2 */

/* ADCMCTL0 Control Bits */
#define ADCINCH0_L             (0x0001)       /* ADC Input Channel Select Bit 0 */
#define ADCINCH1_L             (0x0002)       /* ADC Input Channel Select Bit 1 */
#define ADCINCH2_L             (0x0004)       /* ADC Input Channel Select Bit 2 */
#define ADCINCH3_L             (0x0008)       /* ADC Input Channel Select Bit 3 */
#define ADCSREF0_L             (0x0010)       /* ADC Select Reference Bit 0 */
#define ADCSREF1_L             (0x0020)       /* ADC Select Reference Bit 1 */
#define ADCSREF2_L             (0x0040)       /* ADC Select Reference Bit 2 */

#define ADCINCH_0              (0)            /* ADC Input Channel 0 */
#define ADCINCH_1              (1)            /* ADC Input Channel 1 */
#define ADCINCH_2              (2)            /* ADC Input Channel 2 */
#define ADCINCH_3              (3)            /* ADC Input Channel 3 */
#define ADCINCH_4              (4)            /* ADC Input Channel 4 */
#define ADCINCH_5              (5)            /* ADC Input Channel 5 */
#define ADCINCH_6              (6)            /* ADC Input Channel 6 */
#define ADCINCH_7              (7)            /* ADC Input Channel 7 */
#define ADCINCH_8              (8)            /* ADC Input Channel 8 */
#define ADCINCH_9              (9)            /* ADC Input Channel 9 */
#define ADCINCH_10             (10)           /* ADC Input Channel 10 */
#define ADCINCH_11             (11)           /* ADC Input Channel 11 */
#define ADCINCH_12             (12)           /* ADC Input Channel 12 */
#define ADCINCH_13             (13)           /* ADC Input Channel 13 */
#define ADCINCH_14             (14)           /* ADC Input Channel 14 */
#define ADCINCH_15             (15)           /* ADC Input Channel 15 */

#define ADCSREF_0              (0*0x10u)      /* ADC Select Reference 0 */
#define ADCSREF_1              (1*0x10u)      /* ADC Select Reference 1 */
#define ADCSREF_2              (2*0x10u)      /* ADC Select Reference 2 */
#define ADCSREF_3              (3*0x10u)      /* ADC Select Reference 3 */
#define ADCSREF_4              (4*0x10u)      /* ADC Select Reference 4 */
#define ADCSREF_5              (5*0x10u)      /* ADC Select Reference 5 */
#define ADCSREF_6              (6*0x10u)      /* ADC Select Reference 6 */
#define ADCSREF_7              (7*0x10u)      /* ADC Select Reference 7 */

/* ADCIE Interrupt Enable Bits */
#define ADCIE0                 (0x0001)       /* ADC Interrupt enable */
#define ADCINIE                (0x0002)       /* ADC Interrupt enable for the inside of window of the Window comparator */
#define ADCLOIE                (0x0004)       /* ADC Interrupt enable for lower threshold of the Window comparator */
#define ADCHIIE                (0x0008)       /* ADC Interrupt enable for upper threshold of the Window comparator */
#define ADCOVIE                (0x0010)       /* ADC ADCMEM overflow Interrupt enable */
#define ADCTOVIE               (0x0020)       /* ADC conversion-time-overflow Interrupt enable */

/* ADCIE Interrupt Enable Bits */
#define ADCIE0_L               (0x0001)       /* ADC Interrupt enable */
#define ADCINIE_L              (0x0002)       /* ADC Interrupt enable for the inside of window of the Window comparator */
#define ADCLOIE_L              (0x0004)       /* ADC Interrupt enable for lower threshold of the Window comparator */
#define ADCHIIE_L              (0x0008)       /* ADC Interrupt enable for upper threshold of the Window comparator */
#define ADCOVIE_L              (0x0010)       /* ADC ADCMEM overflow Interrupt enable */
#define ADCTOVIE_L             (0x0020)       /* ADC conversion-time-overflow Interrupt enable */

/* ADCIFG Interrupt Flag Bits */
#define ADCIFG0                (0x0001)       /* ADC Interrupt Flag */
#define ADCINIFG               (0x0002)       /* ADC Interrupt Flag for the inside of window of the Window comparator */
#define ADCLOIFG               (0x0004)       /* ADC Interrupt Flag for lower threshold of the Window comparator */
#define ADCHIIFG               (0x0008)       /* ADC Interrupt Flag for upper threshold of the Window comparator */
#define ADCOVIFG               (0x0010)       /* ADC ADCMEM overflow Interrupt Flag */
#define ADCTOVIFG              (0x0020)       /* ADC conversion-time-overflow Interrupt Flag */

/* ADCIFG Interrupt Flag Bits */
#define ADCIFG0_L              (0x0001)       /* ADC Interrupt Flag */
#define ADCINIFG_L             (0x0002)       /* ADC Interrupt Flag for the inside of window of the Window comparator */
#define ADCLOIFG_L             (0x0004)       /* ADC Interrupt Flag for lower threshold of the Window comparator */
#define ADCHIIFG_L             (0x0008)       /* ADC Interrupt Flag for upper threshold of the Window comparator */
#define ADCOVIFG_L             (0x0010)       /* ADC ADCMEM overflow Interrupt Flag */
#define ADCTOVIFG_L            (0x0020)       /* ADC conversion-time-overflow Interrupt Flag */

/* ADCIV Definitions */
#define ADCIV_NONE             (0x0000)       /* No Interrupt pending */
#define ADCIV_ADCOVIFG         (0x0002)       /* ADCOVIFG */
#define ADCIV_ADCTOVIFG        (0x0004)       /* ADCTOVIFG */
#define ADCIV_ADCHIIFG         (0x0006)       /* ADCHIIFG */
#define ADCIV_ADCLOIFG         (0x0008)       /* ADCLOIFG */
#define ADCIV_ADCINIFG         (0x000A)       /* ADCINIFG */
#define ADCIV_ADCIFG           (0x000C)       /* ADCIFG */

/*************************************************************
* Backup Memory Module
*************************************************************/
#define __MSP430_HAS_BKMEM__                  /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_BKMEM__ 0x0660
#define BKMEM_BASE             __MSP430_BASEADDRESS_BKMEM__

#define __MSP430_HAS_BACKUP_RAM__                /* Legacy module name */
#define BAK_RAM_BASE           BKMEM_BASE     /* Legacy module name */

SFR_16BIT(BAKMEM0);                           /* Battery Backup Memory 0 */
SFR_8BIT(BAKMEM0_L);                          /* Battery Backup Memory 0 */
SFR_8BIT(BAKMEM0_H);                          /* Battery Backup Memory 0 */
SFR_16BIT(BAKMEM1);                           /* Battery Backup Memory 1 */
SFR_8BIT(BAKMEM1_L);                          /* Battery Backup Memory 1 */
SFR_8BIT(BAKMEM1_H);                          /* Battery Backup Memory 1 */
SFR_16BIT(BAKMEM2);                           /* Battery Backup Memory 2 */
SFR_8BIT(BAKMEM2_L);                          /* Battery Backup Memory 2 */
SFR_8BIT(BAKMEM2_H);                          /* Battery Backup Memory 2 */
SFR_16BIT(BAKMEM3);                           /* Battery Backup Memory 3 */
SFR_8BIT(BAKMEM3_L);                          /* Battery Backup Memory 3 */
SFR_8BIT(BAKMEM3_H);                          /* Battery Backup Memory 3 */
SFR_16BIT(BAKMEM4);                           /* Battery Backup Memory 4 */
SFR_8BIT(BAKMEM4_L);                          /* Battery Backup Memory 4 */
SFR_8BIT(BAKMEM4_H);                          /* Battery Backup Memory 4 */
SFR_16BIT(BAKMEM5);                           /* Battery Backup Memory 5 */
SFR_8BIT(BAKMEM5_L);                          /* Battery Backup Memory 5 */
SFR_8BIT(BAKMEM5_H);                          /* Battery Backup Memory 5 */
SFR_16BIT(BAKMEM6);                           /* Battery Backup Memory 6 */
SFR_8BIT(BAKMEM6_L);                          /* Battery Backup Memory 6 */
SFR_8BIT(BAKMEM6_H);                          /* Battery Backup Memory 6 */
SFR_16BIT(BAKMEM7);                           /* Battery Backup Memory 7 */
SFR_8BIT(BAKMEM7_L);                          /* Battery Backup Memory 7 */
SFR_8BIT(BAKMEM7_H);                          /* Battery Backup Memory 7 */
SFR_16BIT(BAKMEM8);                           /* Battery Backup Memory 8 */
SFR_8BIT(BAKMEM8_L);                          /* Battery Backup Memory 8 */
SFR_8BIT(BAKMEM8_H);                          /* Battery Backup Memory 8 */
SFR_16BIT(BAKMEM9);                           /* Battery Backup Memory 9 */
SFR_8BIT(BAKMEM9_L);                          /* Battery Backup Memory 9 */
SFR_8BIT(BAKMEM9_H);                          /* Battery Backup Memory 9 */
SFR_16BIT(BAKMEM10);                          /* Battery Backup Memory 10 */
SFR_8BIT(BAKMEM10_L);                         /* Battery Backup Memory 10 */
SFR_8BIT(BAKMEM10_H);                         /* Battery Backup Memory 10 */
SFR_16BIT(BAKMEM11);                          /* Battery Backup Memory 11 */
SFR_8BIT(BAKMEM11_L);                         /* Battery Backup Memory 11 */
SFR_8BIT(BAKMEM11_H);                         /* Battery Backup Memory 11 */
SFR_16BIT(BAKMEM12);                          /* Battery Backup Memory 12 */
SFR_8BIT(BAKMEM12_L);                         /* Battery Backup Memory 12 */
SFR_8BIT(BAKMEM12_H);                         /* Battery Backup Memory 12 */
SFR_16BIT(BAKMEM13);                          /* Battery Backup Memory 13 */
SFR_8BIT(BAKMEM13_L);                         /* Battery Backup Memory 13 */
SFR_8BIT(BAKMEM13_H);                         /* Battery Backup Memory 13 */
SFR_16BIT(BAKMEM14);                          /* Battery Backup Memory 14 */
SFR_8BIT(BAKMEM14_L);                         /* Battery Backup Memory 14 */
SFR_8BIT(BAKMEM14_H);                         /* Battery Backup Memory 14 */
SFR_16BIT(BAKMEM15);                          /* Battery Backup Memory 15 */
SFR_8BIT(BAKMEM15_L);                         /* Battery Backup Memory 15 */
SFR_8BIT(BAKMEM15_H);                         /* Battery Backup Memory 15 */

/************************************************************
* Capacitive_Touch_IO 0
************************************************************/
#define __MSP430_HAS_CAP_TOUCH_IO_0__                /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_CAP_TOUCH_IO_0__ 0x02E0
#define CAP_TOUCH_0_BASE       __MSP430_BASEADDRESS_CAP_TOUCH_IO_0__

SFR_16BIT(CAPTIO0CTL);                        /* Capacitive_Touch_IO 0 control register */
SFR_8BIT(CAPTIO0CTL_L);                       /* Capacitive_Touch_IO 0 control register */
SFR_8BIT(CAPTIO0CTL_H);                       /* Capacitive_Touch_IO 0 control register */

#define  CAPSIO0CTL            CAPTIO0CTL     /* legacy define */

/* CAPTIOxCTL Control Bits */
#define CAPTIOPISEL0           (0x0002)       /* CapTouchIO Pin Select Bit: 0 */
#define CAPTIOPISEL1           (0x0004)       /* CapTouchIO Pin Select Bit: 1 */
#define CAPTIOPISEL2           (0x0008)       /* CapTouchIO Pin Select Bit: 2 */
#define CAPTIOPOSEL0           (0x0010)       /* CapTouchIO Port Select Bit: 0 */
#define CAPTIOPOSEL1           (0x0020)       /* CapTouchIO Port Select Bit: 1 */
#define CAPTIOPOSEL2           (0x0040)       /* CapTouchIO Port Select Bit: 2 */
#define CAPTIOPOSEL3           (0x0080)       /* CapTouchIO Port Select Bit: 3 */
#define CAPTIOEN               (0x0100)       /* CapTouchIO Enable */
#define CAPTIO                 (0x0200)       /* CapTouchIO state */

/* CAPTIOxCTL Control Bits */
#define CAPTIOPISEL0_L         (0x0002)       /* CapTouchIO Pin Select Bit: 0 */
#define CAPTIOPISEL1_L         (0x0004)       /* CapTouchIO Pin Select Bit: 1 */
#define CAPTIOPISEL2_L         (0x0008)       /* CapTouchIO Pin Select Bit: 2 */
#define CAPTIOPOSEL0_L         (0x0010)       /* CapTouchIO Port Select Bit: 0 */
#define CAPTIOPOSEL1_L         (0x0020)       /* CapTouchIO Port Select Bit: 1 */
#define CAPTIOPOSEL2_L         (0x0040)       /* CapTouchIO Port Select Bit: 2 */
#define CAPTIOPOSEL3_L         (0x0080)       /* CapTouchIO Port Select Bit: 3 */

/* CAPTIOxCTL Control Bits */
#define CAPTIOEN_H             (0x0001)       /* CapTouchIO Enable */
#define CAPTIO_H               (0x0002)       /* CapTouchIO state */

/* Legacy defines */
#define CAPSIOPISEL0           (0x0002)       /* CapTouchIO Pin Select Bit: 0 */
#define CAPSIOPISEL1           (0x0004)       /* CapTouchIO Pin Select Bit: 1 */
#define CAPSIOPISEL2           (0x0008)       /* CapTouchIO Pin Select Bit: 2 */
#define CAPSIOPOSEL0           (0x0010)       /* CapTouchIO Port Select Bit: 0 */
#define CAPSIOPOSEL1           (0x0020)       /* CapTouchIO Port Select Bit: 1 */
#define CAPSIOPOSEL2           (0x0040)       /* CapTouchIO Port Select Bit: 2 */
#define CAPSIOPOSEL3           (0x0080)       /* CapTouchIO Port Select Bit: 3 */
#define CAPSIOEN               (0x0100)       /* CapTouchIO Enable */
#define CAPSIO                 (0x0200)       /* CapTouchIO state */

/*************************************************************
* CRC Module
*************************************************************/
#define __MSP430_HAS_CRC__                    /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_CRC__ 0x01C0
#define CRC_BASE               __MSP430_BASEADDRESS_CRC__

SFR_16BIT(CRCDI);                             /* CRC Data In Register */
SFR_8BIT(CRCDI_L);                            /* CRC Data In Register */
SFR_8BIT(CRCDI_H);                            /* CRC Data In Register */
SFR_16BIT(CRCDIRB);                           /* CRC data in reverse byte Register */
SFR_8BIT(CRCDIRB_L);                          /* CRC data in reverse byte Register */
SFR_8BIT(CRCDIRB_H);                          /* CRC data in reverse byte Register */
SFR_16BIT(CRCINIRES);                         /* CRC Initialisation Register and Result Register */
SFR_8BIT(CRCINIRES_L);                        /* CRC Initialisation Register and Result Register */
SFR_8BIT(CRCINIRES_H);                        /* CRC Initialisation Register and Result Register */
SFR_16BIT(CRCRESR);                           /* CRC reverse result Register */
SFR_8BIT(CRCRESR_L);                          /* CRC reverse result Register */
SFR_8BIT(CRCRESR_H);                          /* CRC reverse result Register */

/************************************************************
* CLOCK SYSTEM CONTROL
************************************************************/
#define __MSP430_HAS_CS__                     /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_CS__ 0x0180
#define CS_BASE                __MSP430_BASEADDRESS_CS__

SFR_16BIT(CSCTL0);                            /* CS Control Register 0 */
SFR_8BIT(CSCTL0_L);                           /* CS Control Register 0 */
SFR_8BIT(CSCTL0_H);                           /* CS Control Register 0 */
SFR_16BIT(CSCTL1);                            /* CS Control Register 1 */
SFR_8BIT(CSCTL1_L);                           /* CS Control Register 1 */
SFR_8BIT(CSCTL1_H);                           /* CS Control Register 1 */
SFR_16BIT(CSCTL2);                            /* CS Control Register 2 */
SFR_8BIT(CSCTL2_L);                           /* CS Control Register 2 */
SFR_8BIT(CSCTL2_H);                           /* CS Control Register 2 */
SFR_16BIT(CSCTL3);                            /* CS Control Register 3 */
SFR_8BIT(CSCTL3_L);                           /* CS Control Register 3 */
SFR_8BIT(CSCTL3_H);                           /* CS Control Register 3 */
SFR_16BIT(CSCTL4);                            /* CS Control Register 4 */
SFR_8BIT(CSCTL4_L);                           /* CS Control Register 4 */
SFR_8BIT(CSCTL4_H);                           /* CS Control Register 4 */
SFR_16BIT(CSCTL5);                            /* CS Control Register 5 */
SFR_8BIT(CSCTL5_L);                           /* CS Control Register 5 */
SFR_8BIT(CSCTL5_H);                           /* CS Control Register 5 */
SFR_16BIT(CSCTL6);                            /* CS Control Register 6 */
SFR_8BIT(CSCTL6_L);                           /* CS Control Register 6 */
SFR_8BIT(CSCTL6_H);                           /* CS Control Register 6 */
SFR_16BIT(CSCTL7);                            /* CS Control Register 7 */
SFR_8BIT(CSCTL7_L);                           /* CS Control Register 7 */
SFR_8BIT(CSCTL7_H);                           /* CS Control Register 7 */
SFR_16BIT(CSCTL8);                            /* CS Control Register 8 */
SFR_8BIT(CSCTL8_L);                           /* CS Control Register 8 */
SFR_8BIT(CSCTL8_H);                           /* CS Control Register 8 */

/* CSCTL0 Control Bits */
#define DCO0                   (0x0001)       /* DCO TAP Bit : 0 */
#define DCO1                   (0x0002)       /* DCO TAP Bit : 1 */
#define DCO2                   (0x0004)       /* DCO TAP Bit : 2 */
#define DCO3                   (0x0008)       /* DCO TAP Bit : 3 */
#define DCO4                   (0x0010)       /* DCO TAP Bit : 4 */
#define DCO5                   (0x0020)       /* DCO TAP Bit : 5 */
#define DCO6                   (0x0040)       /* DCO TAP Bit : 6 */
#define DCO7                   (0x0080)       /* DCO TAP Bit : 7 */
#define DCO8                   (0x0100)       /* DCO TAP Bit : 8 */
#define MOD0                   (0x0200)       /* Modulation Bit Counter Bit : 0 */
#define MOD1                   (0x0400)       /* Modulation Bit Counter Bit : 1 */
#define MOD2                   (0x0800)       /* Modulation Bit Counter Bit : 2 */
#define MOD3                   (0x1000)       /* Modulation Bit Counter Bit : 3 */
#define MOD4                   (0x2000)       /* Modulation Bit Counter Bit : 4 */

/* CSCTL0 Control Bits */
#define DCO0_L                 (0x0001)       /* DCO TAP Bit : 0 */
#define DCO1_L                 (0x0002)       /* DCO TAP Bit : 1 */
#define DCO2_L                 (0x0004)       /* DCO TAP Bit : 2 */
#define DCO3_L                 (0x0008)       /* DCO TAP Bit : 3 */
#define DCO4_L                 (0x0010)       /* DCO TAP Bit : 4 */
#define DCO5_L                 (0x0020)       /* DCO TAP Bit : 5 */
#define DCO6_L                 (0x0040)       /* DCO TAP Bit : 6 */
#define DCO7_L                 (0x0080)       /* DCO TAP Bit : 7 */

/* CSCTL0 Control Bits */
#define DCO8_H                 (0x0001)       /* DCO TAP Bit : 8 */
#define MOD0_H                 (0x0002)       /* Modulation Bit Counter Bit : 0 */
#define MOD1_H                 (0x0004)       /* Modulation Bit Counter Bit : 1 */
#define MOD2_H                 (0x0008)       /* Modulation Bit Counter Bit : 2 */
#define MOD3_H                 (0x0010)       /* Modulation Bit Counter Bit : 3 */
#define MOD4_H                 (0x0020)       /* Modulation Bit Counter Bit : 4 */

/* CSCTL1 Control Bits */
#define DISMOD                 (0x0001)       /* Disable Modulation */
#define DCORSEL0               (0x0002)       /* DCO frequency range select Bit: 0 */
#define DCORSEL1               (0x0004)       /* DCO frequency range select Bit: 1 */
#define DCORSEL2               (0x0008)       /* DCO frequency range select Bit: 2 */
#define DCOFTRIM0              (0x0010)       /* DCO frequency trim. Bit: 0 */
#define DCOFTRIM1              (0x0020)       /* DCO frequency trim. Bit: 1 */
#define DCOFTRIM2              (0x0040)       /* DCO frequency trim. Bit: 2 */
#define DCOFTRIMEN             (0x0080)       /* DCO frequency trim enable */

/* CSCTL1 Control Bits */
#define DISMOD_L               (0x0001)       /* Disable Modulation */
#define DCORSEL0_L             (0x0002)       /* DCO frequency range select Bit: 0 */
#define DCORSEL1_L             (0x0004)       /* DCO frequency range select Bit: 1 */
#define DCORSEL2_L             (0x0008)       /* DCO frequency range select Bit: 2 */
#define DCOFTRIM0_L            (0x0010)       /* DCO frequency trim. Bit: 0 */
#define DCOFTRIM1_L            (0x0020)       /* DCO frequency trim. Bit: 1 */
#define DCOFTRIM2_L            (0x0040)       /* DCO frequency trim. Bit: 2 */
#define DCOFTRIMEN_L           (0x0080)       /* DCO frequency trim enable */

#define DCORSEL_0              (0x0000)       /* DCO frequency range select: 0 */
#define DCORSEL_1              (0x0002)       /* DCO frequency range select: 1 */
#define DCORSEL_2              (0x0004)       /* DCO frequency range select: 2 */
#define DCORSEL_3              (0x0006)       /* DCO frequency range select: 3 */
#define DCORSEL_4              (0x0008)       /* DCO frequency range select: 4 */
#define DCORSEL_5              (0x000A)       /* DCO frequency range select: 5 */
#define DCORSEL_6              (0x000C)       /* DCO frequency range select: 6 */
#define DCORSEL_7              (0x000E)       /* DCO frequency range select: 7 */

#define DCOFTRIM_0             (0x0000)       /* DCO frequency trim: 0 */
#define DCOFTRIM_1             (0x0010)       /* DCO frequency trim: 1 */
#define DCOFTRIM_2             (0x0020)       /* DCO frequency trim: 2 */
#define DCOFTRIM_3             (0x0030)       /* DCO frequency trim: 3 */
#define DCOFTRIM_4             (0x0040)       /* DCO frequency trim: 4 */
#define DCOFTRIM_5             (0x0050)       /* DCO frequency trim: 5 */
#define DCOFTRIM_6             (0x0060)       /* DCO frequency trim: 6 */
#define DCOFTRIM_7             (0x0070)       /* DCO frequency trim: 7 */

/* CSCTL2 Control Bits */
#define FLLN0                  (0x0001)       /* FLL Multipier Bit : 0 */
#define FLLN1                  (0x0002)       /* FLL Multipier Bit : 1 */
#define FLLN2                  (0x0004)       /* FLL Multipier Bit : 2 */
#define FLLN3                  (0x0008)       /* FLL Multipier Bit : 3 */
#define FLLN4                  (0x0010)       /* FLL Multipier Bit : 4 */
#define FLLN5                  (0x0020)       /* FLL Multipier Bit : 5 */
#define FLLN6                  (0x0040)       /* FLL Multipier Bit : 6 */
#define FLLN7                  (0x0080)       /* FLL Multipier Bit : 7 */
#define FLLN8                  (0x0100)       /* FLL Multipier Bit : 8 */
#define FLLN9                  (0x0200)       /* FLL Multipier Bit : 9 */
#define FLLD0                  (0x1000)       /* Loop Divider Bit : 0 */
#define FLLD1                  (0x2000)       /* Loop Divider Bit : 1 */
#define FLLD2                  (0x4000)       /* Loop Divider Bit : 1 */

/* CSCTL2 Control Bits */
#define FLLN0_L                (0x0001)       /* FLL Multipier Bit : 0 */
#define FLLN1_L                (0x0002)       /* FLL Multipier Bit : 1 */
#define FLLN2_L                (0x0004)       /* FLL Multipier Bit : 2 */
#define FLLN3_L                (0x0008)       /* FLL Multipier Bit : 3 */
#define FLLN4_L                (0x0010)       /* FLL Multipier Bit : 4 */
#define FLLN5_L                (0x0020)       /* FLL Multipier Bit : 5 */
#define FLLN6_L                (0x0040)       /* FLL Multipier Bit : 6 */
#define FLLN7_L                (0x0080)       /* FLL Multipier Bit : 7 */

/* CSCTL2 Control Bits */
#define FLLN8_H                (0x0001)       /* FLL Multipier Bit : 8 */
#define FLLN9_H                (0x0002)       /* FLL Multipier Bit : 9 */
#define FLLD0_H                (0x0010)       /* Loop Divider Bit : 0 */
#define FLLD1_H                (0x0020)       /* Loop Divider Bit : 1 */
#define FLLD2_H                (0x0040)       /* Loop Divider Bit : 1 */

#define FLLD_0                 (0x0000)       /* Multiply Selected Loop Freq. By 1 */
#define FLLD_1                 (0x1000)       /* Multiply Selected Loop Freq. By 2 */
#define FLLD_2                 (0x2000)       /* Multiply Selected Loop Freq. By 4 */
#define FLLD_3                 (0x3000)       /* Multiply Selected Loop Freq. By 8 */
#define FLLD_4                 (0x4000)       /* Multiply Selected Loop Freq. By 16 */
#define FLLD_5                 (0x5000)       /* Multiply Selected Loop Freq. By 32 */
#define FLLD_6                 (0x6000)       /* Reserved */
#define FLLD_7                 (0x7000)       /* Reserved */
#define FLLD__1                (0x0000)       /* Multiply Selected Loop Freq. By 1 */
#define FLLD__2                (0x1000)       /* Multiply Selected Loop Freq. By 2 */
#define FLLD__4                (0x2000)       /* Multiply Selected Loop Freq. By 4 */
#define FLLD__8                (0x3000)       /* Multiply Selected Loop Freq. By 8 */
#define FLLD__16               (0x4000)       /* Multiply Selected Loop Freq. By 16 */
#define FLLD__32               (0x5000)       /* Multiply Selected Loop Freq. By 32 */

/* CSCTL3 Control Bits */
#define FLLREFDIV0             (0x0001)       /* Reference Divider Bit : 0 */
#define FLLREFDIV1             (0x0002)       /* Reference Divider Bit : 1 */
#define FLLREFDIV2             (0x0004)       /* Reference Divider Bit : 2 */
#define SELREF0                (0x0010)       /* FLL Reference Clock Select Bit : 0 */
#define SELREF1                (0x0020)       /* FLL Reference Clock Select Bit : 1 */

/* CSCTL3 Control Bits */
#define FLLREFDIV0_L           (0x0001)       /* Reference Divider Bit : 0 */
#define FLLREFDIV1_L           (0x0002)       /* Reference Divider Bit : 1 */
#define FLLREFDIV2_L           (0x0004)       /* Reference Divider Bit : 2 */
#define SELREF0_L              (0x0010)       /* FLL Reference Clock Select Bit : 0 */
#define SELREF1_L              (0x0020)       /* FLL Reference Clock Select Bit : 1 */

#define FLLREFDIV_0            (0x0000)       /* Reference Divider: f(LFCLK)/1 */
#define FLLREFDIV_1            (0x0001)       /* Reference Divider: f(LFCLK)/2 */
#define FLLREFDIV_2            (0x0002)       /* Reference Divider: f(LFCLK)/4 */
#define FLLREFDIV_3            (0x0003)       /* Reference Divider: f(LFCLK)/8 */
#define FLLREFDIV_4            (0x0004)       /* Reference Divider: f(LFCLK)/12 */
#define FLLREFDIV_5            (0x0005)       /* Reference Divider: f(LFCLK)/16 */
#define FLLREFDIV_6            (0x0006)       /* Reference Divider: f(LFCLK)/16 */
#define FLLREFDIV_7            (0x0007)       /* Reference Divider: f(LFCLK)/16 */
#define FLLREFDIV__1           (0x0000)       /* Reference Divider: f(LFCLK)/1   */
#define FLLREFDIV__32          (0x0001)       /* Reference Divider: f(LFCLK)/32  */
#define FLLREFDIV__64          (0x0002)       /* Reference Divider: f(LFCLK)/64  */
#define FLLREFDIV__128         (0x0003)       /* Reference Divider: f(LFCLK)/128 */
#define FLLREFDIV__256         (0x0004)       /* Reference Divider: f(LFCLK)/256 */
#define FLLREFDIV__512         (0x0005)       /* Reference Divider: f(LFCLK)/512 */
#define SELREF_0               (0x0000)       /* FLL Reference Clock Select 0 */
#define SELREF_1               (0x0010)       /* FLL Reference Clock Select 1 */
#define SELREF_2               (0x0020)       /* FLL Reference Clock Select 2 */
#define SELREF_3               (0x0030)       /* FLL Reference Clock Select 3 */
#define SELREF__XT1CLK         (0x0000)       /* Multiply Selected Loop Freq. By XT1CLK */
#define SELREF__REFOCLK        (0x0010)       /* Multiply Selected Loop Freq. By REFOCLK */

/* CSCTL4 Control Bits */
#define SELMS0                 (0x0001)       /* MCLK and SMCLK Source Select Bit: 0 */
#define SELMS1                 (0x0002)       /* MCLK and SMCLK Source Select Bit: 1 */
#define SELMS2                 (0x0004)       /* MCLK and SMCLK Source Select Bit: 2 */
#define SELA                   (0x0100)       /* ACLK Source Select Bit: 0 */

/* CSCTL4 Control Bits */
#define SELMS0_L               (0x0001)       /* MCLK and SMCLK Source Select Bit: 0 */
#define SELMS1_L               (0x0002)       /* MCLK and SMCLK Source Select Bit: 1 */
#define SELMS2_L               (0x0004)       /* MCLK and SMCLK Source Select Bit: 2 */

/* CSCTL4 Control Bits */
#define SELA_H                 (0x0001)       /* ACLK Source Select Bit: 0 */

#define SELMS_0                (0x0000)       /* MCLK and SMCLK Source Select 0 */
#define SELMS_1                (0x0001)       /* MCLK and SMCLK Source Select 1 */
#define SELMS_2                (0x0002)       /* MCLK and SMCLK Source Select 2 */
#define SELMS_3                (0x0003)       /* MCLK and SMCLK Source Select 3 */
#define SELMS_4                (0x0004)       /* MCLK and SMCLK Source Select 4 */
#define SELMS_5                (0x0005)       /* MCLK and SMCLK Source Select 5 */
#define SELMS_6                (0x0006)       /* MCLK and SMCLK Source Select 6 */
#define SELMS_7                (0x0007)       /* MCLK and SMCLK Source Select 7 */
#define SELMS__DCOCLKDIV       (0x0000)       /* MCLK and SMCLK Source Select DCOCLKDIV */
#define SELMS__REFOCLK         (0x0001)       /* MCLK and SMCLK Source Select REFOCLK */
#define SELMS__XT1CLK          (0x0002)       /* MCLK and SMCLK Source Select XT1CLK */
#define SELMS__VLOCLK          (0x0003)       /* MCLK and SMCLK Source Select VLOCLK */

#define SELA__XT1CLK           (0x0000)       /* ACLK Source Select XT1CLK */
#define SELA__REFOCLK          (0x0100)       /* ACLK Source Select REFOCLK */

/* CSCTL5 Control Bits */
#define DIVM0                  (0x0001)       /* MCLK Divider Bit: 0 */
#define DIVM1                  (0x0002)       /* MCLK Divider Bit: 1 */
#define DIVM2                  (0x0004)       /* MCLK Divider Bit: 2 */
#define DIVS0                  (0x0010)       /* SMCLK Divider Bit: 0 */
#define DIVS1                  (0x0020)       /* SMCLK Divider Bit: 1 */
#define SMCLKOFF               (0x0100)       /* SMCLK off */
#define VLOAUTOOFF             (0x1000)       /* VLO automatic off enable */

/* CSCTL5 Control Bits */
#define DIVM0_L                (0x0001)       /* MCLK Divider Bit: 0 */
#define DIVM1_L                (0x0002)       /* MCLK Divider Bit: 1 */
#define DIVM2_L                (0x0004)       /* MCLK Divider Bit: 2 */
#define DIVS0_L                (0x0010)       /* SMCLK Divider Bit: 0 */
#define DIVS1_L                (0x0020)       /* SMCLK Divider Bit: 1 */

/* CSCTL5 Control Bits */
#define SMCLKOFF_H             (0x0001)       /* SMCLK off */
#define VLOAUTOOFF_H           (0x0010)       /* VLO automatic off enable */

#define DIVM_0                 (0x0000)       /* MCLK Source Divider 0 */
#define DIVM_1                 (0x0001)       /* MCLK Source Divider 1 */
#define DIVM_2                 (0x0002)       /* MCLK Source Divider 2 */
#define DIVM_3                 (0x0003)       /* MCLK Source Divider 3 */
#define DIVM_4                 (0x0004)       /* MCLK Source Divider 4 */
#define DIVM_5                 (0x0005)       /* MCLK Source Divider 5 */
#define DIVM_6                 (0x0006)       /* MCLK Source Divider 6 */
#define DIVM_7                 (0x0007)       /* MCLK Source Divider 7 */
#define DIVM__1                (0x0000)       /* MCLK Source Divider f(MCLK)/1 */
#define DIVM__2                (0x0001)       /* MCLK Source Divider f(MCLK)/2 */
#define DIVM__4                (0x0002)       /* MCLK Source Divider f(MCLK)/4 */
#define DIVM__8                (0x0003)       /* MCLK Source Divider f(MCLK)/8 */
#define DIVM__16               (0x0004)       /* MCLK Source Divider f(MCLK)/16 */
#define DIVM__32               (0x0005)       /* MCLK Source Divider f(MCLK)/32 */
#define DIVM__64               (0x0006)       /* MCLK Source Divider f(MCLK)/64 */
#define DIVM__128              (0x0007)       /* MCLK Source Divider f(MCLK)/128 */

#define DIVS_0                 (0x0000)       /* SMCLK Source Divider 0 */
#define DIVS_1                 (0x0010)       /* SMCLK Source Divider 1 */
#define DIVS_2                 (0x0020)       /* SMCLK Source Divider 2 */
#define DIVS_3                 (0x0030)       /* SMCLK Source Divider 3 */
#define DIVS__1                (0x0000)       /* SMCLK Source Divider f(SMCLK)/1 */
#define DIVS__2                (0x0010)       /* SMCLK Source Divider f(SMCLK)/2 */
#define DIVS__4                (0x0020)       /* SMCLK Source Divider f(SMCLK)/4 */
#define DIVS__8                (0x0030)       /* SMCLK Source Divider f(SMCLK)/8 */

/* CSCTL6 Control Bits */
#define XT1AUTOOFF             (0x0001)       /* XT1 automatic off enable */
#define XT1AGCOFF              (0x0002)       /* XT1 Automatic Gain Control (AGC) disable */
#define XT1BYPASS              (0x0010)       /* XT1 bypass mode : 0: internal 1:sourced from external pin */
#define XTS                    (0x0020)       /* 1: Selects high-freq. oscillator */
#define XT1DRIVE0              (0x0040)       /* XT1 Drive Level mode Bit 0 */
#define XT1DRIVE1              (0x0080)       /* XT1 Drive Level mode Bit 1 */

/* CSCTL6 Control Bits */
#define XT1AUTOOFF_L           (0x0001)       /* XT1 automatic off enable */
#define XT1AGCOFF_L            (0x0002)       /* XT1 Automatic Gain Control (AGC) disable */
#define XT1BYPASS_L            (0x0010)       /* XT1 bypass mode : 0: internal 1:sourced from external pin */
#define XTS_L                  (0x0020)       /* 1: Selects high-freq. oscillator */
#define XT1DRIVE0_L            (0x0040)       /* XT1 Drive Level mode Bit 0 */
#define XT1DRIVE1_L            (0x0080)       /* XT1 Drive Level mode Bit 1 */

#define XT1DRIVE_0             (0x0000)       /* XT1 Drive Level mode: 0 */
#define XT1DRIVE_1             (0x0040)       /* XT1 Drive Level mode: 1 */
#define XT1DRIVE_2             (0x0080)       /* XT1 Drive Level mode: 2 */
#define XT1DRIVE_3             (0x00C0)       /* XT1 Drive Level mode: 3 */

/* CSCTL7 Control Bits */
#define DCOFFG                 (0x0001)       /* DCO fault flag */
#define XT1OFFG                (0x0002)       /* XT1 Low Frequency Oscillator Fault Flag */
#define FLLULIFG               (0x0010)       /* FLL unlock interrupt flag */
#define ENSTFCNT1              (0x0040)       /* Enable start counter for XT1 */
#define FLLUNLOCK0             (0x0100)       /* FLL unlock condition Bit: 0 */
#define FLLUNLOCK1             (0x0200)       /* FLL unlock condition Bit: 1 */
#define FLLUNLOCKHIS0          (0x0400)       /* Unlock history Bit: 0 */
#define FLLUNLOCKHIS1          (0x0800)       /* Unlock history Bit: 1 */
#define FLLULPUC               (0x1000)       /* FLL unlock PUC enable */
#define FLLWARNEN              (0x2000)       /* Warning enable */

/* CSCTL7 Control Bits */
#define DCOFFG_L               (0x0001)       /* DCO fault flag */
#define XT1OFFG_L              (0x0002)       /* XT1 Low Frequency Oscillator Fault Flag */
#define FLLULIFG_L             (0x0010)       /* FLL unlock interrupt flag */
#define ENSTFCNT1_L            (0x0040)       /* Enable start counter for XT1 */

/* CSCTL7 Control Bits */
#define FLLUNLOCK0_H           (0x0001)       /* FLL unlock condition Bit: 0 */
#define FLLUNLOCK1_H           (0x0002)       /* FLL unlock condition Bit: 1 */
#define FLLUNLOCKHIS0_H        (0x0004)       /* Unlock history Bit: 0 */
#define FLLUNLOCKHIS1_H        (0x0008)       /* Unlock history Bit: 1 */
#define FLLULPUC_H             (0x0010)       /* FLL unlock PUC enable */
#define FLLWARNEN_H            (0x0020)       /* Warning enable */

#define FLLUNLOCK_0            (0x0000)       /* FLL unlock condition: 0 */
#define FLLUNLOCK_1            (0x0100)       /* FLL unlock condition: 1 */
#define FLLUNLOCK_2            (0x0200)       /* FLL unlock condition: 2 */
#define FLLUNLOCK_3            (0x0300)       /* FLL unlock condition: 3 */
#define FLLUNLOCKHIS_0         (0x0000)       /* Unlock history: 0 */
#define FLLUNLOCKHIS_1         (0x0400)       /* Unlock history: 1 */
#define FLLUNLOCKHIS_2         (0x0800)       /* Unlock history: 2 */
#define FLLUNLOCKHIS_3         (0x0C00)       /* Unlock history: 3 */

/* CSCTL8 Control Bits */
#define ACLKREQEN              (0x0001)       /* ACLK Clock Request Enable */
#define MCLKREQEN              (0x0002)       /* MCLK Clock Request Enable */
#define SMCLKREQEN             (0x0004)       /* SMCLK Clock Request Enable */
#define MODOSCREQEN            (0x0008)       /* MODOSC Clock Request Enable */

/* CSCTL8 Control Bits */
#define ACLKREQEN_L            (0x0001)       /* ACLK Clock Request Enable */
#define MCLKREQEN_L            (0x0002)       /* MCLK Clock Request Enable */
#define SMCLKREQEN_L           (0x0004)       /* SMCLK Clock Request Enable */
#define MODOSCREQEN_L          (0x0008)       /* MODOSC Clock Request Enable */

#define MODCLKREQEN            (0x0008)       /* Legacy: MODOSC Clock Request Enable */
#define MODCLKREQEN_L          (0x0008)       /* Legacy: MODOSC Clock Request Enable */

/*************************************************************
* FRAM Memory
*************************************************************/
#define __MSP430_HAS_FRAM__                   /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_FRAM__ 0x01A0
#define FRAM_BASE              __MSP430_BASEADDRESS_FRAM__
#define __MSP430_HAS_GC__                     /* Definition to show that Module is available */

SFR_16BIT(FRCTL0);                            /* FRAM Controller Control 0 */
SFR_8BIT(FRCTL0_L);                           /* FRAM Controller Control 0 */
SFR_8BIT(FRCTL0_H);                           /* FRAM Controller Control 0 */
SFR_16BIT(GCCTL0);                            /* General Control 0 */
SFR_8BIT(GCCTL0_L);                           /* General Control 0 */
SFR_8BIT(GCCTL0_H);                           /* General Control 0 */
SFR_16BIT(GCCTL1);                            /* General Control 1 */
SFR_8BIT(GCCTL1_L);                           /* General Control 1 */
SFR_8BIT(GCCTL1_H);                           /* General Control 1 */

#define FRCTLPW                (0xA500)       /* FRAM password for write */
#define FRPW                   (0x9600)       /* FRAM password returned by read */
#define FWPW                   (0xA500)       /* FRAM password for write */
#define FXPW                   (0x3300)       /* for use with XOR instruction */

/* FRCTL0 Control Bits */
//#define RESERVED            (0x0001)  /* RESERVED */
//#define RESERVED            (0x0002)  /* RESERVED */
//#define RESERVED            (0x0004)  /* RESERVED */
#define NWAITS0                (0x0010)       /* FRAM Wait state control Bit: 0 */
#define NWAITS1                (0x0020)       /* FRAM Wait state control Bit: 1 */
#define NWAITS2                (0x0040)       /* FRAM Wait state control Bit: 2 */
//#define RESERVED            (0x0080)  /* RESERVED */

/* FRCTL0 Control Bits */
//#define RESERVED            (0x0001)  /* RESERVED */
//#define RESERVED            (0x0002)  /* RESERVED */
//#define RESERVED            (0x0004)  /* RESERVED */
#define NWAITS0_L              (0x0010)       /* FRAM Wait state control Bit: 0 */
#define NWAITS1_L              (0x0020)       /* FRAM Wait state control Bit: 1 */
#define NWAITS2_L              (0x0040)       /* FRAM Wait state control Bit: 2 */
//#define RESERVED            (0x0080)  /* RESERVED */

#define NWAITS_0               (0x0000)       /* FRAM Wait state control: 0 */
#define NWAITS_1               (0x0010)       /* FRAM Wait state control: 1 */
#define NWAITS_2               (0x0020)       /* FRAM Wait state control: 2 */
#define NWAITS_3               (0x0030)       /* FRAM Wait state control: 3 */
#define NWAITS_4               (0x0040)       /* FRAM Wait state control: 4 */
#define NWAITS_5               (0x0050)       /* FRAM Wait state control: 5 */
#define NWAITS_6               (0x0060)       /* FRAM Wait state control: 6 */
#define NWAITS_7               (0x0070)       /* FRAM Wait state control: 7 */

/* GCCTL0 Control Bits */
//#define RESERVED            (0x0001)  /* RESERVED */
#define FRLPMPWR               (0x0002)       /* FRAM Enable FRAM auto power up after LPM */
#define FRPWR                  (0x0004)       /* FRAM Power Control */
#define ACCTEIE                (0x0008)       /* RESERVED */
//#define RESERVED            (0x0010)  /* RESERVED */
#define CBDIE                  (0x0020)       /* Enable NMI event if correctable bit error detected */
#define UBDIE                  (0x0040)       /* Enable NMI event if uncorrectable bit error detected */
#define UBDRSTEN               (0x0080)       /* Enable Power Up Clear (PUC) reset if FRAM uncorrectable bit error detected */

/* GCCTL0 Control Bits */
//#define RESERVED            (0x0001)  /* RESERVED */
#define FRLPMPWR_L             (0x0002)       /* FRAM Enable FRAM auto power up after LPM */
#define FRPWR_L                (0x0004)       /* FRAM Power Control */
#define ACCTEIE_L              (0x0008)       /* RESERVED */
//#define RESERVED            (0x0010)  /* RESERVED */
#define CBDIE_L                (0x0020)       /* Enable NMI event if correctable bit error detected */
#define UBDIE_L                (0x0040)       /* Enable NMI event if uncorrectable bit error detected */
#define UBDRSTEN_L             (0x0080)       /* Enable Power Up Clear (PUC) reset if FRAM uncorrectable bit error detected */

/* GCCTL1 Control Bits */
//#define RESERVED            (0x0001)  /* RESERVED */
#define CBDIFG                 (0x0002)       /* FRAM correctable bit error flag */
#define UBDIFG                 (0x0004)       /* FRAM uncorrectable bit error flag */
#define ACCTEIFG               (0x0008)       /* Access time error flag */

/* GCCTL1 Control Bits */
//#define RESERVED            (0x0001)  /* RESERVED */
#define CBDIFG_L               (0x0002)       /* FRAM correctable bit error flag */
#define UBDIFG_L               (0x0004)       /* FRAM uncorrectable bit error flag */
#define ACCTEIFG_L             (0x0008)       /* Access time error flag */

/************************************************************
* PMM - Power Management System for FR2xx/FR4xx
************************************************************/
#define __MSP430_HAS_PMM_FRAM__                /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PMM_FRAM__ 0x0120
#define PMM_BASE               __MSP430_BASEADDRESS_PMM_FRAM__

SFR_16BIT(PMMCTL0);                           /* PMM Control 0 */
SFR_8BIT(PMMCTL0_L);                          /* PMM Control 0 */
SFR_8BIT(PMMCTL0_H);                          /* PMM Control 0 */
SFR_16BIT(PMMCTL1);                           /* PMM Control 1 */
SFR_8BIT(PMMCTL1_L);                          /* PMM Control 1 */
SFR_8BIT(PMMCTL1_H);                          /* PMM Control 1 */
SFR_16BIT(PMMCTL2);                           /* PMM Control 2 */
SFR_8BIT(PMMCTL2_L);                          /* PMM Control 2 */
SFR_8BIT(PMMCTL2_H);                          /* PMM Control 2 */
SFR_16BIT(PMMIFG);                            /* PMM Interrupt Flag */
SFR_8BIT(PMMIFG_L);                           /* PMM Interrupt Flag */
SFR_8BIT(PMMIFG_H);                           /* PMM Interrupt Flag */
SFR_16BIT(PMMIE);                             /* PMM Interrupt Enable */
SFR_8BIT(PMMIE_L);                            /* PMM Interrupt Enable */
SFR_8BIT(PMMIE_H);                            /* PMM Interrupt Enable */
SFR_16BIT(PM5CTL0);                           /* PMM Power Mode 5 Control Register 0 */
SFR_8BIT(PM5CTL0_L);                          /* PMM Power Mode 5 Control Register 0 */
SFR_8BIT(PM5CTL0_H);                          /* PMM Power Mode 5 Control Register 0 */

#define PMMPW                  (0xA500)       /* PMM Register Write Password */
#define PMMPW_H                (0xA5)         /* PMM Register Write Password for high word access */

/* PMMCTL0 Control Bits */
#define PMMSWBOR               (0x0004)       /* PMM Software BOR */
#define PMMSWPOR               (0x0008)       /* PMM Software POR */
#define PMMREGOFF              (0x0010)       /* PMM Turn Regulator off */
#define SVSHE                  (0x0040)       /* SVS high side enable */

/* PMMCTL0 Control Bits */
#define PMMSWBOR_L             (0x0004)       /* PMM Software BOR */
#define PMMSWPOR_L             (0x0008)       /* PMM Software POR */
#define PMMREGOFF_L            (0x0010)       /* PMM Turn Regulator off */
#define SVSHE_L                (0x0040)       /* SVS high side enable */

/* PMMCTL1 Control Bits */

#define PMMCTL1KEY             (0xCC00)       /* PMM PMMCTL1 Register Write Password */

/* PMMCTL2 Control Bits */
#define INTREFEN               (0x0001)       /* Internal Reference Enable */
#define EXTREFEN               (0x0002)       /* External Reference output Enable */
#define TSENSOREN              (0x0008)       /* Temperature Sensor Enable */
#define REFGENACT              (0x0100)       /* REF Reference generator active */
#define REFBGACT               (0x0200)       /* REF Reference bandgap active */
#define BGMODE                 (0x0800)       /* REF Bandgap mode */
#define REFGENRDY              (0x1000)       /* REF Reference generator ready */
#define REFBGRDY               (0x2000)       /* REF Reference bandgap ready */

/* PMMCTL2 Control Bits */
#define INTREFEN_L             (0x0001)       /* Internal Reference Enable */
#define EXTREFEN_L             (0x0002)       /* External Reference output Enable */
#define TSENSOREN_L            (0x0008)       /* Temperature Sensor Enable */

/* PMMCTL2 Control Bits */
#define REFGENACT_H            (0x0001)       /* REF Reference generator active */
#define REFBGACT_H             (0x0002)       /* REF Reference bandgap active */
#define BGMODE_H               (0x0008)       /* REF Bandgap mode */
#define REFGENRDY_H            (0x0010)       /* REF Reference generator ready */
#define REFBGRDY_H             (0x0020)       /* REF Reference bandgap ready */

/* PMMIFG Control Bits */
#define PMMBORIFG              (0x0100)       /* PMM Software BOR interrupt flag */
#define PMMRSTIFG              (0x0200)       /* PMM RESET pin interrupt flag */
#define PMMPORIFG              (0x0400)       /* PMM Software POR interrupt flag */
#define SVSHIFG                (0x2000)       /* SVS low side interrupt flag */
#define PMMLPM5IFG             (0x8000)       /* LPM5 indication Flag */

/* PMMIFG Control Bits */
#define PMMBORIFG_H            (0x0001)       /* PMM Software BOR interrupt flag */
#define PMMRSTIFG_H            (0x0002)       /* PMM RESET pin interrupt flag */
#define PMMPORIFG_H            (0x0004)       /* PMM Software POR interrupt flag */
#define SVSHIFG_H              (0x0020)       /* SVS low side interrupt flag */
#define PMMLPM5IFG_H           (0x0080)       /* LPM5 indication Flag */

/* PMMIE Control Bits */

/* PM5CTL0 Power Mode 5 Control Bits */
#define LOCKLPM5               (0x0001)       /* Lock I/O pin configuration upon entry/exit to/from LPM5 */
#define LPM5SW                 (0x0010)       /* LPMx.5 switch dis/connected */
#define LPM5SM                 (0x0020)       /* Manual mode for LPM3.5 switch */

/* PM5CTL0 Power Mode 5 Control Bits */
#define LOCKLPM5_L             (0x0001)       /* Lock I/O pin configuration upon entry/exit to/from LPM5 */
#define LPM5SW_L               (0x0010)       /* LPMx.5 switch dis/connected */
#define LPM5SM_L               (0x0020)       /* Manual mode for LPM3.5 switch */


/************************************************************
* DIGITAL I/O Port1/2 Pull up / Pull down Resistors
************************************************************/
#define __MSP430_HAS_PORT1_R__                /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORT1_R__ 0x0200
#define P1_BASE                __MSP430_BASEADDRESS_PORT1_R__
#define __MSP430_HAS_PORT2_R__                /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORT2_R__ 0x0200
#define P2_BASE                __MSP430_BASEADDRESS_PORT2_R__
#define __MSP430_HAS_PORTA_R__                /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORTA_R__ 0x0200
#define PA_BASE                __MSP430_BASEADDRESS_PORTA_R__
#define __MSP430_HAS_P1SEL0__                 /* Define for DriverLib */
#define __MSP430_HAS_P2SEL0__                 /* Define for DriverLib */
#define __MSP430_HAS_PASEL0__                 /* Define for DriverLib */

SFR_16BIT(PAIN);                              /* Port A Input */
SFR_8BIT(PAIN_L);                             /* Port A Input */
SFR_8BIT(PAIN_H);                             /* Port A Input */
SFR_16BIT(PAOUT);                             /* Port A Output */
SFR_8BIT(PAOUT_L);                            /* Port A Output */
SFR_8BIT(PAOUT_H);                            /* Port A Output */
SFR_16BIT(PADIR);                             /* Port A Direction */
SFR_8BIT(PADIR_L);                            /* Port A Direction */
SFR_8BIT(PADIR_H);                            /* Port A Direction */
SFR_16BIT(PAREN);                             /* Port A Resistor Enable */
SFR_8BIT(PAREN_L);                            /* Port A Resistor Enable */
SFR_8BIT(PAREN_H);                            /* Port A Resistor Enable */
SFR_16BIT(PASEL0);                            /* Port A Selection 0 */
SFR_8BIT(PASEL0_L);                           /* Port A Selection 0 */
SFR_8BIT(PASEL0_H);                           /* Port A Selection 0 */
SFR_16BIT(PAIES);                             /* Port A Interrupt Edge Select */
SFR_8BIT(PAIES_L);                            /* Port A Interrupt Edge Select */
SFR_8BIT(PAIES_H);                            /* Port A Interrupt Edge Select */
SFR_16BIT(PAIE);                              /* Port A Interrupt Enable */
SFR_8BIT(PAIE_L);                             /* Port A Interrupt Enable */
SFR_8BIT(PAIE_H);                             /* Port A Interrupt Enable */
SFR_16BIT(PAIFG);                             /* Port A Interrupt Flag */
SFR_8BIT(PAIFG_L);                            /* Port A Interrupt Flag */
SFR_8BIT(PAIFG_H);                            /* Port A Interrupt Flag */


SFR_16BIT(P1IV);                              /* Port 1 Interrupt Vector Word */
SFR_16BIT(P2IV);                              /* Port 2 Interrupt Vector Word */
#define P1IN                   (PAIN_L)       /* Port 1 Input */
#define P1OUT                  (PAOUT_L)      /* Port 1 Output */
#define P1DIR                  (PADIR_L)      /* Port 1 Direction */
#define P1REN                  (PAREN_L)      /* Port 1 Resistor Enable */
#define P1SEL0                 (PASEL0_L)     /* Port 1 Selection 0 */
#define P1IES                  (PAIES_L)      /* Port 1 Interrupt Edge Select */
#define P1IE                   (PAIE_L)       /* Port 1 Interrupt Enable */
#define P1IFG                  (PAIFG_L)      /* Port 1 Interrupt Flag */

//Definitions for P1IV
#define P1IV_NONE              (0x0000)       /* No Interrupt pending */
#define P1IV_P1IFG0            (0x0002)       /* P1IV P1IFG.0 */
#define P1IV_P1IFG1            (0x0004)       /* P1IV P1IFG.1 */
#define P1IV_P1IFG2            (0x0006)       /* P1IV P1IFG.2 */
#define P1IV_P1IFG3            (0x0008)       /* P1IV P1IFG.3 */
#define P1IV_P1IFG4            (0x000A)       /* P1IV P1IFG.4 */
#define P1IV_P1IFG5            (0x000C)       /* P1IV P1IFG.5 */
#define P1IV_P1IFG6            (0x000E)       /* P1IV P1IFG.6 */
#define P1IV_P1IFG7            (0x0010)       /* P1IV P1IFG.7 */

#define P2IN                   (PAIN_H)       /* Port 2 Input */
#define P2OUT                  (PAOUT_H)      /* Port 2 Output */
#define P2DIR                  (PADIR_H)      /* Port 2 Direction */
#define P2REN                  (PAREN_H)      /* Port 2 Resistor Enable */
#define P2SEL0                 (PASEL0_H)     /* Port 2 Selection 0 */
#define P2IES                  (PAIES_H)      /* Port 2 Interrupt Edge Select */
#define P2IE                   (PAIE_H)       /* Port 2 Interrupt Enable */
#define P2IFG                  (PAIFG_H)      /* Port 2 Interrupt Flag */

//Definitions for P2IV
#define P2IV_NONE              (0x0000)       /* No Interrupt pending */
#define P2IV_P2IFG0            (0x0002)       /* P2IV P2IFG.0 */
#define P2IV_P2IFG1            (0x0004)       /* P2IV P2IFG.1 */
#define P2IV_P2IFG2            (0x0006)       /* P2IV P2IFG.2 */
#define P2IV_P2IFG3            (0x0008)       /* P2IV P2IFG.3 */
#define P2IV_P2IFG4            (0x000A)       /* P2IV P2IFG.4 */
#define P2IV_P2IFG5            (0x000C)       /* P2IV P2IFG.5 */
#define P2IV_P2IFG6            (0x000E)       /* P2IV P2IFG.6 */
#define P2IV_P2IFG7            (0x0010)       /* P2IV P2IFG.7 */


/************************************************************
* DIGITAL I/O Port3/4 Pull up / Pull down Resistors
************************************************************/
#define __MSP430_HAS_PORT3_R__                /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORT3_R__ 0x0220
#define P3_BASE                __MSP430_BASEADDRESS_PORT3_R__
#define __MSP430_HAS_PORT4_R__                /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORT4_R__ 0x0220
#define P4_BASE                __MSP430_BASEADDRESS_PORT4_R__
#define __MSP430_HAS_PORTB_R__                /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORTB_R__ 0x0220
#define PB_BASE                __MSP430_BASEADDRESS_PORTB_R__
#define __MSP430_HAS_P3SEL0__                 /* Define for DriverLib */
#define __MSP430_HAS_P4SEL0__                 /* Define for DriverLib */
#define __MSP430_HAS_PBSEL0__                 /* Define for DriverLib */

SFR_16BIT(PBIN);                              /* Port B Input */
SFR_8BIT(PBIN_L);                             /* Port B Input */
SFR_8BIT(PBIN_H);                             /* Port B Input */
SFR_16BIT(PBOUT);                             /* Port B Output */
SFR_8BIT(PBOUT_L);                            /* Port B Output */
SFR_8BIT(PBOUT_H);                            /* Port B Output */
SFR_16BIT(PBDIR);                             /* Port B Direction */
SFR_8BIT(PBDIR_L);                            /* Port B Direction */
SFR_8BIT(PBDIR_H);                            /* Port B Direction */
SFR_16BIT(PBREN);                             /* Port B Resistor Enable */
SFR_8BIT(PBREN_L);                            /* Port B Resistor Enable */
SFR_8BIT(PBREN_H);                            /* Port B Resistor Enable */
SFR_16BIT(PBSEL0);                            /* Port B Selection 0 */
SFR_8BIT(PBSEL0_L);                           /* Port B Selection 0 */
SFR_8BIT(PBSEL0_H);                           /* Port B Selection 0 */


#define P3IN                   (PBIN_L)       /* Port 3 Input */
#define P3OUT                  (PBOUT_L)      /* Port 3 Output */
#define P3DIR                  (PBDIR_L)      /* Port 3 Direction */
#define P3REN                  (PBREN_L)      /* Port 3 Resistor Enable */
#define P3SEL0                 (PBSEL0_L)     /* Port 3 Selection 0 */

#define P4IN                   (PBIN_H)       /* Port 4 Input */
#define P4OUT                  (PBOUT_H)      /* Port 4 Output */
#define P4DIR                  (PBDIR_H)      /* Port 4 Direction */
#define P4REN                  (PBREN_H)      /* Port 4 Resistor Enable */
#define P4SEL0                 (PBSEL0_H)     /* Port 4 Selection 0 */


/************************************************************
* DIGITAL I/O Port5/6 Pull up / Pull down Resistors
************************************************************/
#define __MSP430_HAS_PORT5_R__                /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORT5_R__ 0x0240
#define P5_BASE                __MSP430_BASEADDRESS_PORT5_R__
#define __MSP430_HAS_PORT6_R__                /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORT6_R__ 0x0240
#define P6_BASE                __MSP430_BASEADDRESS_PORT6_R__
#define __MSP430_HAS_PORTC_R__                /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORTC_R__ 0x0240
#define PC_BASE                __MSP430_BASEADDRESS_PORTC_R__
#define __MSP430_HAS_P5SEL0__                 /* Define for DriverLib */
#define __MSP430_HAS_P6SEL0__                 /* Define for DriverLib */
#define __MSP430_HAS_PCSEL0__                 /* Define for DriverLib */

SFR_16BIT(PCIN);                              /* Port C Input */
SFR_8BIT(PCIN_L);                             /* Port C Input */
SFR_8BIT(PCIN_H);                             /* Port C Input */
SFR_16BIT(PCOUT);                             /* Port C Output */
SFR_8BIT(PCOUT_L);                            /* Port C Output */
SFR_8BIT(PCOUT_H);                            /* Port C Output */
SFR_16BIT(PCDIR);                             /* Port C Direction */
SFR_8BIT(PCDIR_L);                            /* Port C Direction */
SFR_8BIT(PCDIR_H);                            /* Port C Direction */
SFR_16BIT(PCREN);                             /* Port C Resistor Enable */
SFR_8BIT(PCREN_L);                            /* Port C Resistor Enable */
SFR_8BIT(PCREN_H);                            /* Port C Resistor Enable */
SFR_16BIT(PCSEL0);                            /* Port C Selection 0 */
SFR_8BIT(PCSEL0_L);                           /* Port C Selection 0 */
SFR_8BIT(PCSEL0_H);                           /* Port C Selection 0 */


#define P5IN                   (PCIN_L)       /* Port 5 Input */
#define P5OUT                  (PCOUT_L)      /* Port 5 Output */
#define P5DIR                  (PCDIR_L)      /* Port 5 Direction */
#define P5REN                  (PCREN_L)      /* Port 5 Resistor Enable */
#define P5SEL0                 (PCSEL0_L)     /* Port 5 Selection 0 */

#define P6IN                   (PCIN_H)       /* Port 6 Input */
#define P6OUT                  (PCOUT_H)      /* Port 6 Output */
#define P6DIR                  (PCDIR_H)      /* Port 6 Direction */
#define P6REN                  (PCREN_H)      /* Port 6 Resistor Enable */
#define P6SEL0                 (PCSEL0_H)     /* Port 6 Selection 0 */


/************************************************************
* DIGITAL I/O Port7/8 Pull up / Pull down Resistors
************************************************************/
#define __MSP430_HAS_PORT7_R__                /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORT7_R__ 0x0260
#define P7_BASE                __MSP430_BASEADDRESS_PORT7_R__
#define __MSP430_HAS_PORT8_R__                /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORT8_R__ 0x0260
#define P8_BASE                __MSP430_BASEADDRESS_PORT8_R__
#define __MSP430_HAS_PORTD_R__                /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORTD_R__ 0x0260
#define PD_BASE                __MSP430_BASEADDRESS_PORTD_R__
#define __MSP430_HAS_P7SEL0__                 /* Define for DriverLib */
#define __MSP430_HAS_P8SEL0__                 /* Define for DriverLib */
#define __MSP430_HAS_PDSEL0__                 /* Define for DriverLib */

SFR_16BIT(PDIN);                              /* Port D Input */
SFR_8BIT(PDIN_L);                             /* Port D Input */
SFR_8BIT(PDIN_H);                             /* Port D Input */
SFR_16BIT(PDOUT);                             /* Port D Output */
SFR_8BIT(PDOUT_L);                            /* Port D Output */
SFR_8BIT(PDOUT_H);                            /* Port D Output */
SFR_16BIT(PDDIR);                             /* Port D Direction */
SFR_8BIT(PDDIR_L);                            /* Port D Direction */
SFR_8BIT(PDDIR_H);                            /* Port D Direction */
SFR_16BIT(PDREN);                             /* Port D Resistor Enable */
SFR_8BIT(PDREN_L);                            /* Port D Resistor Enable */
SFR_8BIT(PDREN_H);                            /* Port D Resistor Enable */
SFR_16BIT(PDSEL0);                            /* Port D Selection 0 */
SFR_8BIT(PDSEL0_L);                           /* Port D Selection 0 */
SFR_8BIT(PDSEL0_H);                           /* Port D Selection 0 */


#define P7IN                   (PDIN_L)       /* Port 7 Input */
#define P7OUT                  (PDOUT_L)      /* Port 7 Output */
#define P7DIR                  (PDDIR_L)      /* Port 7 Direction */
#define P7REN                  (PDREN_L)      /* Port 7 Resistor Enable */
#define P7SEL0                 (PDSEL0_L)     /* Port 7 Selection 0 */

#define P8IN                   (PDIN_H)       /* Port 8 Input */
#define P8OUT                  (PDOUT_H)      /* Port 8 Output */
#define P8DIR                  (PDDIR_H)      /* Port 8 Direction */
#define P8REN                  (PDREN_H)      /* Port 8 Resistor Enable */
#define P8SEL0                 (PDSEL0_H)     /* Port 8 Selection 0 */


/************************************************************
* Real-Time Clock (RTC) Counter
************************************************************/
#define __MSP430_HAS_RTC__                    /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_RTC__ 0x03C0
#define RTC_BASE               __MSP430_BASEADDRESS_RTC__

SFR_16BIT(RTCCTL);                            /* RTC control Register */
SFR_8BIT(RTCCTL_L);                           /* RTC control Register */
SFR_8BIT(RTCCTL_H);                           /* RTC control Register */
SFR_16BIT(RTCIV);                             /* RTC interrupt vector */
SFR_8BIT(RTCIV_L);                            /* RTC interrupt vector */
SFR_8BIT(RTCIV_H);                            /* RTC interrupt vector */
SFR_16BIT(RTCMOD);                            /* RTC moduloRegister */
SFR_8BIT(RTCMOD_L);                           /* RTC moduloRegister */
SFR_8BIT(RTCMOD_H);                           /* RTC moduloRegister */
SFR_16BIT(RTCCNT);                            /* RTC counter Register */
SFR_8BIT(RTCCNT_L);                           /* RTC counter Register */
SFR_8BIT(RTCCNT_H);                           /* RTC counter Register */

/* RTC control Register */
#define RTCIF                  (0x0001)       /* Low-Power-Counter Interrupt Flag */
#define RTCIE                  (0x0002)       /* Low-Power-Counter Interrupt Enable */
#define RTCSR                  (0x0040)       /* Low-Power-Counter Software Reset */
#define RTCPS0                 (0x0100)       /* Low-Power-Counter Clock Pre-divider Select Bit: 0 */
#define RTCPS1                 (0x0200)       /* Low-Power-Counter Clock Pre-divider Select Bit: 1 */
#define RTCPS2                 (0x0400)       /* Low-Power-Counter Clock Pre-divider Select Bit: 2 */
#define RTCSS0                 (0x1000)       /* Low-Power-Counter Clock Source Select Bit: 0 */
#define RTCSS1                 (0x2000)       /* Low-Power-Counter Clock Source Select Bit: 1 */

/* RTC control Register */
#define RTCIF_L                (0x0001)       /* Low-Power-Counter Interrupt Flag */
#define RTCIE_L                (0x0002)       /* Low-Power-Counter Interrupt Enable */
#define RTCSR_L                (0x0040)       /* Low-Power-Counter Software Reset */

/* RTC control Register */
#define RTCPS0_H               (0x0001)       /* Low-Power-Counter Clock Pre-divider Select Bit: 0 */
#define RTCPS1_H               (0x0002)       /* Low-Power-Counter Clock Pre-divider Select Bit: 1 */
#define RTCPS2_H               (0x0004)       /* Low-Power-Counter Clock Pre-divider Select Bit: 2 */
#define RTCSS0_H               (0x0010)       /* Low-Power-Counter Clock Source Select Bit: 0 */
#define RTCSS1_H               (0x0020)       /* Low-Power-Counter Clock Source Select Bit: 1 */

#define RTCPS_0                (0x0000)       /* Low-Power-Counter Clock Pre-divider Select: 0 */
#define RTCPS_1                (0x0100)       /* Low-Power-Counter Clock Pre-divider Select: 1 */
#define RTCPS_2                (0x0200)       /* Low-Power-Counter Clock Pre-divider Select: 2 */
#define RTCPS_3                (0x0300)       /* Low-Power-Counter Clock Pre-divider Select: 3 */
#define RTCPS_4                (0x0400)       /* Low-Power-Counter Clock Pre-divider Select: 4 */
#define RTCPS_5                (0x0500)       /* Low-Power-Counter Clock Pre-divider Select: 5 */
#define RTCPS_6                (0x0600)       /* Low-Power-Counter Clock Pre-divider Select: 6 */
#define RTCPS_7                (0x0700)       /* Low-Power-Counter Clock Pre-divider Select: 7 */
#define RTCPS__1               (0x0000)       /* Low-Power-Counter Clock Pre-divider Select: /1 */
#define RTCPS__10              (0x0100)       /* Low-Power-Counter Clock Pre-divider Select: /10 */
#define RTCPS__100             (0x0200)       /* Low-Power-Counter Clock Pre-divider Select: /100 */
#define RTCPS__1000            (0x0300)       /* Low-Power-Counter Clock Pre-divider Select: /1000 */
#define RTCPS__16              (0x0400)       /* Low-Power-Counter Clock Pre-divider Select: /16 */
#define RTCPS__64              (0x0500)       /* Low-Power-Counter Clock Pre-divider Select: /64 */
#define RTCPS__256             (0x0600)       /* Low-Power-Counter Clock Pre-divider Select: /256 */
#define RTCPS__1024            (0x0700)       /* Low-Power-Counter Clock Pre-divider Select: /1024 */

#define RTCSS_0                (0x0000)       /* Low-Power-Counter Clock Source Select: 0 */
#define RTCSS_1                (0x1000)       /* Low-Power-Counter Clock Source Select: 1 */
#define RTCSS_2                (0x2000)       /* Low-Power-Counter Clock Source Select: 2 */
#define RTCSS_3                (0x3000)       /* Low-Power-Counter Clock Source Select: 3 */

#define RTCSS__DISABLED        (0x0000)       /* Low-Power-Counter Clock Source Select: DISABLED  */
#define RTCSS__SMCLK           (0x1000)       /* Low-Power-Counter Clock Source Select: SMCLK */
#define RTCSS__XT1CLK          (0x2000)       /* Low-Power-Counter Clock Source Select: XT1CLK */
#define RTCSS__VLOCLK          (0x3000)       /* Low-Power-Counter Clock Source Select: VLOCLK */

/* RTCIV Definitions */
#define RTCIV_NONE             (0x0000)       /* No Interrupt pending */
#define RTCIV_RTCIF            (0x0002)       /* RTC Overflow */

/************************************************************
* SFR - Special Function Register Module
************************************************************/
#define __MSP430_HAS_SFR__                    /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_SFR__ 0x0100
#define SFR_BASE               __MSP430_BASEADDRESS_SFR__

SFR_16BIT(SFRIE1);                            /* Interrupt Enable 1 */
SFR_8BIT(SFRIE1_L);                           /* Interrupt Enable 1 */
SFR_8BIT(SFRIE1_H);                           /* Interrupt Enable 1 */

/* SFRIE1 Control Bits */
#define WDTIE                  (0x0001)       /* WDT Interrupt Enable */
#define OFIE                   (0x0002)       /* Osc Fault Enable */
//#define Reserved          (0x0004)
#define VMAIE                  (0x0008)       /* Vacant Memory Interrupt Enable */
#define NMIIE                  (0x0010)       /* NMI Interrupt Enable */
#define JMBINIE                (0x0040)       /* JTAG Mail Box input Interrupt Enable */
#define JMBOUTIE               (0x0080)       /* JTAG Mail Box output Interrupt Enable */

#define WDTIE_L                (0x0001)       /* WDT Interrupt Enable */
#define OFIE_L                 (0x0002)       /* Osc Fault Enable */
//#define Reserved          (0x0004)
#define VMAIE_L                (0x0008)       /* Vacant Memory Interrupt Enable */
#define NMIIE_L                (0x0010)       /* NMI Interrupt Enable */
#define JMBINIE_L              (0x0040)       /* JTAG Mail Box input Interrupt Enable */
#define JMBOUTIE_L             (0x0080)       /* JTAG Mail Box output Interrupt Enable */

SFR_16BIT(SFRIFG1);                           /* Interrupt Flag 1 */
SFR_8BIT(SFRIFG1_L);                          /* Interrupt Flag 1 */
SFR_8BIT(SFRIFG1_H);                          /* Interrupt Flag 1 */
/* SFRIFG1 Control Bits */
#define WDTIFG                 (0x0001)       /* WDT Interrupt Flag */
#define OFIFG                  (0x0002)       /* Osc Fault Flag */
//#define Reserved          (0x0004)
#define VMAIFG                 (0x0008)       /* Vacant Memory Interrupt Flag */
#define NMIIFG                 (0x0010)       /* NMI Interrupt Flag */
//#define Reserved          (0x0020)
#define JMBINIFG               (0x0040)       /* JTAG Mail Box input Interrupt Flag */
#define JMBOUTIFG              (0x0080)       /* JTAG Mail Box output Interrupt Flag */

#define WDTIFG_L               (0x0001)       /* WDT Interrupt Flag */
#define OFIFG_L                (0x0002)       /* Osc Fault Flag */
//#define Reserved          (0x0004)
#define VMAIFG_L               (0x0008)       /* Vacant Memory Interrupt Flag */
#define NMIIFG_L               (0x0010)       /* NMI Interrupt Flag */
//#define Reserved          (0x0020)
#define JMBINIFG_L             (0x0040)       /* JTAG Mail Box input Interrupt Flag */
#define JMBOUTIFG_L            (0x0080)       /* JTAG Mail Box output Interrupt Flag */

SFR_16BIT(SFRRPCR);                           /* RESET Pin Control Register */
SFR_8BIT(SFRRPCR_L);                          /* RESET Pin Control Register */
SFR_8BIT(SFRRPCR_H);                          /* RESET Pin Control Register */
/* SFRRPCR Control Bits */
#define SYSNMI                 (0x0001)       /* NMI select */
#define SYSNMIIES              (0x0002)       /* NMI edge select */
#define SYSRSTUP               (0x0004)       /* RESET Pin pull down/up select */
#define SYSRSTRE               (0x0008)       /* RESET Pin Resistor enable */

#define SYSNMI_L               (0x0001)       /* NMI select */
#define SYSNMIIES_L            (0x0002)       /* NMI edge select */
#define SYSRSTUP_L             (0x0004)       /* RESET Pin pull down/up select */
#define SYSRSTRE_L             (0x0008)       /* RESET Pin Resistor enable */

/************************************************************
* SYS - System Module
************************************************************/
#define __MSP430_HAS_SYS__                    /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_SYS__ 0x0140
#define SYS_BASE               __MSP430_BASEADDRESS_SYS__
#define __MSP430_HAS_DATA_FRWP__                /* Definition to show that Function is available */
#define __MSP430_HAS_ADC_PCTLSEL__                /* Definition to show that Function is available */
#define __MSP430_HAS_LCP_POWER_PIN__                /* Definition to show that Function is available */

SFR_16BIT(SYSCTL);                            /* System control */
SFR_8BIT(SYSCTL_L);                           /* System control */
SFR_8BIT(SYSCTL_H);                           /* System control */
SFR_16BIT(SYSBSLC);                           /* Boot strap configuration area */
SFR_8BIT(SYSBSLC_L);                          /* Boot strap configuration area */
SFR_8BIT(SYSBSLC_H);                          /* Boot strap configuration area */
SFR_16BIT(SYSJMBC);                           /* JTAG mailbox control */
SFR_8BIT(SYSJMBC_L);                          /* JTAG mailbox control */
SFR_8BIT(SYSJMBC_H);                          /* JTAG mailbox control */
SFR_16BIT(SYSJMBI0);                          /* JTAG mailbox input 0 */
SFR_8BIT(SYSJMBI0_L);                         /* JTAG mailbox input 0 */
SFR_8BIT(SYSJMBI0_H);                         /* JTAG mailbox input 0 */
SFR_16BIT(SYSJMBI1);                          /* JTAG mailbox input 1 */
SFR_8BIT(SYSJMBI1_L);                         /* JTAG mailbox input 1 */
SFR_8BIT(SYSJMBI1_H);                         /* JTAG mailbox input 1 */
SFR_16BIT(SYSJMBO0);                          /* JTAG mailbox output 0 */
SFR_8BIT(SYSJMBO0_L);                         /* JTAG mailbox output 0 */
SFR_8BIT(SYSJMBO0_H);                         /* JTAG mailbox output 0 */
SFR_16BIT(SYSJMBO1);                          /* JTAG mailbox output 1 */
SFR_8BIT(SYSJMBO1_L);                         /* JTAG mailbox output 1 */
SFR_8BIT(SYSJMBO1_H);                         /* JTAG mailbox output 1 */

SFR_16BIT(SYSBERRIV);                         /* Bus Error vector generator */
SFR_8BIT(SYSBERRIV_L);                        /* Bus Error vector generator */
SFR_8BIT(SYSBERRIV_H);                        /* Bus Error vector generator */
SFR_16BIT(SYSUNIV);                           /* User NMI vector generator */
SFR_8BIT(SYSUNIV_L);                          /* User NMI vector generator */
SFR_8BIT(SYSUNIV_H);                          /* User NMI vector generator */
SFR_16BIT(SYSSNIV);                           /* System NMI vector generator */
SFR_8BIT(SYSSNIV_L);                          /* System NMI vector generator */
SFR_8BIT(SYSSNIV_H);                          /* System NMI vector generator */
SFR_16BIT(SYSRSTIV);                          /* Reset vector generator */
SFR_8BIT(SYSRSTIV_L);                         /* Reset vector generator */
SFR_8BIT(SYSRSTIV_H);                         /* Reset vector generator */
SFR_16BIT(SYSCFG0);                           /* System Configuration 0 */
SFR_8BIT(SYSCFG0_L);                          /* System Configuration 0 */
SFR_8BIT(SYSCFG0_H);                          /* System Configuration 0 */
SFR_16BIT(SYSCFG1);                           /* System Configuration 1 */
SFR_8BIT(SYSCFG1_L);                          /* System Configuration 1 */
SFR_8BIT(SYSCFG1_H);                          /* System Configuration 1 */
SFR_16BIT(SYSCFG2);                           /* System Configuration 2 */
SFR_8BIT(SYSCFG2_L);                          /* System Configuration 2 */
SFR_8BIT(SYSCFG2_H);                          /* System Configuration 2 */

/* SYSCTL Control Bits */
#define SYSRIVECT              (0x0001)       /* SYS - RAM based interrupt vectors */
//#define RESERVED            (0x0002)  /* SYS - Reserved */
#define SYSPMMPE               (0x0004)       /* SYS - PMM access protect */
//#define RESERVED            (0x0008)  /* SYS - Reserved */
#define SYSBSLIND              (0x0010)       /* SYS - TCK/RST indication detected */
#define SYSJTAGPIN             (0x0020)       /* SYS - Dedicated JTAG pins enabled */
//#define RESERVED            (0x0040)  /* SYS - Reserved */
//#define RESERVED            (0x0080)  /* SYS - Reserved */
//#define RESERVED            (0x0100)  /* SYS - Reserved */
//#define RESERVED            (0x0200)  /* SYS - Reserved */
//#define RESERVED            (0x0400)  /* SYS - Reserved */
//#define RESERVED            (0x0800)  /* SYS - Reserved */
//#define RESERVED            (0x1000)  /* SYS - Reserved */
//#define RESERVED            (0x2000)  /* SYS - Reserved */
//#define RESERVED            (0x4000)  /* SYS - Reserved */
//#define RESERVED            (0x8000)  /* SYS - Reserved */

/* SYSCTL Control Bits */
#define SYSRIVECT_L            (0x0001)       /* SYS - RAM based interrupt vectors */
//#define RESERVED            (0x0002)  /* SYS - Reserved */
#define SYSPMMPE_L             (0x0004)       /* SYS - PMM access protect */
//#define RESERVED            (0x0008)  /* SYS - Reserved */
#define SYSBSLIND_L            (0x0010)       /* SYS - TCK/RST indication detected */
#define SYSJTAGPIN_L           (0x0020)       /* SYS - Dedicated JTAG pins enabled */
//#define RESERVED            (0x0040)  /* SYS - Reserved */
//#define RESERVED            (0x0080)  /* SYS - Reserved */
//#define RESERVED            (0x0100)  /* SYS - Reserved */
//#define RESERVED            (0x0200)  /* SYS - Reserved */
//#define RESERVED            (0x0400)  /* SYS - Reserved */
//#define RESERVED            (0x0800)  /* SYS - Reserved */
//#define RESERVED            (0x1000)  /* SYS - Reserved */
//#define RESERVED            (0x2000)  /* SYS - Reserved */
//#define RESERVED            (0x4000)  /* SYS - Reserved */
//#define RESERVED            (0x8000)  /* SYS - Reserved */

/* SYSBSLC Control Bits */
#define SYSBSLR                (0x0004)       /* SYS - RAM assigned to BSL */
//#define RESERVED            (0x0008)  /* SYS - Reserved */
//#define RESERVED            (0x0010)  /* SYS - Reserved */
//#define RESERVED            (0x0020)  /* SYS - Reserved */
//#define RESERVED            (0x0040)  /* SYS - Reserved */
//#define RESERVED            (0x0080)  /* SYS - Reserved */
//#define RESERVED            (0x0100)  /* SYS - Reserved */
//#define RESERVED            (0x0200)  /* SYS - Reserved */
//#define RESERVED            (0x0400)  /* SYS - Reserved */
//#define RESERVED            (0x0800)  /* SYS - Reserved */
//#define RESERVED            (0x1000)  /* SYS - Reserved */
//#define RESERVED            (0x2000)  /* SYS - Reserved */
#define SYSBSLOFF              (0x4000)       /* SYS - BSL Memory disabled */
#define SYSBSLPE               (0x8000)       /* SYS - BSL Memory protection enabled */

/* SYSBSLC Control Bits */
#define SYSBSLR_L              (0x0004)       /* SYS - RAM assigned to BSL */
//#define RESERVED            (0x0008)  /* SYS - Reserved */
//#define RESERVED            (0x0010)  /* SYS - Reserved */
//#define RESERVED            (0x0020)  /* SYS - Reserved */
//#define RESERVED            (0x0040)  /* SYS - Reserved */
//#define RESERVED            (0x0080)  /* SYS - Reserved */
//#define RESERVED            (0x0100)  /* SYS - Reserved */
//#define RESERVED            (0x0200)  /* SYS - Reserved */
//#define RESERVED            (0x0400)  /* SYS - Reserved */
//#define RESERVED            (0x0800)  /* SYS - Reserved */
//#define RESERVED            (0x1000)  /* SYS - Reserved */
//#define RESERVED            (0x2000)  /* SYS - Reserved */

/* SYSBSLC Control Bits */
//#define RESERVED            (0x0008)  /* SYS - Reserved */
//#define RESERVED            (0x0010)  /* SYS - Reserved */
//#define RESERVED            (0x0020)  /* SYS - Reserved */
//#define RESERVED            (0x0040)  /* SYS - Reserved */
//#define RESERVED            (0x0080)  /* SYS - Reserved */
//#define RESERVED            (0x0100)  /* SYS - Reserved */
//#define RESERVED            (0x0200)  /* SYS - Reserved */
//#define RESERVED            (0x0400)  /* SYS - Reserved */
//#define RESERVED            (0x0800)  /* SYS - Reserved */
//#define RESERVED            (0x1000)  /* SYS - Reserved */
//#define RESERVED            (0x2000)  /* SYS - Reserved */
#define SYSBSLOFF_H            (0x0040)       /* SYS - BSL Memory disabled */
#define SYSBSLPE_H             (0x0080)       /* SYS - BSL Memory protection enabled */

/* SYSJMBC Control Bits */
#define JMBIN0FG               (0x0001)       /* SYS - Incoming JTAG Mailbox 0 Flag */
#define JMBIN1FG               (0x0002)       /* SYS - Incoming JTAG Mailbox 1 Flag */
#define JMBOUT0FG              (0x0004)       /* SYS - Outgoing JTAG Mailbox 0 Flag */
#define JMBOUT1FG              (0x0008)       /* SYS - Outgoing JTAG Mailbox 1 Flag */
#define JMBMODE                (0x0010)       /* SYS - JMB 16/32 Bit Mode */
//#define RESERVED            (0x0020)  /* SYS - Reserved */
#define JMBCLR0OFF             (0x0040)       /* SYS - Incoming JTAG Mailbox 0 Flag auto-clear disalbe */
#define JMBCLR1OFF             (0x0080)       /* SYS - Incoming JTAG Mailbox 1 Flag auto-clear disalbe */
//#define RESERVED            (0x0100)  /* SYS - Reserved */
//#define RESERVED            (0x0200)  /* SYS - Reserved */
//#define RESERVED            (0x0400)  /* SYS - Reserved */
//#define RESERVED            (0x0800)  /* SYS - Reserved */
//#define RESERVED            (0x1000)  /* SYS - Reserved */
//#define RESERVED            (0x2000)  /* SYS - Reserved */
//#define RESERVED            (0x4000)  /* SYS - Reserved */
//#define RESERVED            (0x8000)  /* SYS - Reserved */

/* SYSJMBC Control Bits */
#define JMBIN0FG_L             (0x0001)       /* SYS - Incoming JTAG Mailbox 0 Flag */
#define JMBIN1FG_L             (0x0002)       /* SYS - Incoming JTAG Mailbox 1 Flag */
#define JMBOUT0FG_L            (0x0004)       /* SYS - Outgoing JTAG Mailbox 0 Flag */
#define JMBOUT1FG_L            (0x0008)       /* SYS - Outgoing JTAG Mailbox 1 Flag */
#define JMBMODE_L              (0x0010)       /* SYS - JMB 16/32 Bit Mode */
//#define RESERVED            (0x0020)  /* SYS - Reserved */
#define JMBCLR0OFF_L           (0x0040)       /* SYS - Incoming JTAG Mailbox 0 Flag auto-clear disalbe */
#define JMBCLR1OFF_L           (0x0080)       /* SYS - Incoming JTAG Mailbox 1 Flag auto-clear disalbe */
//#define RESERVED            (0x0100)  /* SYS - Reserved */
//#define RESERVED            (0x0200)  /* SYS - Reserved */
//#define RESERVED            (0x0400)  /* SYS - Reserved */
//#define RESERVED            (0x0800)  /* SYS - Reserved */
//#define RESERVED            (0x1000)  /* SYS - Reserved */
//#define RESERVED            (0x2000)  /* SYS - Reserved */
//#define RESERVED            (0x4000)  /* SYS - Reserved */
//#define RESERVED            (0x8000)  /* SYS - Reserved */

/* SYSCFG0 Control Bits */
#define PFWP                   (0x0001)       /* Program FRAM Write Protection */
#define DFWP                   (0x0002)       /* Data FRAM Write Protection */

/* SYSCFG0 Control Bits */
#define PFWP_L                 (0x0001)       /* Program FRAM Write Protection */
#define DFWP_L                 (0x0002)       /* Data FRAM Write Protection */

/* SYSCFG1 Control Bits */
#define IREN                   (0x0001)       /* Infrared enable */
#define IRPSEL                 (0x0002)       /* Infrared polarity select */
#define IRMSEL                 (0x0004)       /* Infrared mode select */
#define IRDSSEL                (0x0008)       /* Infrared data source select */
#define IRDATA                 (0x0010)       /* Infrared enable */

/* SYSCFG1 Control Bits */
#define IREN_L                 (0x0001)       /* Infrared enable */
#define IRPSEL_L               (0x0002)       /* Infrared polarity select */
#define IRMSEL_L               (0x0004)       /* Infrared mode select */
#define IRDSSEL_L              (0x0008)       /* Infrared data source select */
#define IRDATA_L               (0x0010)       /* Infrared enable */

/* SYSCFG2 Control Bits */
#define ADCPCTL0               (0x0001)       /* ADC input A0 pin select */
#define ADCPCTL1               (0x0002)       /* ADC input A1 pin select */
#define ADCPCTL2               (0x0004)       /* ADC input A2 pin select */
#define ADCPCTL3               (0x0008)       /* ADC input A3 pin select */
#define ADCPCTL4               (0x0010)       /* ADC input A4 pin select */
#define ADCPCTL5               (0x0020)       /* ADC input A5 pin select */
#define ADCPCTL6               (0x0040)       /* ADC input A6 pin select */
#define ADCPCTL7               (0x0080)       /* ADC input A7 pin select */
#define ADCPCTL8               (0x0100)       /* ADC input A8 pin select */
#define ADCPCTL9               (0x0200)       /* ADC input A9 pin select */
#define LCDPCTL                (0x1000)       /* LCD Power Pin */

/* SYSCFG2 Control Bits */
#define ADCPCTL0_L             (0x0001)       /* ADC input A0 pin select */
#define ADCPCTL1_L             (0x0002)       /* ADC input A1 pin select */
#define ADCPCTL2_L             (0x0004)       /* ADC input A2 pin select */
#define ADCPCTL3_L             (0x0008)       /* ADC input A3 pin select */
#define ADCPCTL4_L             (0x0010)       /* ADC input A4 pin select */
#define ADCPCTL5_L             (0x0020)       /* ADC input A5 pin select */
#define ADCPCTL6_L             (0x0040)       /* ADC input A6 pin select */
#define ADCPCTL7_L             (0x0080)       /* ADC input A7 pin select */

/* SYSCFG2 Control Bits */
#define ADCPCTL8_H             (0x0001)       /* ADC input A8 pin select */
#define ADCPCTL9_H             (0x0002)       /* ADC input A9 pin select */
#define LCDPCTL_H              (0x0010)       /* LCD Power Pin */


/* SYSUNIV Definitions */
#define SYSUNIV_NONE           (0x0000)       /* No Interrupt pending */
#define SYSUNIV_NMIIFG         (0x0002)       /* SYSUNIV : NMIIFG */
#define SYSUNIV_OFIFG          (0x0004)       /* SYSUNIV : Osc. Fail - OFIFG */

/* SYSSNIV Definitions */
#define SYSSNIV_NONE           (0x0000)       /* No Interrupt pending */
#define SYSSNIV_SVS            (0x0002)       /* SYSSNIV : SVS low-power reset entry */
#define SYSSNIV_UBDIFG         (0x0004)       /* SYSSNIV : FRAM Uncorrectable bit Error */
#define SYSSNIV_ACCTEIFG       (0x0006)       /* SYSSNIV : ACCTEIFG access time error */
#define SYSSNIV_RES8           (0x0008)       /* SYSSNIV : Reserved */
#define SYSSNIV_RES10          (0x000A)       /* SYSSNIV : Reserved */
#define SYSSNIV_RES12          (0x000C)       /* SYSSNIV : Reserved */
#define SYSSNIV_RES14          (0x000E)       /* SYSSNIV : Reserved */
#define SYSSNIV_RES16          (0x0010)       /* SYSSNIV : Reserved */
#define SYSSNIV_VMAIFG         (0x0012)       /* SYSSNIV : VMAIFG */
#define SYSSNIV_JMBINIFG       (0x0014)       /* SYSSNIV : JMBINIFG */
#define SYSSNIV_JMBOUTIFG      (0x0016)       /* SYSSNIV : JMBOUTIFG */
#define SYSSNIV_CBDIFG         (0x0018)       /* SYSSNIV : FRAM Correctable Bit error */

/* SYSRSTIV Definitions */
#define SYSRSTIV_NONE          (0x0000)       /* No Interrupt pending */
#define SYSRSTIV_BOR           (0x0002)       /* SYSRSTIV : BOR */
#define SYSRSTIV_RSTNMI        (0x0004)       /* SYSRSTIV : RST/NMI */
#define SYSRSTIV_DOBOR         (0x0006)       /* SYSRSTIV : Do BOR */
#define SYSRSTIV_LPM5WU        (0x0008)       /* SYSRSTIV : Port LPM5 Wake Up */
#define SYSRSTIV_SECYV         (0x000A)       /* SYSRSTIV : Security violation */
#define SYSRSTIV_RES0C         (0x000C)       /* SYSRSTIV : Reserved */
#define SYSRSTIV_SVSHIFG       (0x000E)       /* SYSRSTIV : SVSHIFG */
#define SYSRSTIV_RES10         (0x0010)       /* SYSRSTIV : Reserved */
#define SYSRSTIV_RES12         (0x0012)       /* SYSRSTIV : Reserved */
#define SYSRSTIV_DOPOR         (0x0014)       /* SYSRSTIV : Do POR */
#define SYSRSTIV_WDTTO         (0x0016)       /* SYSRSTIV : WDT Time out */
#define SYSRSTIV_WDTPW         (0x0018)       /* SYSRSTIV : WDT Key violation */
#define SYSRSTIV_WDTKEY        (0x0018)       /* SYSRSTIV : WDT Key violation */
#define SYSRSTIV_FRCTLPW       (0x001A)       /* SYSRSTIV : FRAM Key violation */
#define SYSRSTIV_UBDIFG        (0x001C)       /* SYSRSTIV : FRAM Uncorrectable bit Error */
#define SYSRSTIV_PERF          (0x001E)       /* SYSRSTIV : peripheral/config area fetch */
#define SYSRSTIV_PMMPW         (0x0020)       /* SYSRSTIV : PMM Password violation */
#define SYSRSTIV_RES22         (0x0022)       /* SYSRSTIV : Reserved */
#define SYSRSTIV_FLLUL         (0x0024)       /* SYSRSTIV : FLL unlock */

/************************************************************
* Timer0_A3
************************************************************/
#define __MSP430_HAS_T0A3__                   /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_T0A3__ 0x0300
#define TIMER_A0_BASE          __MSP430_BASEADDRESS_T0A3__

SFR_16BIT(TA0CTL);                            /* Timer0_A3 Control */
SFR_16BIT(TA0CCTL0);                          /* Timer0_A3 Capture/Compare Control 0 */
SFR_16BIT(TA0CCTL1);                          /* Timer0_A3 Capture/Compare Control 1 */
SFR_16BIT(TA0CCTL2);                          /* Timer0_A3 Capture/Compare Control 2 */
SFR_16BIT(TA0R);                              /* Timer0_A3 */
SFR_16BIT(TA0CCR0);                           /* Timer0_A3 Capture/Compare 0 */
SFR_16BIT(TA0CCR1);                           /* Timer0_A3 Capture/Compare 1 */
SFR_16BIT(TA0CCR2);                           /* Timer0_A3 Capture/Compare 2 */
SFR_16BIT(TA0IV);                             /* Timer0_A3 Interrupt Vector Word */
SFR_16BIT(TA0EX0);                            /* Timer0_A3 Expansion Register 0 */

/* TAxCTL Control Bits */
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
#define MC_2                   (2*0x10u)      /* Timer A mode control: 2 - Continuous up */
#define MC_3                   (3*0x10u)      /* Timer A mode control: 3 - Up/Down */
#define ID_0                   (0*0x40u)      /* Timer A input divider: 0 - /1 */
#define ID_1                   (1*0x40u)      /* Timer A input divider: 1 - /2 */
#define ID_2                   (2*0x40u)      /* Timer A input divider: 2 - /4 */
#define ID_3                   (3*0x40u)      /* Timer A input divider: 3 - /8 */
#define TASSEL_0               (0*0x100u)     /* Timer A clock source select: 0 - TACLK */
#define TASSEL_1               (1*0x100u)     /* Timer A clock source select: 1 - ACLK  */
#define TASSEL_2               (2*0x100u)     /* Timer A clock source select: 2 - SMCLK */
#define TASSEL_3               (3*0x100u)     /* Timer A clock source select: 3 - INCLK */
#define MC__STOP               (0*0x10u)      /* Timer A mode control: 0 - Stop */
#define MC__UP                 (1*0x10u)      /* Timer A mode control: 1 - Up to CCR0 */
#define MC__CONTINUOUS         (2*0x10u)      /* Timer A mode control: 2 - Continuous up */
#define MC__CONTINOUS          (2*0x10u)      /* Legacy define */
#define MC__UPDOWN             (3*0x10u)      /* Timer A mode control: 3 - Up/Down */
#define ID__1                  (0*0x40u)      /* Timer A input divider: 0 - /1 */
#define ID__2                  (1*0x40u)      /* Timer A input divider: 1 - /2 */
#define ID__4                  (2*0x40u)      /* Timer A input divider: 2 - /4 */
#define ID__8                  (3*0x40u)      /* Timer A input divider: 3 - /8 */
#define TASSEL__TACLK          (0*0x100u)     /* Timer A clock source select: 0 - TACLK */
#define TASSEL__ACLK           (1*0x100u)     /* Timer A clock source select: 1 - ACLK  */
#define TASSEL__SMCLK          (2*0x100u)     /* Timer A clock source select: 2 - SMCLK */
#define TASSEL__INCLK          (3*0x100u)     /* Timer A clock source select: 3 - INCLK */

/* TAxCCTLx Control Bits */
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

/* TAxEX0 Control Bits */
#define TAIDEX0                (0x0001)       /* Timer A Input divider expansion Bit: 0 */
#define TAIDEX1                (0x0002)       /* Timer A Input divider expansion Bit: 1 */
#define TAIDEX2                (0x0004)       /* Timer A Input divider expansion Bit: 2 */

#define TAIDEX_0               (0*0x0001u)    /* Timer A Input divider expansion : /1 */
#define TAIDEX_1               (1*0x0001u)    /* Timer A Input divider expansion : /2 */
#define TAIDEX_2               (2*0x0001u)    /* Timer A Input divider expansion : /3 */
#define TAIDEX_3               (3*0x0001u)    /* Timer A Input divider expansion : /4 */
#define TAIDEX_4               (4*0x0001u)    /* Timer A Input divider expansion : /5 */
#define TAIDEX_5               (5*0x0001u)    /* Timer A Input divider expansion : /6 */
#define TAIDEX_6               (6*0x0001u)    /* Timer A Input divider expansion : /7 */
#define TAIDEX_7               (7*0x0001u)    /* Timer A Input divider expansion : /8 */

/* T0A3IV Definitions */
#define TA0IV_NONE             (0x0000)       /* No Interrupt pending */
#define TA0IV_TACCR1           (0x0002)       /* TA0CCR1_CCIFG */
#define TA0IV_TACCR2           (0x0004)       /* TA0CCR2_CCIFG */
#define TA0IV_3                (0x0006)       /* Reserved */
#define TA0IV_4                (0x0008)       /* Reserved */
#define TA0IV_5                (0x000A)       /* Reserved */
#define TA0IV_6                (0x000C)       /* Reserved */
#define TA0IV_TAIFG            (0x000E)       /* TA0IFG */

/* Legacy Defines */
#define TA0IV_TA0CCR1          (0x0002)       /* TA0CCR1_CCIFG */
#define TA0IV_TA0CCR2          (0x0004)       /* TA0CCR2_CCIFG */
#define TA0IV_TA0IFG           (0x000E)       /* TA0IFG */

/************************************************************
* Timer1_A3
************************************************************/
#define __MSP430_HAS_T1A3__                   /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_T1A3__ 0x0340
#define TIMER_A1_BASE          __MSP430_BASEADDRESS_T1A3__

SFR_16BIT(TA1CTL);                            /* Timer1_A3 Control */
SFR_16BIT(TA1CCTL0);                          /* Timer1_A3 Capture/Compare Control 0 */
SFR_16BIT(TA1CCTL1);                          /* Timer1_A3 Capture/Compare Control 1 */
SFR_16BIT(TA1CCTL2);                          /* Timer1_A3 Capture/Compare Control 2 */
SFR_16BIT(TA1R);                              /* Timer1_A3 */
SFR_16BIT(TA1CCR0);                           /* Timer1_A3 Capture/Compare 0 */
SFR_16BIT(TA1CCR1);                           /* Timer1_A3 Capture/Compare 1 */
SFR_16BIT(TA1CCR2);                           /* Timer1_A3 Capture/Compare 2 */
SFR_16BIT(TA1IV);                             /* Timer1_A3 Interrupt Vector Word */
SFR_16BIT(TA1EX0);                            /* Timer1_A3 Expansion Register 0 */

/* Bits are already defined within the Timer0_Ax */

/* TA1IV Definitions */
#define TA1IV_NONE             (0x0000)       /* No Interrupt pending */
#define TA1IV_TACCR1           (0x0002)       /* TA1CCR1_CCIFG */
#define TA1IV_TACCR2           (0x0004)       /* TA1CCR2_CCIFG */
#define TA1IV_3                (0x0006)       /* Reserved */
#define TA1IV_4                (0x0008)       /* Reserved */
#define TA1IV_5                (0x000A)       /* Reserved */
#define TA1IV_6                (0x000C)       /* Reserved */
#define TA1IV_TAIFG            (0x000E)       /* TA1IFG */

/* Legacy Defines */
#define TA1IV_TA1CCR1          (0x0002)       /* TA1CCR1_CCIFG */
#define TA1IV_TA1CCR2          (0x0004)       /* TA1CCR2_CCIFG */
#define TA1IV_TA1IFG           (0x000E)       /* TA1IFG */

/************************************************************
* USCI A0
************************************************************/
#define __MSP430_HAS_EUSCI_A0__                /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_EUSCI_A0__ 0x0500
#define EUSCI_A0_BASE          __MSP430_BASEADDRESS_EUSCI_A0__

SFR_16BIT(UCA0CTLW0);                         /* USCI A0 Control Word Register 0 */
SFR_8BIT(UCA0CTLW0_L);                        /* USCI A0 Control Word Register 0 */
SFR_8BIT(UCA0CTLW0_H);                        /* USCI A0 Control Word Register 0 */
#define UCA0CTL1               UCA0CTLW0_L    /* USCI A0 Control Register 1 */
#define UCA0CTL0               UCA0CTLW0_H    /* USCI A0 Control Register 0 */
SFR_16BIT(UCA0CTLW1);                         /* USCI A0 Control Word Register 1 */
SFR_8BIT(UCA0CTLW1_L);                        /* USCI A0 Control Word Register 1 */
SFR_8BIT(UCA0CTLW1_H);                        /* USCI A0 Control Word Register 1 */
SFR_16BIT(UCA0BRW);                           /* USCI A0 Baud Word Rate 0 */
SFR_8BIT(UCA0BRW_L);                          /* USCI A0 Baud Word Rate 0 */
SFR_8BIT(UCA0BRW_H);                          /* USCI A0 Baud Word Rate 0 */
#define UCA0BR0                UCA0BRW_L      /* USCI A0 Baud Rate 0 */
#define UCA0BR1                UCA0BRW_H      /* USCI A0 Baud Rate 1 */
SFR_16BIT(UCA0MCTLW);                         /* USCI A0 Modulation Control */
SFR_8BIT(UCA0MCTLW_L);                        /* USCI A0 Modulation Control */
SFR_8BIT(UCA0MCTLW_H);                        /* USCI A0 Modulation Control */
SFR_8BIT(UCA0STATW);                          /* USCI A0 Status Register */
SFR_16BIT(UCA0RXBUF);                         /* USCI A0 Receive Buffer */
SFR_8BIT(UCA0RXBUF_L);                        /* USCI A0 Receive Buffer */
SFR_8BIT(UCA0RXBUF_H);                        /* USCI A0 Receive Buffer */
SFR_16BIT(UCA0TXBUF);                         /* USCI A0 Transmit Buffer */
SFR_8BIT(UCA0TXBUF_L);                        /* USCI A0 Transmit Buffer */
SFR_8BIT(UCA0TXBUF_H);                        /* USCI A0 Transmit Buffer */
SFR_8BIT(UCA0ABCTL);                          /* USCI A0 LIN Control */
SFR_16BIT(UCA0IRCTL);                         /* USCI A0 IrDA Transmit Control */
SFR_8BIT(UCA0IRCTL_L);                        /* USCI A0 IrDA Transmit Control */
SFR_8BIT(UCA0IRCTL_H);                        /* USCI A0 IrDA Transmit Control */
#define UCA0IRTCTL             UCA0IRCTL_L    /* USCI A0 IrDA Transmit Control */
#define UCA0IRRCTL             UCA0IRCTL_H    /* USCI A0 IrDA Receive Control */
SFR_16BIT(UCA0IE);                            /* USCI A0 Interrupt Enable Register */
SFR_8BIT(UCA0IE_L);                           /* USCI A0 Interrupt Enable Register */
SFR_8BIT(UCA0IE_H);                           /* USCI A0 Interrupt Enable Register */
SFR_16BIT(UCA0IFG);                           /* USCI A0 Interrupt Flags Register */
SFR_8BIT(UCA0IFG_L);                          /* USCI A0 Interrupt Flags Register */
SFR_8BIT(UCA0IFG_H);                          /* USCI A0 Interrupt Flags Register */
SFR_16BIT(UCA0IV);                            /* USCI A0 Interrupt Vector Register */


/************************************************************
* USCI B0
************************************************************/
#define __MSP430_HAS_EUSCI_B0__                /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_EUSCI_B0__ 0x0540
#define EUSCI_B0_BASE          __MSP430_BASEADDRESS_EUSCI_B0__


SFR_16BIT(UCB0CTLW0);                         /* USCI B0 Control Word Register 0 */
SFR_8BIT(UCB0CTLW0_L);                        /* USCI B0 Control Word Register 0 */
SFR_8BIT(UCB0CTLW0_H);                        /* USCI B0 Control Word Register 0 */
#define UCB0CTL1               UCB0CTLW0_L    /* USCI B0 Control Register 1 */
#define UCB0CTL0               UCB0CTLW0_H    /* USCI B0 Control Register 0 */
SFR_16BIT(UCB0CTLW1);                         /* USCI B0 Control Word Register 1 */
SFR_8BIT(UCB0CTLW1_L);                        /* USCI B0 Control Word Register 1 */
SFR_8BIT(UCB0CTLW1_H);                        /* USCI B0 Control Word Register 1 */
SFR_16BIT(UCB0BRW);                           /* USCI B0 Baud Word Rate 0 */
SFR_8BIT(UCB0BRW_L);                          /* USCI B0 Baud Word Rate 0 */
SFR_8BIT(UCB0BRW_H);                          /* USCI B0 Baud Word Rate 0 */
#define UCB0BR0                UCB0BRW_L      /* USCI B0 Baud Rate 0 */
#define UCB0BR1                UCB0BRW_H      /* USCI B0 Baud Rate 1 */
SFR_16BIT(UCB0STATW);                         /* USCI B0 Status Word Register */
SFR_8BIT(UCB0STATW_L);                        /* USCI B0 Status Word Register */
SFR_8BIT(UCB0STATW_H);                        /* USCI B0 Status Word Register */
#define UCB0STAT               UCB0STATW_L    /* USCI B0 Status Register */
#define UCB0BCNT               UCB0STATW_H    /* USCI B0 Byte Counter Register */
SFR_16BIT(UCB0TBCNT);                         /* USCI B0 Byte Counter Threshold Register */
SFR_8BIT(UCB0TBCNT_L);                        /* USCI B0 Byte Counter Threshold Register */
SFR_8BIT(UCB0TBCNT_H);                        /* USCI B0 Byte Counter Threshold Register */
SFR_16BIT(UCB0RXBUF);                         /* USCI B0 Receive Buffer */
SFR_8BIT(UCB0RXBUF_L);                        /* USCI B0 Receive Buffer */
SFR_8BIT(UCB0RXBUF_H);                        /* USCI B0 Receive Buffer */
SFR_16BIT(UCB0TXBUF);                         /* USCI B0 Transmit Buffer */
SFR_8BIT(UCB0TXBUF_L);                        /* USCI B0 Transmit Buffer */
SFR_8BIT(UCB0TXBUF_H);                        /* USCI B0 Transmit Buffer */
SFR_16BIT(UCB0I2COA0);                        /* USCI B0 I2C Own Address 0 */
SFR_8BIT(UCB0I2COA0_L);                       /* USCI B0 I2C Own Address 0 */
SFR_8BIT(UCB0I2COA0_H);                       /* USCI B0 I2C Own Address 0 */
SFR_16BIT(UCB0I2COA1);                        /* USCI B0 I2C Own Address 1 */
SFR_8BIT(UCB0I2COA1_L);                       /* USCI B0 I2C Own Address 1 */
SFR_8BIT(UCB0I2COA1_H);                       /* USCI B0 I2C Own Address 1 */
SFR_16BIT(UCB0I2COA2);                        /* USCI B0 I2C Own Address 2 */
SFR_8BIT(UCB0I2COA2_L);                       /* USCI B0 I2C Own Address 2 */
SFR_8BIT(UCB0I2COA2_H);                       /* USCI B0 I2C Own Address 2 */
SFR_16BIT(UCB0I2COA3);                        /* USCI B0 I2C Own Address 3 */
SFR_8BIT(UCB0I2COA3_L);                       /* USCI B0 I2C Own Address 3 */
SFR_8BIT(UCB0I2COA3_H);                       /* USCI B0 I2C Own Address 3 */
SFR_16BIT(UCB0ADDRX);                         /* USCI B0 Received Address Register */
SFR_8BIT(UCB0ADDRX_L);                        /* USCI B0 Received Address Register */
SFR_8BIT(UCB0ADDRX_H);                        /* USCI B0 Received Address Register */
SFR_16BIT(UCB0ADDMASK);                       /* USCI B0 Address Mask Register */
SFR_8BIT(UCB0ADDMASK_L);                      /* USCI B0 Address Mask Register */
SFR_8BIT(UCB0ADDMASK_H);                      /* USCI B0 Address Mask Register */
SFR_16BIT(UCB0I2CSA);                         /* USCI B0 I2C Slave Address */
SFR_8BIT(UCB0I2CSA_L);                        /* USCI B0 I2C Slave Address */
SFR_8BIT(UCB0I2CSA_H);                        /* USCI B0 I2C Slave Address */
SFR_16BIT(UCB0IE);                            /* USCI B0 Interrupt Enable Register */
SFR_8BIT(UCB0IE_L);                           /* USCI B0 Interrupt Enable Register */
SFR_8BIT(UCB0IE_H);                           /* USCI B0 Interrupt Enable Register */
SFR_16BIT(UCB0IFG);                           /* USCI B0 Interrupt Flags Register */
SFR_8BIT(UCB0IFG_L);                          /* USCI B0 Interrupt Flags Register */
SFR_8BIT(UCB0IFG_H);                          /* USCI B0 Interrupt Flags Register */
SFR_16BIT(UCB0IV);                            /* USCI B0 Interrupt Vector Register */

// UCAxCTLW0 UART-Mode Control Bits
#define UCPEN                  (0x8000)       /* Async. Mode: Parity enable */
#define UCPAR                  (0x4000)       /* Async. Mode: Parity     0:odd / 1:even */
#define UCMSB                  (0x2000)       /* Async. Mode: MSB first  0:LSB / 1:MSB */
#define UC7BIT                 (0x1000)       /* Async. Mode: Data Bits  0:8-bits / 1:7-bits */
#define UCSPB                  (0x0800)       /* Async. Mode: Stop Bits  0:one / 1: two */
#define UCMODE1                (0x0400)       /* Async. Mode: USCI Mode 1 */
#define UCMODE0                (0x0200)       /* Async. Mode: USCI Mode 0 */
#define UCSYNC                 (0x0100)       /* Sync-Mode  0:UART-Mode / 1:SPI-Mode */
#define UCSSEL1                (0x0080)       /* USCI 0 Clock Source Select 1 */
#define UCSSEL0                (0x0040)       /* USCI 0 Clock Source Select 0 */
#define UCRXEIE                (0x0020)       /* RX Error interrupt enable */
#define UCBRKIE                (0x0010)       /* Break interrupt enable */
#define UCDORM                 (0x0008)       /* Dormant (Sleep) Mode */
#define UCTXADDR               (0x0004)       /* Send next Data as Address */
#define UCTXBRK                (0x0002)       /* Send next Data as Break */
#define UCSWRST                (0x0001)       /* USCI Software Reset */

// UCAxCTLW0 UART-Mode Control Bits
#define UCSSEL1_L              (0x0080)       /* USCI 0 Clock Source Select 1 */
#define UCSSEL0_L              (0x0040)       /* USCI 0 Clock Source Select 0 */
#define UCRXEIE_L              (0x0020)       /* RX Error interrupt enable */
#define UCBRKIE_L              (0x0010)       /* Break interrupt enable */
#define UCDORM_L               (0x0008)       /* Dormant (Sleep) Mode */
#define UCTXADDR_L             (0x0004)       /* Send next Data as Address */
#define UCTXBRK_L              (0x0002)       /* Send next Data as Break */
#define UCSWRST_L              (0x0001)       /* USCI Software Reset */

// UCAxCTLW0 UART-Mode Control Bits
#define UCPEN_H                (0x0080)       /* Async. Mode: Parity enable */
#define UCPAR_H                (0x0040)       /* Async. Mode: Parity     0:odd / 1:even */
#define UCMSB_H                (0x0020)       /* Async. Mode: MSB first  0:LSB / 1:MSB */
#define UC7BIT_H               (0x0010)       /* Async. Mode: Data Bits  0:8-bits / 1:7-bits */
#define UCSPB_H                (0x0008)       /* Async. Mode: Stop Bits  0:one / 1: two */
#define UCMODE1_H              (0x0004)       /* Async. Mode: USCI Mode 1 */
#define UCMODE0_H              (0x0002)       /* Async. Mode: USCI Mode 0 */
#define UCSYNC_H               (0x0001)       /* Sync-Mode  0:UART-Mode / 1:SPI-Mode */

// UCxxCTLW0 SPI-Mode Control Bits
#define UCCKPH                 (0x8000)       /* Sync. Mode: Clock Phase */
#define UCCKPL                 (0x4000)       /* Sync. Mode: Clock Polarity */
#define UCMST                  (0x0800)       /* Sync. Mode: Master Select */
//#define res               (0x0020)    /* reserved */
//#define res               (0x0010)    /* reserved */
//#define res               (0x0008)    /* reserved */
//#define res               (0x0004)    /* reserved */
#define UCSTEM                 (0x0002)       /* USCI STE Mode */

// UCBxCTLW0 I2C-Mode Control Bits
#define UCA10                  (0x8000)       /* 10-bit Address Mode */
#define UCSLA10                (0x4000)       /* 10-bit Slave Address Mode */
#define UCMM                   (0x2000)       /* Multi-Master Environment */
//#define res               (0x1000)    /* reserved */
//#define res               (0x0100)    /* reserved */
#define UCTXACK                (0x0020)       /* Transmit ACK */
#define UCTR                   (0x0010)       /* Transmit/Receive Select/Flag */
#define UCTXNACK               (0x0008)       /* Transmit NACK */
#define UCTXSTP                (0x0004)       /* Transmit STOP */
#define UCTXSTT                (0x0002)       /* Transmit START */

// UCBxCTLW0 I2C-Mode Control Bits
//#define res               (0x1000)    /* reserved */
//#define res               (0x0100)    /* reserved */
#define UCTXACK_L              (0x0020)       /* Transmit ACK */
#define UCTR_L                 (0x0010)       /* Transmit/Receive Select/Flag */
#define UCTXNACK_L             (0x0008)       /* Transmit NACK */
#define UCTXSTP_L              (0x0004)       /* Transmit STOP */
#define UCTXSTT_L              (0x0002)       /* Transmit START */

// UCBxCTLW0 I2C-Mode Control Bits
#define UCA10_H                (0x0080)       /* 10-bit Address Mode */
#define UCSLA10_H              (0x0040)       /* 10-bit Slave Address Mode */
#define UCMM_H                 (0x0020)       /* Multi-Master Environment */
//#define res               (0x1000)    /* reserved */
//#define res               (0x0100)    /* reserved */

#define UCMODE_0               (0x0000)       /* Sync. Mode: USCI Mode: 0 */
#define UCMODE_1               (0x0200)       /* Sync. Mode: USCI Mode: 1 */
#define UCMODE_2               (0x0400)       /* Sync. Mode: USCI Mode: 2 */
#define UCMODE_3               (0x0600)       /* Sync. Mode: USCI Mode: 3 */

#define UCSSEL_0               (0x0000)       /* USCI 0 Clock Source: 0 */
#define UCSSEL_1               (0x0040)       /* USCI 0 Clock Source: 1 */
#define UCSSEL_2               (0x0080)       /* USCI 0 Clock Source: 2 */
#define UCSSEL_3               (0x00C0)       /* USCI 0 Clock Source: 3 */
#define UCSSEL__UCLK           (0x0000)       /* USCI 0 Clock Source: UCLK */
#define UCSSEL__MODCLK         (0x0040)       /* USCI 0 Clock Source: MODCLK */
#define UCSSEL__SMCLK          (0x0080)       /* USCI 0 Clock Source: SMCLK */

// UCAxCTLW1 UART-Mode Control Bits
#define UCGLIT1                (0x0002)       /* USCI Deglitch Time Bit 1 */
#define UCGLIT0                (0x0001)       /* USCI Deglitch Time Bit 0 */

// UCAxCTLW1 UART-Mode Control Bits
#define UCGLIT1_L              (0x0002)       /* USCI Deglitch Time Bit 1 */
#define UCGLIT0_L              (0x0001)       /* USCI Deglitch Time Bit 0 */

// UCBxCTLW1 I2C-Mode Control Bits
#define UCETXINT               (0x0100)       /* USCI Early UCTXIFG0 */
#define UCCLTO1                (0x0080)       /* USCI Clock low timeout Bit: 1 */
#define UCCLTO0                (0x0040)       /* USCI Clock low timeout Bit: 0 */
#define UCSTPNACK              (0x0020)       /* USCI Acknowledge Stop last byte */
#define UCSWACK                (0x0010)       /* USCI Software controlled ACK */
#define UCASTP1                (0x0008)       /* USCI Automatic Stop condition generation Bit: 1 */
#define UCASTP0                (0x0004)       /* USCI Automatic Stop condition generation Bit: 0 */
#define UCGLIT1                (0x0002)       /* USCI Deglitch time Bit: 1 */
#define UCGLIT0                (0x0001)       /* USCI Deglitch time Bit: 0 */

// UCBxCTLW1 I2C-Mode Control Bits
#define UCCLTO1_L              (0x0080)       /* USCI Clock low timeout Bit: 1 */
#define UCCLTO0_L              (0x0040)       /* USCI Clock low timeout Bit: 0 */
#define UCSTPNACK_L            (0x0020)       /* USCI Acknowledge Stop last byte */
#define UCSWACK_L              (0x0010)       /* USCI Software controlled ACK */
#define UCASTP1_L              (0x0008)       /* USCI Automatic Stop condition generation Bit: 1 */
#define UCASTP0_L              (0x0004)       /* USCI Automatic Stop condition generation Bit: 0 */
#define UCGLIT1_L              (0x0002)       /* USCI Deglitch time Bit: 1 */
#define UCGLIT0_L              (0x0001)       /* USCI Deglitch time Bit: 0 */

// UCBxCTLW1 I2C-Mode Control Bits
#define UCETXINT_H             (0x0001)       /* USCI Early UCTXIFG0 */

#define UCGLIT_0               (0x0000)       /* USCI Deglitch time: 0 */
#define UCGLIT_1               (0x0001)       /* USCI Deglitch time: 1 */
#define UCGLIT_2               (0x0002)       /* USCI Deglitch time: 2 */
#define UCGLIT_3               (0x0003)       /* USCI Deglitch time: 3 */

#define UCASTP_0               (0x0000)       /* USCI Automatic Stop condition generation: 0 */
#define UCASTP_1               (0x0004)       /* USCI Automatic Stop condition generation: 1 */
#define UCASTP_2               (0x0008)       /* USCI Automatic Stop condition generation: 2 */
#define UCASTP_3               (0x000C)       /* USCI Automatic Stop condition generation: 3 */

#define UCCLTO_0               (0x0000)       /* USCI Clock low timeout: 0 */
#define UCCLTO_1               (0x0040)       /* USCI Clock low timeout: 1 */
#define UCCLTO_2               (0x0080)       /* USCI Clock low timeout: 2 */
#define UCCLTO_3               (0x00C0)       /* USCI Clock low timeout: 3 */

/* UCAxMCTLW Control Bits */
#define UCBRS7                 (0x8000)       /* USCI Second Stage Modulation Select 7 */
#define UCBRS6                 (0x4000)       /* USCI Second Stage Modulation Select 6 */
#define UCBRS5                 (0x2000)       /* USCI Second Stage Modulation Select 5 */
#define UCBRS4                 (0x1000)       /* USCI Second Stage Modulation Select 4 */
#define UCBRS3                 (0x0800)       /* USCI Second Stage Modulation Select 3 */
#define UCBRS2                 (0x0400)       /* USCI Second Stage Modulation Select 2 */
#define UCBRS1                 (0x0200)       /* USCI Second Stage Modulation Select 1 */
#define UCBRS0                 (0x0100)       /* USCI Second Stage Modulation Select 0 */
#define UCBRF3                 (0x0080)       /* USCI First Stage Modulation Select 3 */
#define UCBRF2                 (0x0040)       /* USCI First Stage Modulation Select 2 */
#define UCBRF1                 (0x0020)       /* USCI First Stage Modulation Select 1 */
#define UCBRF0                 (0x0010)       /* USCI First Stage Modulation Select 0 */
#define UCOS16                 (0x0001)       /* USCI 16-times Oversampling enable */

/* UCAxMCTLW Control Bits */
#define UCBRF3_L               (0x0080)       /* USCI First Stage Modulation Select 3 */
#define UCBRF2_L               (0x0040)       /* USCI First Stage Modulation Select 2 */
#define UCBRF1_L               (0x0020)       /* USCI First Stage Modulation Select 1 */
#define UCBRF0_L               (0x0010)       /* USCI First Stage Modulation Select 0 */
#define UCOS16_L               (0x0001)       /* USCI 16-times Oversampling enable */

/* UCAxMCTLW Control Bits */
#define UCBRS7_H               (0x0080)       /* USCI Second Stage Modulation Select 7 */
#define UCBRS6_H               (0x0040)       /* USCI Second Stage Modulation Select 6 */
#define UCBRS5_H               (0x0020)       /* USCI Second Stage Modulation Select 5 */
#define UCBRS4_H               (0x0010)       /* USCI Second Stage Modulation Select 4 */
#define UCBRS3_H               (0x0008)       /* USCI Second Stage Modulation Select 3 */
#define UCBRS2_H               (0x0004)       /* USCI Second Stage Modulation Select 2 */
#define UCBRS1_H               (0x0002)       /* USCI Second Stage Modulation Select 1 */
#define UCBRS0_H               (0x0001)       /* USCI Second Stage Modulation Select 0 */

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

/* UCAxSTATW Control Bits */
#define UCLISTEN               (0x0080)       /* USCI Listen mode */
#define UCFE                   (0x0040)       /* USCI Frame Error Flag */
#define UCOE                   (0x0020)       /* USCI Overrun Error Flag */
#define UCPE                   (0x0010)       /* USCI Parity Error Flag */
#define UCBRK                  (0x0008)       /* USCI Break received */
#define UCRXERR                (0x0004)       /* USCI RX Error Flag */
#define UCADDR                 (0x0002)       /* USCI Address received Flag */
#define UCBUSY                 (0x0001)       /* USCI Busy Flag */
#define UCIDLE                 (0x0002)       /* USCI Idle line detected Flag */

/* UCBxSTATW I2C Control Bits */
#define UCBCNT7                (0x8000)       /* USCI Byte Counter Bit 7 */
#define UCBCNT6                (0x4000)       /* USCI Byte Counter Bit 6 */
#define UCBCNT5                (0x2000)       /* USCI Byte Counter Bit 5 */
#define UCBCNT4                (0x1000)       /* USCI Byte Counter Bit 4 */
#define UCBCNT3                (0x0800)       /* USCI Byte Counter Bit 3 */
#define UCBCNT2                (0x0400)       /* USCI Byte Counter Bit 2 */
#define UCBCNT1                (0x0200)       /* USCI Byte Counter Bit 1 */
#define UCBCNT0                (0x0100)       /* USCI Byte Counter Bit 0 */
#define UCSCLLOW               (0x0040)       /* SCL low */
#define UCGC                   (0x0020)       /* General Call address received Flag */
#define UCBBUSY                (0x0010)       /* Bus Busy Flag */

/* UCBxTBCNT I2C Control Bits */
#define UCTBCNT7               (0x0080)       /* USCI Byte Counter Bit 7 */
#define UCTBCNT6               (0x0040)       /* USCI Byte Counter Bit 6 */
#define UCTBCNT5               (0x0020)       /* USCI Byte Counter Bit 5 */
#define UCTBCNT4               (0x0010)       /* USCI Byte Counter Bit 4 */
#define UCTBCNT3               (0x0008)       /* USCI Byte Counter Bit 3 */
#define UCTBCNT2               (0x0004)       /* USCI Byte Counter Bit 2 */
#define UCTBCNT1               (0x0002)       /* USCI Byte Counter Bit 1 */
#define UCTBCNT0               (0x0001)       /* USCI Byte Counter Bit 0 */

/* UCAxIRCTL Control Bits */
#define UCIRRXFL5              (0x8000)       /* IRDA Receive Filter Length 5 */
#define UCIRRXFL4              (0x4000)       /* IRDA Receive Filter Length 4 */
#define UCIRRXFL3              (0x2000)       /* IRDA Receive Filter Length 3 */
#define UCIRRXFL2              (0x1000)       /* IRDA Receive Filter Length 2 */
#define UCIRRXFL1              (0x0800)       /* IRDA Receive Filter Length 1 */
#define UCIRRXFL0              (0x0400)       /* IRDA Receive Filter Length 0 */
#define UCIRRXPL               (0x0200)       /* IRDA Receive Input Polarity */
#define UCIRRXFE               (0x0100)       /* IRDA Receive Filter enable */
#define UCIRTXPL5              (0x0080)       /* IRDA Transmit Pulse Length 5 */
#define UCIRTXPL4              (0x0040)       /* IRDA Transmit Pulse Length 4 */
#define UCIRTXPL3              (0x0020)       /* IRDA Transmit Pulse Length 3 */
#define UCIRTXPL2              (0x0010)       /* IRDA Transmit Pulse Length 2 */
#define UCIRTXPL1              (0x0008)       /* IRDA Transmit Pulse Length 1 */
#define UCIRTXPL0              (0x0004)       /* IRDA Transmit Pulse Length 0 */
#define UCIRTXCLK              (0x0002)       /* IRDA Transmit Pulse Clock Select */
#define UCIREN                 (0x0001)       /* IRDA Encoder/Decoder enable */

/* UCAxIRCTL Control Bits */
#define UCIRTXPL5_L            (0x0080)       /* IRDA Transmit Pulse Length 5 */
#define UCIRTXPL4_L            (0x0040)       /* IRDA Transmit Pulse Length 4 */
#define UCIRTXPL3_L            (0x0020)       /* IRDA Transmit Pulse Length 3 */
#define UCIRTXPL2_L            (0x0010)       /* IRDA Transmit Pulse Length 2 */
#define UCIRTXPL1_L            (0x0008)       /* IRDA Transmit Pulse Length 1 */
#define UCIRTXPL0_L            (0x0004)       /* IRDA Transmit Pulse Length 0 */
#define UCIRTXCLK_L            (0x0002)       /* IRDA Transmit Pulse Clock Select */
#define UCIREN_L               (0x0001)       /* IRDA Encoder/Decoder enable */

/* UCAxIRCTL Control Bits */
#define UCIRRXFL5_H            (0x0080)       /* IRDA Receive Filter Length 5 */
#define UCIRRXFL4_H            (0x0040)       /* IRDA Receive Filter Length 4 */
#define UCIRRXFL3_H            (0x0020)       /* IRDA Receive Filter Length 3 */
#define UCIRRXFL2_H            (0x0010)       /* IRDA Receive Filter Length 2 */
#define UCIRRXFL1_H            (0x0008)       /* IRDA Receive Filter Length 1 */
#define UCIRRXFL0_H            (0x0004)       /* IRDA Receive Filter Length 0 */
#define UCIRRXPL_H             (0x0002)       /* IRDA Receive Input Polarity */
#define UCIRRXFE_H             (0x0001)       /* IRDA Receive Filter enable */

/* UCAxABCTL Control Bits */
//#define res               (0x80)    /* reserved */
//#define res               (0x40)    /* reserved */
#define UCDELIM1               (0x20)         /* Break Sync Delimiter 1 */
#define UCDELIM0               (0x10)         /* Break Sync Delimiter 0 */
#define UCSTOE                 (0x08)         /* Sync-Field Timeout error */
#define UCBTOE                 (0x04)         /* Break Timeout error */
//#define res               (0x02)    /* reserved */
#define UCABDEN                (0x01)         /* Auto Baud Rate detect enable */

/* UCBxI2COA0 Control Bits */
#define UCGCEN                 (0x8000)       /* I2C General Call enable */
#define UCOAEN                 (0x0400)       /* I2C Own Address enable */
#define UCOA9                  (0x0200)       /* I2C Own Address Bit 9 */
#define UCOA8                  (0x0100)       /* I2C Own Address Bit 8 */
#define UCOA7                  (0x0080)       /* I2C Own Address Bit 7 */
#define UCOA6                  (0x0040)       /* I2C Own Address Bit 6 */
#define UCOA5                  (0x0020)       /* I2C Own Address Bit 5 */
#define UCOA4                  (0x0010)       /* I2C Own Address Bit 4 */
#define UCOA3                  (0x0008)       /* I2C Own Address Bit 3 */
#define UCOA2                  (0x0004)       /* I2C Own Address Bit 2 */
#define UCOA1                  (0x0002)       /* I2C Own Address Bit 1 */
#define UCOA0                  (0x0001)       /* I2C Own Address Bit 0 */

/* UCBxI2COA0 Control Bits */
#define UCOA7_L                (0x0080)       /* I2C Own Address Bit 7 */
#define UCOA6_L                (0x0040)       /* I2C Own Address Bit 6 */
#define UCOA5_L                (0x0020)       /* I2C Own Address Bit 5 */
#define UCOA4_L                (0x0010)       /* I2C Own Address Bit 4 */
#define UCOA3_L                (0x0008)       /* I2C Own Address Bit 3 */
#define UCOA2_L                (0x0004)       /* I2C Own Address Bit 2 */
#define UCOA1_L                (0x0002)       /* I2C Own Address Bit 1 */
#define UCOA0_L                (0x0001)       /* I2C Own Address Bit 0 */

/* UCBxI2COA0 Control Bits */
#define UCGCEN_H               (0x0080)       /* I2C General Call enable */
#define UCOAEN_H               (0x0004)       /* I2C Own Address enable */
#define UCOA9_H                (0x0002)       /* I2C Own Address Bit 9 */
#define UCOA8_H                (0x0001)       /* I2C Own Address Bit 8 */

/* UCBxI2COAx Control Bits */
#define UCOAEN                 (0x0400)       /* I2C Own Address enable */
#define UCOA9                  (0x0200)       /* I2C Own Address Bit 9 */
#define UCOA8                  (0x0100)       /* I2C Own Address Bit 8 */
#define UCOA7                  (0x0080)       /* I2C Own Address Bit 7 */
#define UCOA6                  (0x0040)       /* I2C Own Address Bit 6 */
#define UCOA5                  (0x0020)       /* I2C Own Address Bit 5 */
#define UCOA4                  (0x0010)       /* I2C Own Address Bit 4 */
#define UCOA3                  (0x0008)       /* I2C Own Address Bit 3 */
#define UCOA2                  (0x0004)       /* I2C Own Address Bit 2 */
#define UCOA1                  (0x0002)       /* I2C Own Address Bit 1 */
#define UCOA0                  (0x0001)       /* I2C Own Address Bit 0 */

/* UCBxI2COAx Control Bits */
#define UCOA7_L                (0x0080)       /* I2C Own Address Bit 7 */
#define UCOA6_L                (0x0040)       /* I2C Own Address Bit 6 */
#define UCOA5_L                (0x0020)       /* I2C Own Address Bit 5 */
#define UCOA4_L                (0x0010)       /* I2C Own Address Bit 4 */
#define UCOA3_L                (0x0008)       /* I2C Own Address Bit 3 */
#define UCOA2_L                (0x0004)       /* I2C Own Address Bit 2 */
#define UCOA1_L                (0x0002)       /* I2C Own Address Bit 1 */
#define UCOA0_L                (0x0001)       /* I2C Own Address Bit 0 */

/* UCBxI2COAx Control Bits */
#define UCOAEN_H               (0x0004)       /* I2C Own Address enable */
#define UCOA9_H                (0x0002)       /* I2C Own Address Bit 9 */
#define UCOA8_H                (0x0001)       /* I2C Own Address Bit 8 */

/* UCBxADDRX Control Bits */
#define UCADDRX9               (0x0200)       /* I2C Receive Address Bit 9 */
#define UCADDRX8               (0x0100)       /* I2C Receive Address Bit 8 */
#define UCADDRX7               (0x0080)       /* I2C Receive Address Bit 7 */
#define UCADDRX6               (0x0040)       /* I2C Receive Address Bit 6 */
#define UCADDRX5               (0x0020)       /* I2C Receive Address Bit 5 */
#define UCADDRX4               (0x0010)       /* I2C Receive Address Bit 4 */
#define UCADDRX3               (0x0008)       /* I2C Receive Address Bit 3 */
#define UCADDRX2               (0x0004)       /* I2C Receive Address Bit 2 */
#define UCADDRX1               (0x0002)       /* I2C Receive Address Bit 1 */
#define UCADDRX0               (0x0001)       /* I2C Receive Address Bit 0 */

/* UCBxADDRX Control Bits */
#define UCADDRX7_L             (0x0080)       /* I2C Receive Address Bit 7 */
#define UCADDRX6_L             (0x0040)       /* I2C Receive Address Bit 6 */
#define UCADDRX5_L             (0x0020)       /* I2C Receive Address Bit 5 */
#define UCADDRX4_L             (0x0010)       /* I2C Receive Address Bit 4 */
#define UCADDRX3_L             (0x0008)       /* I2C Receive Address Bit 3 */
#define UCADDRX2_L             (0x0004)       /* I2C Receive Address Bit 2 */
#define UCADDRX1_L             (0x0002)       /* I2C Receive Address Bit 1 */
#define UCADDRX0_L             (0x0001)       /* I2C Receive Address Bit 0 */

/* UCBxADDRX Control Bits */
#define UCADDRX9_H             (0x0002)       /* I2C Receive Address Bit 9 */
#define UCADDRX8_H             (0x0001)       /* I2C Receive Address Bit 8 */

/* UCBxADDMASK Control Bits */
#define UCADDMASK9             (0x0200)       /* I2C Address Mask Bit 9 */
#define UCADDMASK8             (0x0100)       /* I2C Address Mask Bit 8 */
#define UCADDMASK7             (0x0080)       /* I2C Address Mask Bit 7 */
#define UCADDMASK6             (0x0040)       /* I2C Address Mask Bit 6 */
#define UCADDMASK5             (0x0020)       /* I2C Address Mask Bit 5 */
#define UCADDMASK4             (0x0010)       /* I2C Address Mask Bit 4 */
#define UCADDMASK3             (0x0008)       /* I2C Address Mask Bit 3 */
#define UCADDMASK2             (0x0004)       /* I2C Address Mask Bit 2 */
#define UCADDMASK1             (0x0002)       /* I2C Address Mask Bit 1 */
#define UCADDMASK0             (0x0001)       /* I2C Address Mask Bit 0 */

/* UCBxADDMASK Control Bits */
#define UCADDMASK7_L           (0x0080)       /* I2C Address Mask Bit 7 */
#define UCADDMASK6_L           (0x0040)       /* I2C Address Mask Bit 6 */
#define UCADDMASK5_L           (0x0020)       /* I2C Address Mask Bit 5 */
#define UCADDMASK4_L           (0x0010)       /* I2C Address Mask Bit 4 */
#define UCADDMASK3_L           (0x0008)       /* I2C Address Mask Bit 3 */
#define UCADDMASK2_L           (0x0004)       /* I2C Address Mask Bit 2 */
#define UCADDMASK1_L           (0x0002)       /* I2C Address Mask Bit 1 */
#define UCADDMASK0_L           (0x0001)       /* I2C Address Mask Bit 0 */

/* UCBxADDMASK Control Bits */
#define UCADDMASK9_H           (0x0002)       /* I2C Address Mask Bit 9 */
#define UCADDMASK8_H           (0x0001)       /* I2C Address Mask Bit 8 */

/* UCBxI2CSA Control Bits */
#define UCSA9                  (0x0200)       /* I2C Slave Address Bit 9 */
#define UCSA8                  (0x0100)       /* I2C Slave Address Bit 8 */
#define UCSA7                  (0x0080)       /* I2C Slave Address Bit 7 */
#define UCSA6                  (0x0040)       /* I2C Slave Address Bit 6 */
#define UCSA5                  (0x0020)       /* I2C Slave Address Bit 5 */
#define UCSA4                  (0x0010)       /* I2C Slave Address Bit 4 */
#define UCSA3                  (0x0008)       /* I2C Slave Address Bit 3 */
#define UCSA2                  (0x0004)       /* I2C Slave Address Bit 2 */
#define UCSA1                  (0x0002)       /* I2C Slave Address Bit 1 */
#define UCSA0                  (0x0001)       /* I2C Slave Address Bit 0 */

/* UCBxI2CSA Control Bits */
#define UCSA7_L                (0x0080)       /* I2C Slave Address Bit 7 */
#define UCSA6_L                (0x0040)       /* I2C Slave Address Bit 6 */
#define UCSA5_L                (0x0020)       /* I2C Slave Address Bit 5 */
#define UCSA4_L                (0x0010)       /* I2C Slave Address Bit 4 */
#define UCSA3_L                (0x0008)       /* I2C Slave Address Bit 3 */
#define UCSA2_L                (0x0004)       /* I2C Slave Address Bit 2 */
#define UCSA1_L                (0x0002)       /* I2C Slave Address Bit 1 */
#define UCSA0_L                (0x0001)       /* I2C Slave Address Bit 0 */

/* UCBxI2CSA Control Bits */
#define UCSA9_H                (0x0002)       /* I2C Slave Address Bit 9 */
#define UCSA8_H                (0x0001)       /* I2C Slave Address Bit 8 */

/* UCAxIE UART Control Bits */
#define UCTXCPTIE              (0x0008)       /* UART Transmit Complete Interrupt Enable */
#define UCSTTIE                (0x0004)       /* UART Start Bit Interrupt Enalble */
#define UCTXIE                 (0x0002)       /* UART Transmit Interrupt Enable */
#define UCRXIE                 (0x0001)       /* UART Receive Interrupt Enable */

/* UCAxIE/UCBxIE SPI Control Bits */

/* UCBxIE I2C Control Bits */
#define UCBIT9IE               (0x4000)       /* I2C Bit 9 Position Interrupt Enable 3 */
#define UCTXIE3                (0x2000)       /* I2C Transmit Interrupt Enable 3 */
#define UCRXIE3                (0x1000)       /* I2C Receive Interrupt Enable 3 */
#define UCTXIE2                (0x0800)       /* I2C Transmit Interrupt Enable 2 */
#define UCRXIE2                (0x0400)       /* I2C Receive Interrupt Enable 2 */
#define UCTXIE1                (0x0200)       /* I2C Transmit Interrupt Enable 1 */
#define UCRXIE1                (0x0100)       /* I2C Receive Interrupt Enable 1 */
#define UCCLTOIE               (0x0080)       /* I2C Clock Low Timeout interrupt enable */
#define UCBCNTIE               (0x0040)       /* I2C Automatic stop assertion interrupt enable */
#define UCNACKIE               (0x0020)       /* I2C NACK Condition interrupt enable */
#define UCALIE                 (0x0010)       /* I2C Arbitration Lost interrupt enable */
#define UCSTPIE                (0x0008)       /* I2C STOP Condition interrupt enable */
#define UCSTTIE                (0x0004)       /* I2C START Condition interrupt enable */
#define UCTXIE0                (0x0002)       /* I2C Transmit Interrupt Enable 0 */
#define UCRXIE0                (0x0001)       /* I2C Receive Interrupt Enable 0 */

/* UCAxIFG UART Control Bits */
#define UCTXCPTIFG             (0x0008)       /* UART Transmit Complete Interrupt Flag */
#define UCSTTIFG               (0x0004)       /* UART Start Bit Interrupt Flag */
#define UCTXIFG                (0x0002)       /* UART Transmit Interrupt Flag */
#define UCRXIFG                (0x0001)       /* UART Receive Interrupt Flag */

/* UCAxIFG/UCBxIFG SPI Control Bits */
#define UCTXIFG                (0x0002)       /* SPI Transmit Interrupt Flag */
#define UCRXIFG                (0x0001)       /* SPI Receive Interrupt Flag */

/* UCBxIFG Control Bits */
#define UCBIT9IFG              (0x4000)       /* I2C Bit 9 Possition Interrupt Flag 3 */
#define UCTXIFG3               (0x2000)       /* I2C Transmit Interrupt Flag 3 */
#define UCRXIFG3               (0x1000)       /* I2C Receive Interrupt Flag 3 */
#define UCTXIFG2               (0x0800)       /* I2C Transmit Interrupt Flag 2 */
#define UCRXIFG2               (0x0400)       /* I2C Receive Interrupt Flag 2 */
#define UCTXIFG1               (0x0200)       /* I2C Transmit Interrupt Flag 1 */
#define UCRXIFG1               (0x0100)       /* I2C Receive Interrupt Flag 1 */
#define UCCLTOIFG              (0x0080)       /* I2C Clock low Timeout interrupt Flag */
#define UCBCNTIFG              (0x0040)       /* I2C Byte counter interrupt flag */
#define UCNACKIFG              (0x0020)       /* I2C NACK Condition interrupt Flag */
#define UCALIFG                (0x0010)       /* I2C Arbitration Lost interrupt Flag */
#define UCSTPIFG               (0x0008)       /* I2C STOP Condition interrupt Flag */
#define UCSTTIFG               (0x0004)       /* I2C START Condition interrupt Flag */
#define UCTXIFG0               (0x0002)       /* I2C Transmit Interrupt Flag 0 */
#define UCRXIFG0               (0x0001)       /* I2C Receive Interrupt Flag 0 */

/* USCI Interrupt Vector UART Definitions */
#define USCI_NONE              (0x0000)       /* No Interrupt pending */
#define USCI_UART_UCRXIFG      (0x0002)       /* Interrupt Vector: UCRXIFG */
#define USCI_UART_UCTXIFG      (0x0004)       /* Interrupt Vector: UCTXIFG */
#define USCI_UART_UCSTTIFG     (0x0006)       /* Interrupt Vector: UCSTTIFG */
#define USCI_UART_UCTXCPTIFG   (0x0008)       /* Interrupt Vector: UCTXCPTIFG */

/* USCI Interrupt Vector SPI Definitions */
#define USCI_SPI_UCRXIFG       (0x0002)       /* Interrupt Vector: UCRXIFG */
#define USCI_SPI_UCTXIFG       (0x0004)       /* Interrupt Vector: UCTXIFG */

/* USCI Interrupt Vector I2C Definitions */
#define USCI_I2C_UCALIFG       (0x0002)       /* Interrupt Vector: I2C Mode: UCALIFG */
#define USCI_I2C_UCNACKIFG     (0x0004)       /* Interrupt Vector: I2C Mode: UCNACKIFG */
#define USCI_I2C_UCSTTIFG      (0x0006)       /* Interrupt Vector: I2C Mode: UCSTTIFG*/
#define USCI_I2C_UCSTPIFG      (0x0008)       /* Interrupt Vector: I2C Mode: UCSTPIFG*/
#define USCI_I2C_UCRXIFG3      (0x000A)       /* Interrupt Vector: I2C Mode: UCRXIFG3 */
#define USCI_I2C_UCTXIFG3      (0x000C)       /* Interrupt Vector: I2C Mode: UCTXIFG3 */
#define USCI_I2C_UCRXIFG2      (0x000E)       /* Interrupt Vector: I2C Mode: UCRXIFG2 */
#define USCI_I2C_UCTXIFG2      (0x0010)       /* Interrupt Vector: I2C Mode: UCTXIFG2 */
#define USCI_I2C_UCRXIFG1      (0x0012)       /* Interrupt Vector: I2C Mode: UCRXIFG1 */
#define USCI_I2C_UCTXIFG1      (0x0014)       /* Interrupt Vector: I2C Mode: UCTXIFG1 */
#define USCI_I2C_UCRXIFG0      (0x0016)       /* Interrupt Vector: I2C Mode: UCRXIFG0 */
#define USCI_I2C_UCTXIFG0      (0x0018)       /* Interrupt Vector: I2C Mode: UCTXIFG0 */
#define USCI_I2C_UCBCNTIFG     (0x001A)       /* Interrupt Vector: I2C Mode: UCBCNTIFG */
#define USCI_I2C_UCCLTOIFG     (0x001C)       /* Interrupt Vector: I2C Mode: UCCLTOIFG */
#define USCI_I2C_UCBIT9IFG     (0x001E)       /* Interrupt Vector: I2C Mode: UCBIT9IFG */

/************************************************************
* WATCHDOG TIMER A
************************************************************/
#define __MSP430_HAS_WDT_A__                  /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_WDT_A__ 0x01CC
#define WDT_A_BASE             __MSP430_BASEADDRESS_WDT_A__

SFR_16BIT(WDTCTL);                            /* Watchdog Timer Control */
SFR_8BIT(WDTCTL_L);                           /* Watchdog Timer Control */
SFR_8BIT(WDTCTL_H);                           /* Watchdog Timer Control */
/* The bit names have been prefixed with "WDT" */
/* WDTCTL Control Bits */
#define WDTIS0                 (0x0001)       /* WDT - Timer Interval Select 0 */
#define WDTIS1                 (0x0002)       /* WDT - Timer Interval Select 1 */
#define WDTIS2                 (0x0004)       /* WDT - Timer Interval Select 2 */
#define WDTCNTCL               (0x0008)       /* WDT - Timer Clear */
#define WDTTMSEL               (0x0010)       /* WDT - Timer Mode Select */
#define WDTSSEL0               (0x0020)       /* WDT - Timer Clock Source Select 0 */
#define WDTSSEL1               (0x0040)       /* WDT - Timer Clock Source Select 1 */
#define WDTHOLD                (0x0080)       /* WDT - Timer hold */

/* WDTCTL Control Bits */
#define WDTIS0_L               (0x0001)       /* WDT - Timer Interval Select 0 */
#define WDTIS1_L               (0x0002)       /* WDT - Timer Interval Select 1 */
#define WDTIS2_L               (0x0004)       /* WDT - Timer Interval Select 2 */
#define WDTCNTCL_L             (0x0008)       /* WDT - Timer Clear */
#define WDTTMSEL_L             (0x0010)       /* WDT - Timer Mode Select */
#define WDTSSEL0_L             (0x0020)       /* WDT - Timer Clock Source Select 0 */
#define WDTSSEL1_L             (0x0040)       /* WDT - Timer Clock Source Select 1 */
#define WDTHOLD_L              (0x0080)       /* WDT - Timer hold */

#define WDTPW                  (0x5A00)

#define WDTIS_0                (0*0x0001u)    /* WDT - Timer Interval Select: /2G */
#define WDTIS_1                (1*0x0001u)    /* WDT - Timer Interval Select: /128M */
#define WDTIS_2                (2*0x0001u)    /* WDT - Timer Interval Select: /8192k */
#define WDTIS_3                (3*0x0001u)    /* WDT - Timer Interval Select: /512k */
#define WDTIS_4                (4*0x0001u)    /* WDT - Timer Interval Select: /32k */
#define WDTIS_5                (5*0x0001u)    /* WDT - Timer Interval Select: /8192 */
#define WDTIS_6                (6*0x0001u)    /* WDT - Timer Interval Select: /512 */
#define WDTIS_7                (7*0x0001u)    /* WDT - Timer Interval Select: /64 */
#define WDTIS__2G              (0*0x0001u)    /* WDT - Timer Interval Select: /2G */
#define WDTIS__128M            (1*0x0001u)    /* WDT - Timer Interval Select: /128M */
#define WDTIS__8192K           (2*0x0001u)    /* WDT - Timer Interval Select: /8192k */
#define WDTIS__512K            (3*0x0001u)    /* WDT - Timer Interval Select: /512k */
#define WDTIS__32K             (4*0x0001u)    /* WDT - Timer Interval Select: /32k */
#define WDTIS__8192            (5*0x0001u)    /* WDT - Timer Interval Select: /8192 */
#define WDTIS__512             (6*0x0001u)    /* WDT - Timer Interval Select: /512 */
#define WDTIS__64              (7*0x0001u)    /* WDT - Timer Interval Select: /64 */

#define WDTSSEL_0              (0*0x0020u)    /* WDT - Timer Clock Source Select: SMCLK */
#define WDTSSEL_1              (1*0x0020u)    /* WDT - Timer Clock Source Select: ACLK */
#define WDTSSEL_2              (2*0x0020u)    /* WDT - Timer Clock Source Select: VLO_CLK */
#define WDTSSEL_3              (3*0x0020u)    /* WDT - Timer Clock Source Select: reserved */
#define WDTSSEL__SMCLK         (0*0x0020u)    /* WDT - Timer Clock Source Select: SMCLK */
#define WDTSSEL__ACLK          (1*0x0020u)    /* WDT - Timer Clock Source Select: ACLK */
#define WDTSSEL__VLO           (2*0x0020u)    /* WDT - Timer Clock Source Select: VLO_CLK */

/* WDT-interval times [1ms] coded with Bits 0-2 */
/* WDT is clocked by fSMCLK (assumed 1MHz) */
#define WDT_MDLY_32         (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2)                         /* 32ms interval (default) */
#define WDT_MDLY_8          (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTIS0)                  /* 8ms     " */
#define WDT_MDLY_0_5        (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTIS1)                  /* 0.5ms   " */
#define WDT_MDLY_0_064      (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTIS1+WDTIS0)           /* 0.064ms " */
/* WDT is clocked by fACLK (assumed 32KHz) */
#define WDT_ADLY_1000       (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTSSEL0)                /* 1000ms  " */
#define WDT_ADLY_250        (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTSSEL0+WDTIS0)         /* 250ms   " */
#define WDT_ADLY_16         (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTSSEL0+WDTIS1)         /* 16ms    " */
#define WDT_ADLY_1_9        (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTSSEL0+WDTIS1+WDTIS0)  /* 1.9ms   " */
/* Watchdog mode -> reset after expired time */
/* WDT is clocked by fSMCLK (assumed 1MHz) */
#define WDT_MRST_32         (WDTPW+WDTCNTCL+WDTIS2)                                  /* 32ms interval (default) */
#define WDT_MRST_8          (WDTPW+WDTCNTCL+WDTIS2+WDTIS0)                           /* 8ms     " */
#define WDT_MRST_0_5        (WDTPW+WDTCNTCL+WDTIS2+WDTIS1)                           /* 0.5ms   " */
#define WDT_MRST_0_064      (WDTPW+WDTCNTCL+WDTIS2+WDTIS1+WDTIS0)                    /* 0.064ms " */
/* WDT is clocked by fACLK (assumed 32KHz) */
#define WDT_ARST_1000       (WDTPW+WDTCNTCL+WDTSSEL0+WDTIS2)                         /* 1000ms  " */
#define WDT_ARST_250        (WDTPW+WDTCNTCL+WDTSSEL0+WDTIS2+WDTIS0)                  /* 250ms   " */
#define WDT_ARST_16         (WDTPW+WDTCNTCL+WDTSSEL0+WDTIS2+WDTIS1)                  /* 16ms    " */
#define WDT_ARST_1_9        (WDTPW+WDTCNTCL+WDTSSEL0+WDTIS2+WDTIS1+WDTIS0)           /* 1.9ms   " */


/************************************************************
* TLV Descriptors
************************************************************/
#define __MSP430_HAS_TLV__                    /* Definition to show that Module is available */
#define TLV_BASE               __MSP430_BASEADDRESS_TLV__

#define TLV_CRC_LENGTH         (0x1A01)       /* CRC length of the TLV structure */
#define TLV_CRC_VALUE          (0x1A02)       /* CRC value of the TLV structure */
#define TLV_START              (0x1A08)       /* Start Address of the TLV structure */
#define TLV_END                (0x1AFF)       /* End Address of the TLV structure */
#define TLV_CRC_START          (0x1A04)       /* Start Address of the CRC protected structure */

#define TLV_LDTAG              (0x01)         /*  Legacy descriptor (1xx, 2xx, 4xx families) */
#define TLV_PDTAG              (0x02)         /*  Peripheral discovery descriptor */
#define TLV_Reserved3          (0x03)         /*  Future usage */
#define TLV_Reserved4          (0x04)         /*  Future usage */
#define TLV_BLANK              (0x05)         /*  Blank descriptor */
#define TLV_Reserved6          (0x06)         /*  Future usage */
#define TLV_Reserved7          (0x07)         /*  Serial Number */
#define TLV_DIERECORD          (0x08)         /*  Die Record  */
#define TLV_ADCCAL             (0x11)         /*  ADC12 calibration */
#define TLV_ADC12CAL           (0x11)         /*  ADC12 calibration */
#define TLV_ADC10CAL           (0x13)         /*  ADC10 calibration */
#define TLV_REFCAL             (0x12)         /*  REF calibration */
#define TLV_TAGEXT             (0xFE)         /*  Tag extender */
#define TLV_TAGEND             (0xFF)         //  Tag End of Table

/************************************************************
* Interrupt Vectors (offset from 0xFF80 + 0x10 for Password)
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
#define PORT2_VECTOR            ".int46"                     /* 0xFFE4 Port 2 */
#else
#define PORT2_VECTOR            (46 * 1u)                    /* 0xFFE4 Port 2 */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define PORT1_VECTOR            ".int47"                     /* 0xFFE6 Port 1 */
#else
#define PORT1_VECTOR            (47 * 1u)                    /* 0xFFE6 Port 1 */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define ADC_VECTOR              ".int48"                     /* 0xFFE8 ADC */
#else
#define ADC_VECTOR              (48 * 1u)                    /* 0xFFE8 ADC */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define USCI_B0_VECTOR          ".int49"                     /* 0xFFEA USCI B0 Receive/Transmit */
#else
#define USCI_B0_VECTOR          (49 * 1u)                    /* 0xFFEA USCI B0 Receive/Transmit */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define USCI_A0_VECTOR          ".int50"                     /* 0xFFEC USCI A0 Receive/Transmit */
#else
#define USCI_A0_VECTOR          (50 * 1u)                    /* 0xFFEC USCI A0 Receive/Transmit */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define WDT_VECTOR              ".int51"                     /* 0xFFEE Watchdog Timer */
#else
#define WDT_VECTOR              (51 * 1u)                    /* 0xFFEE Watchdog Timer */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define RTC_VECTOR              ".int52"                     /* 0xFFF0 RTC */
#else
#define RTC_VECTOR              (52 * 1u)                    /* 0xFFF0 RTC */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define TIMER1_A1_VECTOR        ".int53"                     /* 0xFFF2 Timer1_A3 CC1-2, TA */
#else
#define TIMER1_A1_VECTOR        (53 * 1u)                    /* 0xFFF2 Timer1_A3 CC1-2, TA */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define TIMER1_A0_VECTOR        ".int54"                     /* 0xFFF4 Timer1_A3 CC0 */
#else
#define TIMER1_A0_VECTOR        (54 * 1u)                    /* 0xFFF4 Timer1_A3 CC0 */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define TIMER0_A1_VECTOR        ".int55"                     /* 0xFFF6 Timer0_A3 CC1-2, TA */
#else
#define TIMER0_A1_VECTOR        (55 * 1u)                    /* 0xFFF6 Timer0_A3 CC1-2, TA */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define TIMER0_A0_VECTOR        ".int56"                     /* 0xFFE8 Timer0_A3 CC0 */
#else
#define TIMER0_A0_VECTOR        (56 * 1u)                    /* 0xFFE8 Timer0_A3 CC0 */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define UNMI_VECTOR             ".int57"                     /* 0xFFFA User Non-maskable */
#else
#define UNMI_VECTOR             (57 * 1u)                    /* 0xFFFA User Non-maskable */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define SYSNMI_VECTOR           ".int58"                     /* 0xFFFC System Non-maskable */
#else
#define SYSNMI_VECTOR           (58 * 1u)                    /* 0xFFFC System Non-maskable */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define RESET_VECTOR            ".reset"                     /* 0xFFFE Reset [Highest Priority] */
#else
#define RESET_VECTOR            (59 * 1u)                    /* 0xFFFE Reset [Highest Priority] */
#endif

/************************************************************
* End of Modules
************************************************************/

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* #ifndef __MSP430FR2032 */

