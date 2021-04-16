/*
 * temperature_measurement.c
 *
 *  Created on: 17.01.2019
 *      Author: Martin
 */
#include <stdbool.h>
#include <inttypes.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "osal.h"
#include "ble_att.h"
#include "ble_bufops.h"
#include "ble_common.h"
#include "ble_gatts.h"
#include "ble_uuid.h"
#include "ble_storage.h"
#include "sys_watchdog.h"
#include "temperature_service.h"
#include "led.h"
#include "SEGGER_RTT.h"
#include "platform_devices.h"
#include "ad_gpadc.h"
#include "hw_gpio.h"
#include "ad_nvms.h"
#include "sys_power_mgr.h"

PRIVILEGED_DATA static OS_TIMER temp_sample_timer;

uint16_t thermistor_nominal = 10000;
uint16_t temperature_nominal = 25;
uint16_t b_coefficient = 3435;

nvms_t custom_partition_handler;

#define TEMP_SAMPLES_FREQUENCY_MS     10000

#define ADC_OFFSET_MV      (12)

#ifdef COMPENSATE_INACCURACY
#define COMPENSATE_MEASURE_INACCURACY(X)        (uint16_t)((float)(X)/(float)1.005 + (float)16.5)
#else
#define COMPENSATE_MEASURE_INACCURACY(X)        (X)
#endif

volatile uint16_t temperature_channel[7] = { 0, 0, 0, 0, 0, 0, 0 };
volatile uint16_t battery_voltage_mV = 0;

static void enable_switch() {
        hw_gpio_configure_pin(SWITCH_DISABLE_PORT, SWITCH_DISABLE_PIN, HW_GPIO_MODE_OUTPUT_PUSH_PULL, HW_GPIO_FUNC_GPIO, false);
}

static void disable_switch() {
        hw_gpio_configure_pin(SWITCH_DISABLE_PORT, SWITCH_DISABLE_PIN, HW_GPIO_MODE_OUTPUT_PUSH_PULL, HW_GPIO_FUNC_GPIO, true);
}

