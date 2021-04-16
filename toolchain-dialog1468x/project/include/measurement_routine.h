/*
 * measurement_routine.h
 *
 *  Created on: 15.03.2019
 *      Author: Felix Sch�tte
 */

#ifndef INC_MEASUREMENT_ROUTINE_H_
#define INC_MEASUREMENT_ROUTINE_H_

#include "osal.h"

#define MEASUREMENT_ROUTINE_DEBUG                       1
#define MEASUREMENT_TASK_PRIORITY        ( OS_TASK_PRIORITY_NORMAL)

#define NUMBER_POF_NTC_SENS                     (7)

void measurement_routine_task(void *params);
void new_measurement_available();

#endif /* INC_MEASUREMENT_ROUTINE_H_ */
