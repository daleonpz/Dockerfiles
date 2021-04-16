/*
 * storage.h
 *
 *  Created on: 10.04.2019
 *      Author: Felix Sch�tte
 */
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#ifndef INC_SBT_STORAGE_H_
#define INC_STORAGE_H_

#define SBT_MSG_QUEUE_MAX                                                           (10)
#define SBT_STORAGE_DEBUG_ENABLED                                                   (1)
#define SBT_ELEMENTS_PER_FRAME                                                      (5)

typedef enum {
    storage_not_initialized = 0,
    storage_initialized = 1
} sbt_storage_status_t;

typedef struct {
    uint16_t key;
    uint16_t value;
    uint32_t timestamp;
} sbt_storage_data_point_t;

typedef struct sbt_msg_queue_element_t{
    struct sbt_msg_queue_element_t *next;
    uint8_t *msg;
    uint16_t msg_length;
    uint32_t id;
} sbt_msg_queue_element_t;

typedef struct{
    sbt_msg_queue_element_t *head;
    uint16_t max_capacity;
    uint16_t element_cnt;
}sbt_msg_queue_t;

typedef struct{
    uint part_size;
    uint head;
    uint tail;
    uint max_capacity;
    uint data_point_cnt;
}sbt_storage_handle_t;

uint8_t is_element_uninitialized(sbt_msg_queue_element_t *element);
uint8_t sbt_storage_init();
uint8_t sbt_storage_add_datapoint(sbt_storage_data_point_t *data_point);
uint8_t sbt_storage_get_next_data_point(sbt_storage_data_point_t *data_point);
bool sbt_is_storage_empty(void);
uint32_t sbt_get_data_point_cnt(void);
uint16_t sbt_msg_queue_data_points_to_store();
void sbt_msg_queue_append(uint8_t **trans_string, uint16_t string_size);
uint16_t sbt_msg_queue_get_cnt();
uint8_t is_element_in_queue(sbt_msg_queue_element_t *element_to_find);
uint8_t sbt_msg_queue_iterate_through(sbt_msg_queue_element_t *current);
uint8_t sbt_msg_queue_remove_by_id(uint32_t id);
uint32_t sbt_msg_queue_get_msg_id(uint8_t **trans_string);
void print_msg_list();
uint8_t is_last_element_of_msg_queue(uint32_t id);
#endif /* INC_SBT_STORAGE_H_ */
