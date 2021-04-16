#ifndef DELAY_H_
#define DELAY_H_

#include <intrinsics.h>

// define system frequency and macros for time delay loops
#define CLOCK_RATE 1048576
#define __delay_usec(x) __delay_cycles((unsigned long) (x))
#define __delay_msec(x) __delay_cycles(((unsigned long) (x)) * 1048L)
#define __delay_sec(x) __delay_cycles(((unsigned long) (x)) * 1048576L)

#endif /* DELAY_H_ */
