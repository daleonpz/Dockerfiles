/*
 * lsm303ah.c
 *
 *  Created on: 11.03.2019
 *      Author: Felix Sch�tte
 */
#include "lsm303ah.h"
#include "ad_i2c.h"
#include <stdlib.h>
#include <platform_devices.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

//static uint8_t lsm303_check_ids(void);
static void lsm303_read_reg(uint8_t reg, uint8_t *rbuf, uint8_t len, lsm303_device_t device);
static void lsm303_write_reg(uint8_t reg, uint8_t *wbuf, uint8_t len, lsm303_device_t device);
static uint8_t lsm303_set_data_rate_accel(lsm303_power_mode_t mode, uint8_t data_rate, uint8_t scale, uint8_t bdu);
static void lsm303_configure_interrupt_pins_accel(void);
static uint8_t lsm303_get_data_rate_accel(lsm303_power_mode_t *power_mode, uint8_t *scale);
static uint32_t estimate_odr(uint8_t odr, lsm303_power_mode_t *mode);
static void lsm303_set_fifo_mode(lsm303_fifo_mode mode, uint8_t fifo_threshold);
static uint8_t lsm303_read_status_reg_accel(uint8_t reg);
static uint8_t lsm303_get_output_data_accel(lsm303_accel_data_t *data);
static int convert_2s_complement(int number, uint32_t bits);
static void lsm303_get_fifo_samples(uint16_t *fifo_storage);
static uint8_t lsm303_configure_free_fall(uint8_t duration, uint8_t threshold);
static void lsm303_convert_raw_accel_data(lsm303_accel_data_t *data, uint8_t scale);

uint8_t lsm303_init_accel() {
    if (lsm303_check_ids() != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }
    lsm303_get_data_ready_status();
    lsm303_set_data_rate_accel(low_power, 0, 1, 1);
    lsm303_configure_interrupt_pins_accel();
//     lsm303_set_fifo_mode(continuous_mode, 10);
    lsm303_set_fifo_mode(fifo_turned_off, 10);
    lsm303_configure_free_fall(0, 0);
    return EXIT_SUCCESS;
}

void read_sensor_data(uint32_t *norm) {
    lsm303_accel_data_t data = { 0 };
    lsm303_get_output_data_accel(&data);
//     lsm303_read_out_fifo(&data);
    *norm = sqrt(pow((int)data.x_out, 2) + pow((int)data.y_out, 2) + pow((int)data.z_out, 2));
    lsm303_read_status_reg_accel(STATUS_DUP_A);
}

static void lsm303_read_reg(uint8_t reg, uint8_t *rbuf, uint8_t len, lsm303_device_t device) {
    i2c_device dev = ad_i2c_open(ACCEL);
    if (device == mag) {
        dev = ad_i2c_open(MAG);
    }

    ad_i2c_transact(dev, &reg, 1, rbuf, len);
    ad_i2c_close(dev);
}

static void lsm303_write_reg(uint8_t reg, uint8_t *wbuf, uint8_t len, lsm303_device_t device) {
    i2c_device dev = ad_i2c_open(ACCEL);
    if (device == mag) {
        dev = ad_i2c_open(MAG);
    }
    uint8_t new_write_buffer[len + 1];
    new_write_buffer[0] = reg;
    memcpy(new_write_buffer + 1, wbuf, len);
    ad_i2c_write(dev, new_write_buffer, len + 1);
    ad_i2c_close(dev);
}

uint8_t lsm303_check_ids(void) {
    uint8_t accel_address = 0;
    uint8_t mag_address = 0;

    lsm303_read_reg(WHO_AM_I_A, &accel_address, 1, accel);
    lsm303_read_reg(WHO_AM_I_M, &mag_address, 1, mag);
    if (accel_address != 0x43 || mag_address != 0x40) {
        return EXIT_FAILURE;
    }
#if LSM_DEBUG_ENABLED
    printf("Accelerometer ID: %d \r\n", accel_address);
    printf("Magnetometer ID: %d \r\n", mag_address);
#endif
    return EXIT_SUCCESS;
}

