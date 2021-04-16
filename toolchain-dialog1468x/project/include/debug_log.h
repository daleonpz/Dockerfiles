#ifndef DEBUG_LOG_H_
#define DEBUG_LOG_H_

#include "osal.h"

uint64 rtc_get_time_usec();

void debug_log_init();
void debug_log(char *msg, ...);

#endif
