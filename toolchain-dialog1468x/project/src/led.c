/**
 ****************************************************************************************
 *
 * @file demo_breath.c
 *
 * @brief Breath timer demo (hw_breath driver)
 *
 * Copyright (C) 2015-2017 Dialog Semiconductor.
 * This computer program includes Confidential, Proprietary Information
 * of Dialog Semiconductor. All Rights Reserved.
 *
 ****************************************************************************************
 */

#include <stdio.h>
#include <string.h>
#include <hw_breath.h>
#include <hw_led.h>
#include "led.h"
//#include "common.h"

uint8_t led_status_change_lock  = 0;

#define LED_STATUS_CHANGE_IS_ALLOWED    !led_status_change_lock
#define LOCK_LED_STATUS_CHANGE()        led_status_change_lock = 1
#define UNLOCK_LED_STATUS_CHANGE()      led_status_change_lock = 0

#define LED_TESTING_DIM          0x0001
#define LED_TESTING_BRIGHT       0x0002
#define LED_BREATH_DIM          0x0004
#define LED_BREATH              0x0008

#define LED_ERROR_DIM           0x0100
#define LED_ERROR_BRIGHT        0x0200
#define LED_EMERGENCY           0x0400

uint16_t led_status = 0x00;


static void setup_led_blue(uint8_t dc_min, uint8_t dc_max, uint8_t dc_step, uint8_t freq_div)
{
        breath_config config = {
                .dc_min = dc_min,
                .dc_max = dc_max,
                .dc_step = dc_step,
                .freq_div = freq_div,
                .polarity = HW_BREATH_PWM_POL_POS
        };

        /*
         * Setup breath timer configuration, so hardware can drive LED automatically.
         */
        hw_breath_init(&config);

        /*
         * Setup LED1 output to be driven by timer.
         */
        hw_led_set_led1_src(HW_LED_SRC1_BREATH);
        hw_led_enable_led1(true);

        /*
         * Then start breath timer.
         */
        hw_breath_enable();
}

static void setup_led_red(uint8_t dc_min, uint8_t dc_max, uint8_t dc_step, uint8_t freq_div)
{
        breath_config config = {
                .dc_min = dc_min,
                .dc_max = dc_max,
                .dc_step = dc_step,
                .freq_div = freq_div,
                .polarity = HW_BREATH_PWM_POL_POS
        };

        /*
         * Setup breath timer configuration, so hardware can drive LED automatically.
         */
        hw_breath_init(&config);

        /*
         * Setup LED1 output to be driven by timer.
         */
        hw_led_set_led2_src(HW_LED_SRC2_BREATH);
        hw_led_enable_led2(true);

        /*
         * Then start breath timer.
         */
        hw_breath_enable();
}

void led_online_constant_dim_func()
{
        /*
         * With those parameters, breath timer is setup to generate constant
         * PWM with 12% duty cycle (30 / 256 * 100%). It could be used to
         * drive power LED when device is not in standby mode.
         */
        if(LED_STATUS_CHANGE_IS_ALLOWED) {
                setup_led_blue(29, 30, 255, 255);
                led_status = (led_status & 0xff00) + LED_TESTING_DIM;
        }
}

void led_error_constant_dim_func()
{
        /*
         * With those parameters, breath timer is setup to generate constant
         * PWM with 12% duty cycle (30 / 256 * 100%). It could be used to
         * drive power LED when device is not in standby mode.
         */
        if(LED_STATUS_CHANGE_IS_ALLOWED) {
                setup_led_red(29, 30, 255, 255);
                led_status = (led_status & 0x00ff) + LED_ERROR_DIM;
        }
}

void led_testing_constant_bright_func()
{
        /*
         * With those parameters, breath timer is setup to generate constant
         * PWM with 94% duty cycle (240 / 256 * 100%). It could be used to
         * drive power LED when device is not in standby mode.
         */
        if(LED_STATUS_CHANGE_IS_ALLOWED) {
                setup_led_blue(239, 240, 1, 255);
                led_status = (led_status & 0xff00) + LED_TESTING_BRIGHT;
        }
}