static uint8_t lsm303_set_data_rate_accel(lsm303_power_mode_t mode, uint8_t data_rate, uint8_t scale, uint8_t bdu) {
    lsm303_ctrl_1 reg = { 0 };
    uint8_t ctrl_1_a_reg = 0;
    reg.full_scale = scale & 0x03;
    reg.block_data_update = bdu & 0x01;

    if (mode == power_down) {
        reg.output_data_rate = 0;
        reg.full_scale = 0;
        reg.high_frequency_odr = 0;
        reg.block_data_update = 0;
    } else if (mode == low_power) {
        reg.output_data_rate = 0x08 | (data_rate & 0x07);
        reg.high_frequency_odr = 0;
    } else if (mode == high_resolution) {
        reg.output_data_rate = (data_rate & 0x07);
        reg.high_frequency_odr = 0;
    } else if (mode == high_frequency) {
        reg.output_data_rate = 0x04 | (data_rate & 0x03);
        reg.high_frequency_odr = 1;
    } else {
        return EXIT_FAILURE;
    }

    ctrl_1_a_reg = (reg.output_data_rate << 4) | (reg.full_scale << 2) | (reg.high_frequency_odr << 1) | (reg.block_data_update);
    lsm303_write_reg(CTRL1_A, &ctrl_1_a_reg, 1, accel);
    return EXIT_SUCCESS;
}

static uint8_t lsm303_get_data_rate_accel(lsm303_power_mode_t *power_mode, uint8_t *scale) {
    uint8_t ctrl_reg = 0;
    uint8_t odr = 0;
    uint32_t frequency = 0;

    lsm303_read_reg(CTRL1_A, &ctrl_reg, 1, accel);
    *scale = (12 & ctrl_reg) >> 2;
    odr = (ctrl_reg >> 4);
    if (odr & 0x08) {
        *power_mode = low_power;
    } else if (ctrl_reg & 0x02) {
        *power_mode = high_frequency;
    } else if ((odr & 0x07) && (*power_mode != high_frequency)) {
        *power_mode = high_resolution;
    } else {
        return EXIT_FAILURE;
    }
#if LSM_DEBUG_ENABLED
    frequency = estimate_odr(odr, power_mode);
    printf("Power mode: %d (0 = PD, 1 = LP, 2 = HR, 3 = HF) \r\n", *power_mode);
    printf("Accelerometer ODR: %d \r\n", (int) frequency);
#endif
    return EXIT_SUCCESS;
}

static uint32_t estimate_odr(uint8_t odr, lsm303_power_mode_t *mode) {
    odr = odr & 0x07;
    float frequency = 0;
    if (*mode != high_frequency) {
        frequency = 579023700 + (18.23217 - 579023700) / (1 + pow((odr / 155.8404), 4.357905));
        return (uint32_t) frequency;
    }
    if (odr == 7) {
        frequency = (uint32_t) 6400;
    }
    if (odr == 6) {
        frequency = (uint32_t) 3200;
    }
    if (odr == 5) {
        frequency = (uint32_t) 1600;
    }
    return frequency;
}

static void lsm303_configure_interrupt_pins_accel(void) {
    uint8_t ctrl_4_reg = 0;
    uint8_t ctrl_5_reg = 0;

    /* Free-fall recognition is routed on INT1 pad. */
    ctrl_4_reg = (1 << 4);
    lsm303_write_reg(CTRL4_A, &ctrl_4_reg, 1, accel);
    /* FIFO Threshold interrupt is routed on INT2 pad. */
    ctrl_5_reg = (1 << 1);
    lsm303_write_reg(CTRL5_A, &ctrl_5_reg, 1, accel);
}

static void lsm303_set_fifo_mode(lsm303_fifo_mode mode, uint8_t fifo_threshold) {
    /* set mode */
    uint8_t fifo_mode = mode & 0x7;
    fifo_mode = fifo_mode << 5;
    lsm303_write_reg(FIFO_CTRL_A, &fifo_mode, 1, accel);
    /* set FIFO threshold to throw an interrupt */
    lsm303_write_reg(FIFO_THS_A, &fifo_threshold, 1, accel);
}

static uint8_t lsm303_get_output_data_accel(lsm303_accel_data_t *data) {
    lsm303_power_mode_t mode = 0;
    uint8_t low_byte, high_byte;
    uint8_t scale = 0;

    lsm303_read_reg(OUT_X_L_A, &low_byte, 1, accel);
    lsm303_read_reg(OUT_X_H_A, &high_byte, 1, accel);
    data->x_out = (high_byte << 8) | low_byte;
    lsm303_read_reg(OUT_Y_L_A, &low_byte, 1, accel);
    lsm303_read_reg(OUT_Y_H_A, &high_byte, 1, accel);
    data->y_out = (high_byte << 8) | low_byte;
    lsm303_read_reg(OUT_Z_L_A, &low_byte, 1, accel);
    lsm303_read_reg(OUT_Z_H_A, &high_byte, 1, accel);
    data->z_out = (high_byte << 8) | low_byte;

    lsm303_get_data_rate_accel(&mode, &scale);
    lsm303_convert_raw_accel_data(data, scale);

#if LSM_DEBUG_ENABLED
    printf("X: %d \t", (int) data->x_out);
    printf("Y: %d \t", (int) data->y_out);
    printf("Z: %d \t", (int) data->z_out);
    printf("\r\n");
#endif

    return EXIT_SUCCESS;
}

