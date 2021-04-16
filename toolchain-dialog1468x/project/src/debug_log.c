#include <stdio.h>
#include <stdarg.h>

#include "osal.h"
#include "sys_rtc.h"
#include "sys_clock_mgr.h"
#include "debug_log.h"

static OS_MUTEX debug_lock;

uint64 rtc_get_time_usec()
{
#if (dg_configUSE_LP_CLK == LP_CLK_RCX)
    static uint64 time_usec = 0;
    static uint64 last_rtc = 0;

    OS_MUTEX_GET(debug_lock, OS_MUTEX_FOREVER);

    uint64 now_rtc = rtc_get();
    time_usec += (now_rtc - last_rtc) * (uint64) rcx_clock_period / 1024 / 1024;
    last_rtc = now_rtc;

    OS_MUTEX_PUT(debug_lock);

    return time_usec;
#else
    return rtc_get() * (uint64) 1000000 / (uint64) configSYSTICK_CLOCK_HZ;
#endif
}

void debug_log_init()
{
    OS_MUTEX_CREATE(debug_lock);
}

void debug_log(char *msg, ...)
{
    va_list args;
    va_start(args, msg);

    OS_MUTEX_GET(debug_lock, OS_MUTEX_FOREVER);

    int time = rtc_get_time_usec() / 1000;
    printf("%d.%03d: ", time / 1000, time % 1000);
    vprintf(msg, args);
    printf("\n");

    OS_MUTEX_PUT(debug_lock);
}