static void configure_switch(channel_config_t channel) {
        switch (channel) {
        case ch_0:
                // S1 = L, S2 = L, S3 = L => CH_0
                hw_gpio_configure_pin(S1_PORT, S1_PIN, HW_GPIO_MODE_OUTPUT_PUSH_PULL, HW_GPIO_FUNC_GPIO, false);
                hw_gpio_configure_pin(S2_PORT, S2_PIN, HW_GPIO_MODE_OUTPUT_PUSH_PULL, HW_GPIO_FUNC_GPIO, false);
                hw_gpio_configure_pin(S3_PORT, S3_PIN, HW_GPIO_MODE_OUTPUT_PUSH_PULL, HW_GPIO_FUNC_GPIO, false);
                break;
        case ch_1:
                // S1 = L, S2 = L, S3 = H => CH_1
                hw_gpio_configure_pin(S1_PORT, S1_PIN, HW_GPIO_MODE_OUTPUT_PUSH_PULL, HW_GPIO_FUNC_GPIO, true);
                hw_gpio_configure_pin(S2_PORT, S2_PIN, HW_GPIO_MODE_OUTPUT_PUSH_PULL, HW_GPIO_FUNC_GPIO, false);
                hw_gpio_configure_pin(S3_PORT, S3_PIN, HW_GPIO_MODE_OUTPUT_PUSH_PULL, HW_GPIO_FUNC_GPIO, false);
                break;
        case ch_2:
                // S1 = L, S2 = H, S3 = L => CH_2
                hw_gpio_configure_pin(S1_PORT, S1_PIN, HW_GPIO_MODE_OUTPUT_PUSH_PULL, HW_GPIO_FUNC_GPIO, false);
                hw_gpio_configure_pin(S2_PORT, S2_PIN, HW_GPIO_MODE_OUTPUT_PUSH_PULL, HW_GPIO_FUNC_GPIO, true);
                hw_gpio_configure_pin(S3_PORT, S3_PIN, HW_GPIO_MODE_OUTPUT_PUSH_PULL, HW_GPIO_FUNC_GPIO, false);
                break;
        case ch_3:
                // S1 = L, S2 = H, S3 = H => CH_3
                hw_gpio_configure_pin(S1_PORT, S1_PIN, HW_GPIO_MODE_OUTPUT_PUSH_PULL, HW_GPIO_FUNC_GPIO, true);
                hw_gpio_configure_pin(S2_PORT, S2_PIN, HW_GPIO_MODE_OUTPUT_PUSH_PULL, HW_GPIO_FUNC_GPIO, true);
                hw_gpio_configure_pin(S3_PORT, S3_PIN, HW_GPIO_MODE_OUTPUT_PUSH_PULL, HW_GPIO_FUNC_GPIO, false);
                break;
        case ch_4:
                // S1 = H, S2 = L, S3 = L => CH_4
                hw_gpio_configure_pin(S1_PORT, S1_PIN, HW_GPIO_MODE_OUTPUT_PUSH_PULL, HW_GPIO_FUNC_GPIO, false);
                hw_gpio_configure_pin(S2_PORT, S2_PIN, HW_GPIO_MODE_OUTPUT_PUSH_PULL, HW_GPIO_FUNC_GPIO, false);
                hw_gpio_configure_pin(S3_PORT, S3_PIN, HW_GPIO_MODE_OUTPUT_PUSH_PULL, HW_GPIO_FUNC_GPIO, true);
                break;
        case ch_5:
                // S1 = H, S2 = L, S3 = H => CH_5
                hw_gpio_configure_pin(S1_PORT, S1_PIN, HW_GPIO_MODE_OUTPUT_PUSH_PULL, HW_GPIO_FUNC_GPIO, true);
                hw_gpio_configure_pin(S2_PORT, S2_PIN, HW_GPIO_MODE_OUTPUT_PUSH_PULL, HW_GPIO_FUNC_GPIO, false);
                hw_gpio_configure_pin(S3_PORT, S3_PIN, HW_GPIO_MODE_OUTPUT_PUSH_PULL, HW_GPIO_FUNC_GPIO, true);
                break;
        case ch_6:
                // S1 = H, S2 = H, S3 = L => CH_6
                hw_gpio_configure_pin(S1_PORT, S1_PIN, HW_GPIO_MODE_OUTPUT_PUSH_PULL, HW_GPIO_FUNC_GPIO, false);
                hw_gpio_configure_pin(S2_PORT, S2_PIN, HW_GPIO_MODE_OUTPUT_PUSH_PULL, HW_GPIO_FUNC_GPIO, true);
                hw_gpio_configure_pin(S3_PORT, S3_PIN, HW_GPIO_MODE_OUTPUT_PUSH_PULL, HW_GPIO_FUNC_GPIO, true);
                break;
        case vbat:
                // S1 = H, S2 = H, S3 = H => VBAT
                hw_gpio_configure_pin(S1_PORT, S1_PIN, HW_GPIO_MODE_OUTPUT_PUSH_PULL, HW_GPIO_FUNC_GPIO, true);
                hw_gpio_configure_pin(S2_PORT, S2_PIN, HW_GPIO_MODE_OUTPUT_PUSH_PULL, HW_GPIO_FUNC_GPIO, true);
                hw_gpio_configure_pin(S3_PORT, S3_PIN, HW_GPIO_MODE_OUTPUT_PUSH_PULL, HW_GPIO_FUNC_GPIO, true);
                break;
        default:
                break;
        }
}

