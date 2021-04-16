/*
 * si7060.c
 *
 *  Created on: 19.07.2018
 *      Author: jtl
 */

#include "si7060.h"
#include "ad_i2c.h"
#include <platform_devices.h>

void si7060_init(void)
{
//    i2c_device dev = ad_i2c_open(TEMP);
//    si7060_ulp_sleep(dev);
//    ad_i2c_close(dev);
}

void si7060_setConfig(bool low4temp, uint8_t temp, uint8_t hysteresis)
{

}

int8_t si7060_getTemperature()
{

        uint8_t _Dspsigm;
        uint8_t _Dspsigl;
        uint32_t result = 0;
        float factor = 0.00635;
        i2c_device dev = ad_i2c_open(TEMP);

        //wake
        uint8_t buf0[1] = { SI7060_CHIPINFO };
        ad_i2c_write(dev, buf0, 1);
        ad_i2c_read(dev, NULL, 1);

        //start measurement
        uint8_t buffer[2] = { SI7060_CTL1, SI7060_CTL1_ONEBURST }; //|SI7060_CTL1_SLEEP};
        ad_i2c_write(dev, buffer, 2);

        vTaskDelay(OS_MS_2_TICKS(10));

        uint8_t bufh[1] = { SI7060_TEMP_H };
        uint8_t bufl[1] = { SI7060_TEMP_L };
        ad_i2c_write(dev, bufh, 1);
        ad_i2c_read(dev, &_Dspsigm, 1);
//    ad_i2c_transact(dev,bufh,1,&_Dspsigm,1);

        ad_i2c_write(dev, bufl, 1);
        ad_i2c_read(dev, &_Dspsigl, 1);
//    ad_i2c_transact(dev,bufh,1,&_Dspsigl,1);

        si7060_ulp_sleep(dev);
//    uint8_t bufs[2] = {SI7060_CTL3,SI7060_CTL3_TIMEENA};
//    ad_i2c_write(dev,bufs,2);
        ad_i2c_close(dev);
        result = (int8_t)(55 + ((((_Dspsigm & 0x7F) << 8) + _Dspsigl - 16384) * factor));
        return result;
        printf("Temperature: %d ", (uint16_t)result);
}

void si7060_sleep()
{
        i2c_device dev = ad_i2c_open(TEMP);
        uint8_t buffer[2] = { SI7060_CTL1, SI7060_CTL1_STOP };
        ad_i2c_write(dev, buffer, 2);
        ad_i2c_close(dev);
}

void si7060_ulp_sleep(i2c_device dev)
{
        uint8_t buffer[2] = { SI7060_CTL1, SI7060_CTL1_SLEEP };
        ad_i2c_write(dev, buffer, 2);
}
