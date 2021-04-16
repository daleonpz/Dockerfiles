/*
 * led_online.h
 *
 *  Created on: 17.01.2019
 *      Author: Martin
 */

#ifndef LED_H_
#define LED_H_

#include <stdbool.h>

void led_online_constant_dim_func();
void led_error_constant_dim_func();
void led_testing_constant_bright_func();
void led_error_constant_bright_func();
void led_set_emergency_blink_func();
void led_clear_emergency_blink_func();
void led_dim_standby_breath_func();
void led_testing_breath_func();
void led_stop_func();
void led_error_stop_func();
void led_online_stop_func();
void init_led_after_wakeup();

#endif /* LED_H_ */
