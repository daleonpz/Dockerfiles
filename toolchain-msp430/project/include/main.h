#ifndef MAIN_H_
#define MAIN_H_

#include <stdint.h>
#include "timer.h"

#define	WDT_250ms		WDT_ARST_250
#define WDT_16s 		WDTPW+WDTCNTCL+WDTSSEL0+WDTIS1+WDTIS0
#define WDT_4m16s         WDTPW+WDTCNTCL+WDTSSEL0+WDTIS1

// WDTPW is already included in WDT_MODE
#define	wdt_set(x)		WDTCTL = x
#define	wdt_stop()		WDTCTL = WDTPW + WDTHOLD
#define wdt_reset()     WDTCTL = WDTHOLD



#endif /* MAIN_H_ */
