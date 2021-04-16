/*
 * tasks.h
 *
 *  Created on: 18.04.2019
 *      Author: Felix Sch�tte
 */
#include "osal.h"
#ifndef INC_TASKS_H_
#define INC_TASKS_H_

/*
 * Measurement tast
 */
OS_TASK measurement_task_handle;
#define CHANGE_MEAS_TIMER_PERIOD                (1 << 2)
#define MEASUREMENT_DONE_NOTIF                  (1 << 3)
#define MEASUREMENT_ACCEL_NOTIF                 (1 << 4)

/*
 * Bluetooth peripheral task
 */
OS_TASK ble_peripheral_handle;
#define PRESENCE_ADVERTISEMENT                  (1 << 2)
#define WAKEUP_ADVERTISEMENT                    (1 << 3)
#define DATA_ADVERTISEMENT                      (1 << 4)

/*
 * COM Service
 */
OS_TASK com_service_handle;
#define SECOND_CNT_NOTIF                        (1 << 1)
#define DISCONNECT_CLIENTS_NOTIF                (1 << 2)

#endif /* INC_TASKS_H_ */
