#include <msp430.h>
#include <stdint.h>

#include "timer.h"
#include "main.h"
#include "uart.h"

uint8_t volatile _sleep_flag = 0;
uint8_t volatile _timer1_timeout_flag = 0;
uint8_t volatile _timer2_timeout_flag = 0;

// configure & run timer. must be called before any other functions of this module
void setup_timer(void) 
{
    TA0CTL = ( 0
            | TASSEL_1	// ACLK
            | ID_0		// Input divider /1
            | MC_1		// Up mode
            | TACLR		// Timer clear
            //| TAIE	    // Timer interrupt enable
            );
    // upper boarder of 0xFFFF/2 = 32767 => 1s
    TA0CCR0 = PWM_PERIOD;

    TA1CTL = TACLR; 		//reset
    TA1CTL = (
            TASSEL_1      // clock select: TASSEL_1 = ACLK; TASSEL_2 = SMCLK
            | TIMER_ID    // input divider
            | MC_2        // mode ctrl: MC_0=stop; MC_1=up; MC_2=cont; MC_3=updown
            | TAIE        // interrupt enable
            );

    TA2CTL = TACLR; 		//reset
    TA2CTL = (
            TASSEL_1      // clock select: TASSEL_1 = ACLK; TASSEL_2 = SMCLK
            | TIMER_ID    // input divider
            | MC_2        // mode ctrl: MC_0=stop; MC_1=up; MC_2=cont; MC_3=updown
            | TAIE        // interrupt enable
            );

}

void lpm_sleep(uint16_t ticks) 
{
    TA1CCR1 = TA1R + ticks;
    TA1CCTL1 = (OUTMOD_4 | CCIE);
    LPM3;
    TA1CCTL1 = 0;
}

void sleep(uint16_t ticks) 
{
    _sleep_flag = 0;
    TA1CCR1 = TA1R + ticks;
    TA1CCTL1 = (OUTMOD_4 | CCIE);
    while (!(_sleep_flag));
    TA1CCTL1 = 0;
}

void timer1_timeout_raise(uint16_t ticks) 
{
    TA1CCR2 = TA1R + ticks;
    _timer1_timeout_flag = 0;
    TA1CCTL2 = (OUTMOD_4 | CCIE);
}

void timer2_timeout_raise(uint16_t ticks) 
{
    TA2CCR1 = TA2R + ticks;
    _timer2_timeout_flag = 0;
    TA2CCTL1 = (OUTMOD_4 | CCIE);
}

void timer1_wait_timeout_msec(uint16_t msec)
{
    timer1_timeout_raise_msec(msec);
    while ( !_timer1_timeout_flag  ) {};
}

void timer2_wait_timeout_msec(uint16_t msec)
{
    timer2_timeout_raise_msec(msec);
    while ( !_timer2_timeout_flag  ) {};
}

void timer1_wait_timeout_sec(uint16_t secs)
{
    timer1_timeout_raise_sec(secs);
    while ( !_timer1_timeout_flag  ) {};
}

void timer2_wait_timeout_sec(uint16_t secs)
{
    timer2_timeout_raise_sec(secs);
    while ( !_timer2_timeout_flag  ) {};
}

inline void timer1_timeout_200msec(void)
{
    TA1CCR2 = TA1R + TIMER_200MSEC; 
    _timer1_timeout_flag = 0;
    TA1CCTL2 = (OUTMOD_4 | CCIE);
}

inline void timer1_reset_timeout_flag(void)
{
    _timer1_timeout_flag = 0;
}

inline uint8_t timer1_get_timeout_flag(void)
{
    return _timer1_timeout_flag;
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER2_A0_VECTOR
__interrupt void timer2_a0_ccrn_isr(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt TIMER2_A0_VECTOR)) timer2_a0_ccrn_isr()
#else
#error Compiler not supported!
#endif
{
    TA2CCTL0 &= ~CCIFG;
}

/*
 * ISR for one-time timer flags
 *
 * the corresponding CCRs are set by functions and expected
 * to raise only once after being set.
 * that's why the CCRs are disabled after they trigger once.
 */
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER2_A1_VECTOR
__interrupt void timer2_a1_ccrn_isr(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt TIMER2_A1_VECTOR)) timer2_a1_ccrn_isr()
#else
#error Compiler not supported!
#endif
{
    switch (TA2IV) 
    {
            // for raise_timeout()
        case TA2IV_TA2CCR1:
            _timer2_timeout_flag = 1;
            TA2CCTL1 = 0;
            break;
    }
}



#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER1_A0_VECTOR
__interrupt void timer1_a0_ccrn_isr(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt TIMER1_A0_VECTOR)) timer1_a0_ccrn_isr()
#else
#error Compiler not supported!
#endif
{
    TA1CCTL0 &= ~CCIFG;
}

/*
 * ISR for one-time timer flags
 *
 * the corresponding CCRs are set by functions and expected
 * to raise only once after being set.
 * that's why the CCRs are disabled after they trigger once.
 */
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER1_A1_VECTOR
__interrupt void timer1_a1_ccrn_isr(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt TIMER1_A1_VECTOR)) timer1_a1_ccrn_isr()
#else
#error Compiler not supported!
#endif
{
    switch (TA1IV) 
    {
            // for sleep() and lpm_sleep()
        case TA1IV_TA1CCR1:
            _sleep_flag = 1;
            TA1CCTL1 = 0;
            LPM3_EXIT;
            break;

            // for raise_timeout()
        case TA1IV_TA1CCR2:
            _timer1_timeout_flag = 1;
            TA1CCTL2 = 0;
            break;
    }
}
