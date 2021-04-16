#ifndef _RADIO_H_
#define _RADIO_H_

#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#include "ATparser.h"
#include "board.h"
#include "gpio.h"
#include "hw_memmap.h"
#include "timer.h"
#include "uart.h"
#include "std_casted.h"

void radio_turn_on(void) ;

bool radio_connect(uint8_t * apn_server);
void radio_disconnect(void);

bool radio_send_data_to_cloud(uint8_t *data, uint8_t* mqtt_topic);
bool radio_get_data_from_cloud(uint8_t **data);

bool radio_subscribe_topic(uint8_t *mqtt_topic);
bool radio_unsubscribe_topic(uint8_t *mqtt_topic);
bool radio_subscribe_topic_and_get_data(uint8_t *mqtt_topic, uint8_t **data);

bool radio_connect_mqtt(uint8_t *broker, 
        uint8_t *mqtt_client,
        uint8_t *mqtt_userid, 
        uint8_t *mqtt_password);

bool radio_disconnect_mqtt(void);

uint8_t radio_get_signal_quality(void);
uint32_t radio_get_timestamp(void);
bool radio_network_registration(uint8_t number_of_tries);
bool radio_GPRS_network_registration(uint8_t number_of_tries);

#endif

