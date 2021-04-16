/*
 * digital_roller.h
 *
 *  Created on: Jan 16, 2020
 *      Author: felix
 */

#ifndef DIGITAL_ROLLER_H_
#define DIGITAL_ROLLER_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "osal.h"
#include "tasks.h"
#include "debug_log.h"
#include "stdbool.h"

/**
 *
 *  LOW_RESULTION: device samples with low resolution and transmits in specified intervals
 *  HIGH_RESULTION: device samples with high resolution and transmits data immediately
 *
**/
typedef enum
{
    LOW_RESOLUTION = 0,
    HIGH_RESOLUTION = 1
} roller_states_t;

#define DEFAULT_HIGH_RES_MEAS_INT (10)    // [s]
#define DEFAULT_LOW_RES_MEAS_INT (600)    // [s]
#define DEFAULT_SETTLING_TIME (1800)       // [s]
#define DEFAULT_TEMP_THRESHOLD (150 * 100) // Degree Celsius * 100
#define DEFAULT_TRANS_INT (3600)           // [s]
#define DEFAULT_RES_STATE (LOW_RESOLUTION)
#define IS_ROLLER_ACTIVE        (1500)

/**
 *
 * highRes_measInt: high resolution measurement interval, specified in [seconds]
 * lowRes_measInt: low resolution measurement interval, specified in [seconds]
 * settling_time: time elapsed until the normal state is reached, specified in [seconds]
 * trans_int: transmission interval, specified in [seconds]
 * temp_threshold: threshold to be reached, specified in [100 * degreeCelsius]
 * resolution_state: 0 for low resolution state, 1 for high resolution state
 *
 **/
typedef struct
{
    uint16_t highRes_measInt;
    uint16_t lowRes_measInt;
    uint16_t settling_time;
    uint16_t trans_int;
    uint16_t temp_threshold;
    roller_states_t resolution_state;
} digital_roller_config_t;

typedef enum
{
    NTC1 = 0x00,
    NTC2 = 0x01,
    NTC3 = 0x02,
    NTC4 = 0x03,
    NTC5 = 0x04,
    NTC6 = 0x05,
    NTC7 = 0x06,
    SI_70_60 = 0x07,
    LSM303AH = 0x08
} digital_roller_sensor_data_keys;

typedef enum
{
    HIGH_RES_MEAS_INT = 0x00,
    LOW_RES_MEAS_INT = 0x01,
    SETTLING_TIME = 0x02,
    TRANS_INT = 0x03,
    TEMP_THRESHOLD = 0x04,
    TRIGGER_RES = 0x05
} digital_roller_actuator_cmd_keys;

typedef struct
{
    digital_roller_config_t config;
    roller_states_t res_state;
} digital_roller_dev;

typedef struct
{
    uint16_t key;
    uint16_t value;
} actuator_command_t;

uint16_t roller_get_highResMeasInt();

uint16_t roller_get_lowResMeasInt();

uint16_t roller_get_settlingTime();

uint16_t roller_get_transInt();

uint16_t roller_get_tempThreshold();

roller_states_t roller_get_resolutionState();

void roller_initialize();

void start_ble_adv_transInt_timer();

void start_advertising();

void roller_AlarmMode();

uint8_t roller_processActuatorCommand(actuator_command_t actCmd);

#endif /* DIGITAL_ROLLER_H_ */
