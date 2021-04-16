/*
 * lsm303ah.h
 *
 *  Created on: 11.03.2019
 *      Author: Felix Sch�tte
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef INC_LSM303AH_H_
#define INC_LSM303AH_H_

#define                 LSM_DEBUG_ENABLED               0x01

/* Register map (Accelerometer) */
#define                 WHO_AM_I_A                      0x0F
#define                 CTRL1_A                         0x20
#define                 CTRL2_A                         0x21
#define                 CTRL3_A                         0x22
#define                 CTRL4_A                         0x23
#define                 CTRL5_A                         0x24
#define                 FIFO_CTRL_A                     0x25
#define                 OUT_T_A                         0x26
#define                 STATUS_A                        0x27
#define                 OUT_X_L_A                       0x28
#define                 OUT_X_H_A                       0x29
#define                 OUT_Y_L_A                       0x2A
#define                 OUT_Y_H_A                       0x2B
#define                 OUT_Z_L_A                       0x2C
#define                 OUT_Z_H_A                       0x2D
#define                 FIFO_THS_A                      0x2E
#define                 FIFO_SRC_A                      0x2F
#define                 FIFO_SAMPLES_A                  0x30
#define                 TAP_6D_THS_A                    0x31
#define                 INT_DUR_A                       0x32
#define                 WAKE_UP_THS_A                   0x33
#define                 WAKE_UP_DUR_A                   0x34
#define                 FREE_FALL_A                     0x35
#define                 STATUS_DUP_A                    0x36
#define                 WAKE_UP_SRC_A                   0x37
#define                 TAP_SRC_A                       0x38
//#define                 6D_SRC_A                        0x39
#define                 STEP_COUNTER_MINTHS_A           0x3A
#define                 STEP_COUNTER_L_A                0x3B
#define                 STEP_COUNTER_H_A                0x3C
#define                 FUNC_CK_GATE_A                  0x3D
#define                 FUNC_SRC_A                      0x3E
#define                 FUNC_CTRL_A                     0x40

/* Register map (Magnetometer) */
#define                 OFFSET_X_REG_L_M                0x45
#define                 OFFSET_X_REG_H_M                0x46
#define                 OFFSET_Y_REG_L_M                0x47
#define                 OFFSET_Y_REG_H_M                0x48
#define                 OFFSET_Z_REG_L_M                0x49
#define                 OFFSET_Z_REG_H_M                0x4A
#define                 WHO_AM_I_M                      0x4F
#define                 CFG_REG_A_M                     0x60
#define                 CFG_REG_B_M                     0x61
#define                 CFG_REG_C_M                     0x62
#define                 INT_CRTL_REG_M                  0x63
#define                 INT_SOURCE_REG_M                0x64
#define                 INT_THS_L_REG_M                 0x65
#define                 INT_THS_H_REG_M                 0x66
#define                 STATUS_REG_M                    0x67
#define                 OUTX_L_REG_M                    0x68
#define                 OUTX_H_REG_M                    0x69
#define                 OUTY_L_REG_M                    0x6A
#define                 OUTY_H_REG_M                    0x6B
#define                 OUTZ_L_REG_M                    0x6C
#define                 OUTZ_H_REG_M                    0x6D

#define LSM303AH_FROM_FS_2g_TO_mg(lsb)    (float)(lsb *  61.0f) / 1000.0f
#define LSM303AH_FROM_FS_4g_TO_mg(lsb)    (float)(lsb * 122.0f) / 1000.0f
#define LSM303AH_FROM_FS_8g_TO_mg(lsb)    (float)(lsb * 244.0f) / 1000.0f
#define LSM303AH_FROM_FS_16g_TO_mg(lsb)   (float)(lsb * 488.0f) / 1000.0f

typedef enum {
        power_down,
        low_power,
        high_resolution,
        high_frequency
} lsm303_power_mode_t;

typedef struct {
        uint8_t output_data_rate;
        uint8_t full_scale;
        uint8_t high_frequency_odr;
        uint8_t block_data_update;
} lsm303_ctrl_1;

typedef enum {
        fifo_turned_off,
        fifo_mode,
        reserved,
        continuous_to_fifo,
        bypass_to_fifo,
        reserved_2,
        continuous_mode,
} lsm303_fifo_mode;

typedef enum {
        accel,
        mag
} lsm303_device_t;

typedef struct {
        float x_out;
        float y_out;
        float z_out;
} lsm303_accel_data_t;


uint8_t lsm303_check_ids(void);
uint8_t lsm303_init_accel(void);
void lsm303_read_out_fifo(lsm303_accel_data_t *data);
void read_sensor_data();
uint8_t lsm303_get_data_ready_status();
uint8_t lsm303_get_free_fall_status();
#endif /* INC_LSM303AH_H_ */