static void lsm303_get_fifo_samples(uint16_t *fifo_storage) {
    uint8_t fifo_src_a = 0;
    uint8_t fifo_samples_a = 0;
    lsm303_read_reg(FIFO_SAMPLES_A, &fifo_samples_a, 1, accel);
    lsm303_read_reg(FIFO_SRC_A, &fifo_src_a, 1, accel);
    if (fifo_src_a & 32) {
        /* DIFF 8 is set -> FIFO is full */
        *fifo_storage = 256;
    } else {
        *fifo_storage = (uint16_t) fifo_samples_a;
    }
#if LSM_DEBUG_ENABLED
        printf("%d samples stored in FIFO \r\n", *fifo_storage);
#endif
}

static uint8_t lsm303_configure_free_fall(uint8_t duration, uint8_t threshold) {
    /* set free fall duration and threshold */
    uint8_t free_fall_a = 0;
    uint8_t wake_up_dur_a = 0;

    lsm303_read_reg(WAKE_UP_DUR_A, &wake_up_dur_a, 1, accel);
    lsm303_read_reg(FREE_FALL_A, &free_fall_a, 1, accel);
    free_fall_a = (duration & 0x1F) << 3 | (threshold & 0x3);
    wake_up_dur_a |= 16;
    if (duration & 0x20) {
        wake_up_dur_a |= (1 << 7);

    }
    lsm303_write_reg(FREE_FALL_A, &free_fall_a, 1, accel);
    lsm303_write_reg(WAKE_UP_DUR_A, &wake_up_dur_a, 1, accel);
    return EXIT_SUCCESS;
}

void lsm303_read_out_fifo(lsm303_accel_data_t *data) {
    uint16_t fifo_buffer = 0;
    lsm303_get_fifo_samples(&fifo_buffer);
    while(fifo_buffer > 0) {
        lsm303_get_output_data_accel(data);
        fifo_buffer--;
    }
}

static void lsm303_convert_raw_accel_data(lsm303_accel_data_t *data, uint8_t scale) {
    float scaling_factor[4] = { 61.0f, 488.0f, 122.0f, 244.0f };

    data->x_out = convert_2s_complement(data->x_out, 16) * scaling_factor[scale] / 1000;
    data->y_out = convert_2s_complement(data->y_out, 16) * scaling_factor[scale] / 1000;
    data->z_out = convert_2s_complement(data->z_out, 16) * scaling_factor[scale] / 1000;
}

static int convert_2s_complement(int number, uint32_t bits) {
    int _number = 0;
    uint16_t max_mask = (uint16_t) (1 << bits) - 1;
    if (number & (1 << (bits - 1))) {
        number = ((~number) & max_mask) + 1;
        _number = -number;
    } else {
        _number = number;
    }
    return _number;
}

static uint8_t lsm303_read_status_reg_accel(uint8_t reg) {
    uint8_t accel_status_reg;
    lsm303_read_reg(reg, &accel_status_reg, 1, accel);
#if LSM_DEBUG_ENABLED
    if (accel_status_reg & 0x01) {
        printf("Data-Ready - new data available \r\n");
    }
    if (accel_status_reg & 0x02) {
        printf("Free-fall event detected \r\n");
    }
    if (accel_status_reg & 0x03) {
        printf("A change in position detected \r\n");
    }
    if (accel_status_reg & 0x04) {
        printf("Single-tap event detected \r\n");
    }
    if (accel_status_reg & 0x05) {
        printf("Double-tap event detected \r\n");
    }
    if (accel_status_reg & 0x06) {
        printf("Sleep event detected \r\n");
    }
    if (accel_status_reg & 0x07) {
        printf("Wakeup event detected \r\n");
    }
    if (accel_status_reg & 0x08) {
        printf("FIFO filling is equal to or higher than the threshold level \r\n");
    }
#endif
    return accel_status_reg;
}

uint8_t lsm303_get_free_fall_status() {
    uint8_t free_fall_int = 0;
    free_fall_int = hw_gpio_get_pin_status(HW_GPIO_PORT_2, HW_GPIO_PIN_3);
//#if LSM_DEBUG_ENABLED
//        printf("Free Fall status: %d \r\n", free_fall_int);
//#endif
    return free_fall_int;
}

uint8_t lsm303_get_data_ready_status() {
    uint8_t data_ready_int = 0;
    data_ready_int = hw_gpio_get_pin_status(HW_GPIO_PORT_4, HW_GPIO_PIN_7);
#if LSM_DEBUG_ENABLED
    printf("Data Ready status: %d \r\n", data_ready_int);
#endif
    return data_ready_int;
}
