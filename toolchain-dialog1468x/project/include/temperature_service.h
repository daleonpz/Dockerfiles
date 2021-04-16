/*
 * temperature_service.h
 *
 *  Created on: 17.01.2019
 *      Author: Martin
 */

#ifndef TEMPERATURE_SERVICE_H_
#define TEMPERATURE_SERVICE_H_

#include <stdbool.h>
#include <stdint.h>
#include <ble_service.h>

#define TEMPERATURE_TASK_PRIORITY              ( OS_TASK_PRIORITY_NORMAL )

#define READ_TEMP_NOTIF            (1 << 1)
#define TEMP_CONNECTED                (1 << 2)
#define TEMP_DISCONNECTED             (1 << 4)

typedef enum {ch_0 = 0, ch_1 = 1, ch_2 = 2, ch_3 = 3, ch_4 = 4, ch_5 = 5, ch_6 = 6, vbat = 7} channel_config_t;
channel_config_t channel;

ble_service_t *temperature_service_init(void);

uint16_t get_temperature(channel_config_t channel);

void temperature_service_task(void *params);

#endif /* TEMPERATURE_SERVICE_H_ */
