/*
 * measurement_routine.c
 *
 *  Created on: 15.03.2019
 *      Author: Felix Sch�tte
 */
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lsm303ah.h"
#include "si7060.h"
#include <stdio.h>
#include "platform_devices.h"
#include "sys_watchdog.h"
#include "measurement_routine.h"
#include "hw_wkup.h"
#include "ad_nvparam.h"
#include "platform_nvparam.h"
#include "sbt_storage.h"
#include "sys_rtc.h"
#include "tasks.h"
#include "debug_log.h"
#include "temperature_service.h"
#include "sys_power_mgr.h"
#include "digital_roller.h"
#include "hw_wkup.h"

#define RTC_FREQUENCY                     (32768)

#define debug_log(...)  

PRIVILEGED_DATA static OS_TIMER measurement_cycle_timer;

void timer_cb(OS_TIMER timer)
{
        uint32_t notif = (uint32_t)OS_TIMER_GET_TIMER_ID(timer);
        OS_TASK_NOTIFY(measurement_task_handle, notif, OS_NOTIFY_SET_BITS);
}

static void temp_alarm(uint16_t temp_value)
{
        if (temp_value > roller_get_tempThreshold()) {
                debug_log("temperature threshold exceeded.");
                roller_AlarmMode();
        }
}

static void isRollerActive(uint16_t norm)
{
        if (norm > IS_ROLLER_ACTIVE) {
                debug_log("roller is active now.");
                roller_AlarmMode();
        }
}

void measurement_routine_task(void *params)
{
        measurement_cycle_timer = OS_TIMER_CREATE("Measurement Period",
                OS_MS_2_TICKS(1000), true, MEASUREMENT_DONE_NOTIF,
                timer_cb);
        OS_ASSERT(measurement_cycle_timer);

        OS_TIMER_START(measurement_cycle_timer, OS_TIMER_FOREVER);

        roller_initialize();

        lsm303_init_accel();

#if MEASUREMENT_ROUTINE_DEBUG
        debug_log("Measurement Task alive");
#endif

        int8_t wdog_id = sys_watchdog_register(false);
        while (1) {
                OS_BASE_TYPE ret;
                uint32_t notif;

                // notify watchdog on each loop
                sys_watchdog_notify(wdog_id);

                // suspend watchdog while blocking on OS_TASK_NOTIFY_WAIT()
                sys_watchdog_suspend(wdog_id);

                // wait on any notification, and then clear all bits
                ret = OS_TASK_NOTIFY_WAIT(0, OS_TASK_NOTIFY_ALL_BITS, &notif,
                        OS_TIME_TO_TICKS(100000));

                // resume watchdog
                sys_watchdog_notify_and_resume(wdog_id);

                if (notif & MEASUREMENT_DONE_NOTIF) {
                        sbt_storage_data_point_t temperature = { 0 };
                        sbt_storage_data_point_t si7060_temp = { 0 };
                        sbt_storage_data_point_t accel = { 0 };
                        uint32_t vector_norm = 0;

                        debug_log("Performing measurement");
                        pm_stay_alive();
                        for (uint8_t i = 0; i < NUMBER_POF_NTC_SENS; i++) {
                                temperature.key = i;
                                temperature.timestamp = (uint32_t)rtc_get() / RTC_FREQUENCY;
                                temperature.value = get_temperature((channel_config_t)i);

                                debug_log("Temperature: #%d:  %d", i,
                                        temperature.value);
                                sbt_storage_add_datapoint(&temperature);
                                temp_alarm(temperature.value);

                        }
                        pm_resume_sleep();

                        si7060_temp.key = SI_70_60;
                        si7060_temp.value = si7060_getTemperature() * 100;
                        sbt_storage_add_datapoint(&si7060_temp);
                        debug_log("si7060 temp: %d", si7060_temp.value);
                        temp_alarm(si7060_temp.value);

                        read_sensor_data(&vector_norm);
                        debug_log("Accelerometer norm: %d ", vector_norm);
                        accel.key = LSM303AH;
                        accel.value = (uint16_t) vector_norm;
                        sbt_storage_add_datapoint(&accel);
                        isRollerActive((uint16_t) accel.value);
                        start_advertising();
                }
                else if (notif & CHANGE_MEAS_TIMER_PERIOD) {
                        if (roller_get_resolutionState() == HIGH_RESOLUTION) {
                                OS_TIMER_STOP(measurement_cycle_timer, OS_TIMER_FOREVER);
                                OS_TIMER_CHANGE_PERIOD(measurement_cycle_timer, OS_MS_2_TICKS(
                                        roller_get_highResMeasInt() * 1000), OS_TIMER_FOREVER);
                                debug_log("Changing timer period to (high) %d ",
                                        roller_get_highResMeasInt());
                        }
                        else {
                                OS_TIMER_STOP(measurement_cycle_timer, OS_TIMER_FOREVER);
                                OS_TIMER_CHANGE_PERIOD(measurement_cycle_timer,
                                        OS_MS_2_TICKS(roller_get_lowResMeasInt() * 1000),
                                        OS_TIMER_FOREVER);
                                debug_log("Changing timer period to (low) %d ",
                                        roller_get_lowResMeasInt());
                        }
                }
                else {
                        debug_log("no measurement ... \r\n");
                }
        }
}

