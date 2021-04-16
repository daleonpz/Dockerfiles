/*
 * my_test_service.h
 *
 *  Created on: 21.01.2019
 *      Author: Felix Schütte
 */

#ifndef COM_SERVICE_H_
#define COM_SERVICE_H_

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "osal.h"
#include "sys_watchdog.h"
#include "ble_att.h"
#include "ble_common.h"
#include "ble_gap.h"
#include "ble_gatts.h"
#include "ble_att.h"
#include "ble_service.h"
#include "ble_uuid.h"
#include "ble_peripheral_config.h"
#include "bas.h"
#include "cts.h"
#include "dis.h"
#include "scps.h"

/* custom includes */
ble_service_t *COM_Service_init();
void COM_Service_Task(void *params);

#endif /* MY_TEST_SERVICE_H_ */
