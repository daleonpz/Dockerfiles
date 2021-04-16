#include <msp430.h>
#include <stdint.h>

#include "rtc.h"

void setup_rtc (void) 
{
    RTCMOD = 0xFFFF; //Set compareregister to MAX
    RTCCTL = ( 0
            | RTCSS1 // XT1CLK as clocksource
            | RTCPS0 //
            | RTCPS1 // divider to 1024 -> overflow every 34,13 minutes
            | RTCPS2 //
            | RTCSR  // reset rtc
            | RTCIE
            );
}

/*
 * sets the RTC to the value of *time
 *      (e.g. address of global _csp_packet_rx.time)
 */
void rtc_set_time(const uint32_t * time) 
{
    RTCCTL |= RTCSR;  // reset rtc
    rtc_offset = *time;
}

/*
 * reads the time from the RTC module and writes it to _time
 */
void rtc_get_time(uint32_t *time) 
{
    uint16_t rtc_time = (RTCCNT / 32);
    *time = rtc_time + rtc_offset;
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=RTC_VECTOR
__interrupt void rtc_isr(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt RTC_VECTOR)) rtc_isr()
#else
#error Compiler not supported!
#endif
{
    if(RTCIV)
    {
        rtc_offset = rtc_offset + (uint32_t) 2048;//34,13min
    }
}
