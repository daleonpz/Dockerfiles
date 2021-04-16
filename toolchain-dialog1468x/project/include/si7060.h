/*
 * si7060.h
 *
 *  Created on: 19.07.2018
 *      Author: jtl
 */

#ifndef INCLUDE_SI7060_H_
#define INCLUDE_SI7060_H_

#include <stdint.h>
#include <stdbool.h>
#include "ad_i2c.h"

#define SI7060_CHIPINFO 0xC0
#define SI7060_TEMP_H   0xC1    //T (�C) = 55+ (256*TEMP_H[6:0]+TEMP_L[7:0] -16384)/160
#define SI7060_TEMP_L   0xC2
#define SI7060_CTL1     0xC4
#define SI7060_CTL2     0xC5
#define SI7060_TEMP_SW1 0xC6
#define SI7060_TEMP_SW2 0xC7
#define SI7060_CTL3     0xC9

#define SI7060_CTL1_MEAS        0x80    //RO  indicates a measurement is in progress
#define SI7060_CTL1_SLEEP       0x01    //Setting this bit causes the part to enter sleep mode after the current measurement burst completes. Once set, clearing this bit restarts the measurement loop.
#define SI7060_CTL1_STOP        0x02    //Setting this bit causes the control state machine measurement loop to pause after the current measurement burst completes.Once set, clearing this bit restarts the measurement loop.
#define SI7060_CTL1_ONEBURST    0x04    //Setting this bit initiates a single conversion. Set stop = 0 when setting oneburst = 1. The stop bit will be set to 1 when the conversion completes.
#define SI7060_CTL1_USESTORE    0x08    //Setting this bit causes the current state of OTP registers for the sw_op, sw_hyst, sw_low4field, and sw_fieldpolsel bits to be
                                        //saved and restored during the next sleep and wakeup sequence instead of using the factory programmed default settings corresponding
                                        //to 80�C set point and 75�C release point.

#define SI7060_CTL2_ARAUTOINC    0x01   //enables auto increment of the I2C register address pointer. This bit is not retained in sleep mode.

#define SI7060_TEMP_SW1_OP       0x01   //ONLY THE MEAS 7 ARE SETTABLE; This 9 bit number sets the center point of the decision point for temperature high or low. The actual decision point is the center point plus or minus the hysteresis.
                                        //sw_op of 256 corresponds to a decision point of 55�C. The decision point will go up or down by 0.4�C as sw_op increases or decreases from this value.
#define SI7060_TEMP_SW1_LOW4TEMP 0x80   //determines the polarity of the output pin. The default setting of sw_low4temp = 1 means the pin will go low at high
                                        //temperature, e.g. sw_op + hysteresis. sw_low4temp = 0 means the pin will go high at low temperature, e.g., sw_op - hysteresis .
#define SI7060_TEMP_SW2_HYST     0x01   //6bit hysteresis = 0.025�C*(8 + sw_hyst[2:0]) � 2^sw_hyst[5:3] When sw_hyst = 63, the hysteresis is set to zero. These numbers can range from 0.2�C to 44.8�C
                                        //The operate point is threshold plus the hysteresis, and the release point is the threshold minus the hysteresis.
#define SI7060_CTL3_TIMEENA      0x80   //Enables the sleep timer. 0 means the part goes into complete sleep once the sleep bit is set. 1 means the parts will wake a
                                        //factory set interval between 1 and 200 msec, make a measurement, set the output pin value, and return to sleep.

void si7060_init(void);
void si7060_setConfig(bool low4temp, uint8_t temp, uint8_t hysteresis);
int8_t si7060_getTemperature(void);
void si7060_sleep();
void si7060_ulp_sleep(i2c_device dev);

#endif /* INCLUDE_SI7060_H_ */
