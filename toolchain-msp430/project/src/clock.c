/*
 * clock.c
 *
 *  Created on: 09.11.2017
 *      Author: martinfehre
 */

#include <msp430.h>
#include "clock.h"

void clock_init() 
{
    P2SEL0 |= BIT0 | BIT1;                  // set XT1 pin as second function

    while (SFRIFG1 & OFIFG)              // Test oscillator fault flag
    {
        CSCTL7 &= ~(XT1OFFG | DCOFFG);      // Clear XT1 and DCO fault flag
        SFRIFG1 &= ~OFIFG;
    }

    __bis_SR_register(SCG0);                // disable FLL

    CSCTL3 |= SELREF__XT1CLK;               // Set XT1CLK as FLL reference source
    CSCTL0 = 0;                             // clear DCO and MOD registers
    CSCTL1 &= ~(DCORSEL_7);                 // Clear DCO frequency select bits first
    CSCTL1 |= DCORSEL_3;                    // Set DCO = 8MHz
    CSCTL2 = FLLD_0 + 243;                  // DCODIV = 8MHz

    __delay_cycles(3);
    __bic_SR_register(SCG0);                // enable FLL

    while(CSCTL7 & (FLLUNLOCK0 | FLLUNLOCK1)); // Poll until FLL is locked
    
    // DCOCLK = MCLK and SMCLK source
    // Set ACLK = XT1CLK = 32768Hz
    CSCTL4 = SELMS__DCOCLKDIV | SELA__XT1CLK;  
}
