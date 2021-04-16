#ifndef TIMER_H_
#define TIMER_H_

#define TIMER_CLOCK_SPEED  32768

#define TIMER_ID        ID__8
#define TIMER_ID_VAL    8

#define TIMER_IDEX      TAIDEX_7
#define TIMER_IDEX_VAL  1

#define TIMER_SEC (TIMER_CLOCK_SPEED / TIMER_ID_VAL / TIMER_IDEX_VAL)
#define TIMER_500MSEC (TIMER_SEC / 2)
#define TIMER_200MSEC (TIMER_SEC / 5)

#define PWM_PERIOD		0x7FFF

#define sleep_msec(X) sleep(((X) * TIMER_SEC) / 1000)
#define sleep_sec(X) sleep((X) * TIMER_SEC)
#define lpm_sleep_msec(X) lpm_sleep(((X) * TIMER_SEC) / 1000)
#define lpm_sleep_sec(X) lpm_sleep((X) * TIMER_SEC)

#define timer1_timeout_raise_msec(X) timer1_timeout_raise(((X) * TIMER_SEC) / 1000)
#define timer1_timeout_raise_sec(X) timer1_timeout_raise(((X) * TIMER_SEC))
#define timer1_timeout_abort() TA1CCTL2 = 0

#define timer2_timeout_raise_msec(X) timer2_timeout_raise(((X) * TIMER_SEC) / 1000)
#define timer2_timeout_raise_sec(X) timer2_timeout_raise(((X) * TIMER_SEC))
#define timer2_timeout_abort() TA2CCTL1 = 0


/*
 * sleep (busy or LPM) until ticks are elapsed
 */
void sleep(uint16_t);
void lpm_sleep(uint16_t);
void setup_timer(void);
void start_red_led_timer();


void timer1_timeout_raise(uint16_t ticks);
void timer1_wait_timeout_msec(uint16_t msec);
void timer1_wait_timeout_sec(uint16_t secs);
inline void timer1_timeout_200msec(void);
inline void timer1_reset_timeout_flag(void);
inline uint8_t timer1_get_timeout_flag(void);

void timer2_timeout_raise(uint16_t ticks);
void timer2_wait_timeout_msec(uint16_t msec);
void timer2_wait_timeout_sec(uint16_t secs);

#endif /* TIMER_H_ */
