/*
 * sbt_config.h
 *
 *  Created on: Jan 24, 2020
 *      Author: root
 */

#include "aes-ccm.h"

#ifndef SBT_CONFIG_H_
#define SBT_CONFIG_H_

#define ADV_INTERVAL_MAX                50
#define ADV_INTERVAL_MIN                25

 extern aes_ccm_key_t master_key;

extern uint8_t sbt_device_id[4];

extern uint8_t sbt_uuid_presence[16];

extern uint8_t sbt_uuid_wakeup[16];

uint8_t sbt_uuid_data[16];

const char *dev_scan_local_name;

#endif /* SBT_CONFIG_H_ */