static uint16_t convert_adc_to_mv(gpadc_source src, uint16_t value)
{
        gpadc_source_config *cfg = (gpadc_source_config *)src;
        const uint16 adc_src_max =  ad_gpadc_get_source_max(src);
        uint32_t mv_src_max = (cfg->hw_init.input_attenuator == HW_GPADC_INPUT_VOLTAGE_UP_TO_1V2) ?
                1200 : 3600;

        uint16_t ret = 0;

        switch (cfg->hw_init.input_mode) {
        case HW_GPADC_INPUT_MODE_SINGLE_ENDED:
                if (cfg->hw_init.input == HW_GPADC_INPUT_SE_VBAT) {
                        mv_src_max = 5000;
                }
                ret =  (mv_src_max * value) / adc_src_max;
                break;
        case HW_GPADC_INPUT_MODE_DIFFERENTIAL:
                ret = ((int)mv_src_max * (value - (adc_src_max >> 1))) / (adc_src_max >> 1);
                break;
        default:
                /* Invalid input mode */
                OS_ASSERT(0);
        }

        return ret;
}

static uint16_t convert_resistance_to_temperature(uint16_t resistance) {
        /*
         *      Note: Termperature conversion works only between -328 and 327�C properly
         *      Do not use this function outside of its specification.
         *
         */
        volatile float temperature;
        temperature = (float)resistance / (float)thermistor_nominal;    // (R/Ro)
        temperature = log(temperature);                                 // ln(R/Ro)
        temperature /= b_coefficient;                                   // 1/B * ln(R/Ro)
        temperature += 1.0 / (temperature_nominal + 273.15);            // + (1/To)
        temperature = 1.0 / temperature;                                // Invert
        temperature -= 273.15;                                          // convert to C

        return (uint16_t)(temperature*100);
}

static uint16_t read_voltage_in_mv(channel_config_t channel) {
        gpadc_source src;
        uint16_t value;
        configure_switch(channel);
        enable_switch();
        OS_DELAY_MS(10);
        configure_switch(channel);
        /*
         * Open source connected to GPADC.
         * This will not start any measurement yet.
         */
        src = ad_gpadc_open(TEMP_SENSOR);

        //Power Manager (PM) of the chip is aware of the GPADC peripheral usage and, before the system enters sleep, it checks whether or not there is activity on the GPADC block.
        ad_gpadc_read(src, &value);

        //printf("U2: %"PRIu16"[mV] ", convert_adc_to_mv(src, value));
        //printf(" --> %"PRIu16" [mV]\r\n", COMPENSATE_MEASURE_INACCURACY(convert_adc_to_mv(src, value)));
        /*
         * This task will not use GPADC for time being, close it.
         */
        ad_gpadc_close(src);

        // Disable switch and discharge capacitor
        disable_switch();
        hw_gpio_configure_pin(ADC_PORT, ADC_PIN, HW_GPIO_MODE_OUTPUT_PUSH_PULL, HW_GPIO_FUNC_GPIO, false);
        OS_DELAY_MS(10);
        hw_gpio_configure_pin(ADC_PORT, ADC_PIN, HW_GPIO_MODE_INPUT, HW_GPIO_FUNC_ADC, true);

        return COMPENSATE_MEASURE_INACCURACY(convert_adc_to_mv(src, value));
}

#define read_battery_voltage_in_mv()      read_voltage_in_mv((channel_config_t)vbat)

/*                              VBAT
 *                              ___
 *                               |
 *                               |
 *                              ---
 *                              | |
 *                              | |  R_1
 *                              ---
 *                               |
 *                               +------------------o U_2
 *                               |             |
 *                              ---            |
 *                              | |          -----
 *                              | | R_2      -----  C
 *                              ---            |
 *                               |             |
 *                               |             |
 *                              ___           ___
 *                               -             -
 */

uint16_t get_temperature(channel_config_t channel) {
        uint16_t U_2_mV = 0;
        uint16_t R_1_Ohm = 0;
        const uint16_t R_2_kOhm = 2;
        uint16_t current_uA = 0;

        battery_voltage_mV = read_battery_voltage_in_mv();
        U_2_mV = read_voltage_in_mv(channel);

        if(battery_voltage_mV <= U_2_mV) {
                // this should not happen
                R_1_Ohm = 1;
        }
        else {
                current_uA = U_2_mV / R_2_kOhm;
                R_1_Ohm = (battery_voltage_mV - U_2_mV) * 1000 / current_uA;
        }
        temperature_channel[(uint8_t)channel] = convert_resistance_to_temperature(R_1_Ohm);

        return  temperature_channel[(uint8_t)channel];
}