void led_error_constant_bright_func()
{
        /*
         * With those parameters, breath timer is setup to generate constant
         * PWM with 94% duty cycle (240 / 256 * 100%). It could be used to
         * drive power LED when device is not in standby mode.
         */
        if(LED_STATUS_CHANGE_IS_ALLOWED) {
                setup_led_red(239, 240, 1, 255);
                led_status = (led_status & 0x00ff) + LED_ERROR_BRIGHT;
        }
}

void led_set_emergency_blink_func()
{
        /*
         * Following configuration allows to setup breath timer settings with maximum PWM
         * changing from 0 to 100% at speed around 4 times per second.
         * Those settings could be used for emergency blinking mode.
         */
        LOCK_LED_STATUS_CHANGE();
        led_online_stop_func();
        setup_led_red(0, 255, 32, 255);
        led_status = LED_EMERGENCY;
}

void led_clear_emergency_blink_func()
{
        /*
         * Following configuration allows to setup breath timer settings with maximum PWM
         * changing from 0 to 100% at speed around 4 times per second.
         * Those settings could be used for emergency blinking mode.
         */
        UNLOCK_LED_STATUS_CHANGE();
        led_error_stop_func();
        led_status = 0;
}

void led_dim_standby_breath_func()
{
        /*
         * Following configuration allows to setup breath timer settings with maximum PWM
         * duty cycle reduce to 31% (80 * 100 / 256).
         * Those settings could be used for standby mode if allowing 100% maximum duty cycle
         * is to bright. With this settings, LED will blink 3 times in 2 seconds.
         */
        if(LED_STATUS_CHANGE_IS_ALLOWED) {
                setup_led_blue(0, 80, 255, 255);
                led_status = (led_status & 0xff00) + LED_BREATH_DIM;
        }
}

void led_testing_breath_func()
{
        /*
         * Following configuration allows to setup slowest possible breath timer settings.
         * PWM duty cycle changes form 0 to 100% and back in around 2 seconds, generating
         * PWM suitable for unobtrusive standby LED.
         */
        if(LED_STATUS_CHANGE_IS_ALLOWED) {
                setup_led_blue(0, 255, 255, 255);
                led_status = (led_status & 0xff00) + LED_BREATH;
        }
}

void init_led_after_wakeup() {
        if(led_status == 0x0000) {
                return;
        }
        switch(led_status & 0xff00) {
        case LED_EMERGENCY:
                led_set_emergency_blink_func();
                return;
        case LED_ERROR_DIM:
                led_error_constant_dim_func();
                break;
        case LED_ERROR_BRIGHT:
                led_error_constant_bright_func();
                break;
        default: break;
        }

        switch(led_status & 0x00ff) {
        case LED_TESTING_DIM:
                led_online_constant_dim_func();
                break;
        case LED_TESTING_BRIGHT:
                led_testing_constant_bright_func();
                break;
        case LED_BREATH_DIM:
                led_dim_standby_breath_func();
                break;
        case LED_BREATH:
                led_testing_breath_func();
                break;
        default: break;
        }
}

void led_stop_func()
{
        /*
         * Stop generating PWM.
         */
        hw_breath_disable();
        hw_led_enable_led1(false);
        hw_led_enable_led2(false);
        led_status = 0x0000;
}

void led_online_stop_func()
{
        /*
         * Stop generating PWM.
         */
        hw_led_enable_led1(false);
        led_status &= ~0x00ff;
        if(led_status == 0x0000) {
                hw_breath_disable();
        }
}

void led_error_stop_func()
{
        /*
         * Stop generating PWM.
         */
        hw_breath_disable();
        hw_led_enable_led2(false);
        led_status &= ~0xff00;
        if(led_status == 0x0000) {
                hw_breath_disable();
        }
}
