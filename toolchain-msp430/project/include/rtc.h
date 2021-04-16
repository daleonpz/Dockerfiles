#ifndef RTC_H_
#define RTC_H_

/*
 * Set up the MCU's RTC module. This will most probably have to be edited for
 * any new MCU or if there's no clock quartz, etc.
 */
extern void setup_rtc(void);

/*
 * Read current time (epoch) from RTC and write it to supplied uint32_t pointer.
 */
extern void rtc_get_time(uint32_t *);

/*
 * Read time (epoch) from supplied uin32_t pointer and write it to the RTC.
 */
extern void rtc_set_time(const uint32_t *);

volatile uint32_t rtc_offset;

#endif /* RTC_H_ */