static void temp_sample_cb(OS_TIMER timer)
{
        OS_TASK task = (OS_TASK) OS_TIMER_GET_TIMER_ID(timer);
        OS_TASK_NOTIFY(task, READ_TEMP_NOTIF, OS_NOTIFY_SET_BITS);
}

void temperature_service_task(void *params) {
        // register this task with the watchdog
        int8_t wdog_id = sys_watchdog_register(false);

        printf("temperature service task alive\r\n");

        ble_service_t *temperature_service = params;

        // create timer for DIN processing
        temp_sample_timer = OS_TIMER_CREATE("temperature", OS_MS_2_TICKS(TEMP_SAMPLES_FREQUENCY_MS), true, (void *) OS_GET_CURRENT_TASK(), temp_sample_cb);
        OS_ASSERT(temp_sample_timer);

        /*
        * Before accessing a partition entry, you should first open it. */
        custom_partition_handler = ad_nvms_open(NVMS_CUSTOM_ENTRY_ONE);

//        wd_log_bytes = ad_nvms_write(nvms_var, 0,
//        (uint8_t *)log_value_1_wd, sizeof(log_value_1_wd));
//        OS_ASSERT(wd_log_bytes != 0);
        uint8_t buf[2];
        ad_nvms_read(custom_partition_handler, 0x00000000, buf, sizeof(uint16_t));
        thermistor_nominal = (buf[0] << 8) + buf[1];
        if(thermistor_nominal == 0xffff) {
                thermistor_nominal = 10000;
        }
        ad_nvms_read(custom_partition_handler, 0x00000002, buf, sizeof(uint16_t));
        temperature_nominal = (buf[0] << 8) + buf[1];
        if(temperature_nominal == 0xffff) {
                temperature_nominal = 25;
        }
        ad_nvms_read(custom_partition_handler, 0x00000004, buf, sizeof(uint16_t));
        b_coefficient = (buf[0] << 8) + buf[1];
        if(b_coefficient == 0xffff) {
                b_coefficient = 3435;
        }

        while (1) {
                OS_BASE_TYPE ret;
                uint32_t notif;

                // notify watchdog on each loop
                sys_watchdog_notify(wdog_id);

                // suspend watchdog while blocking on OS_TASK_NOTIFY_WAIT()
                //sys_watchdog_suspend(wdog_id);

                // wait on any notification, and then clear all bits
                ret = OS_TASK_NOTIFY_WAIT(0, OS_TASK_NOTIFY_ALL_BITS, &notif, OS_TIME_TO_TICKS(2000));

                // resume watchdog
                //sys_watchdog_notify_and_resume(wdog_id);
                sys_watchdog_notify(wdog_id);

                if (ret == OS_TASK_NOTIFY_FAIL) {
                        printf("temperature task: no notifications\r\n");
                        continue;
                }

                // notified from DIN processing timer
                if (notif & READ_TEMP_NOTIF) {
                        uint16_t temp_values[8] = {0};
                        pm_stay_alive();
                        for(uint8_t i=0; i<7; i++) {
                                temp_values[i] = get_temperature((channel_config_t)i);
                        }
                        send_temp_notifications(temperature_service);
                        pm_resume_sleep();
                }
                else if(notif & TEMP_CONNECTED) {
                        OS_TIMER_START(temp_sample_timer, OS_TIMER_FOREVER);
                }
                else if(notif & TEMP_DISCONNECTED) {
                        OS_TIMER_STOP(temp_sample_timer, OS_TIMER_FOREVER);
                }
        }
}
