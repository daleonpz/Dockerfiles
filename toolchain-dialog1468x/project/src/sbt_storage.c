/*
 * storage.c
 *
 *  Created on: 10.04.2019
 *      Author: Felix Sch�tte
 */
#include <string.h>
#include "sbt_storage.h"
#include "ad_nvms.h"
#include "osal.h"
#include "debug_log.h"

static nvms_t part_handle;
sbt_storage_handle_t storage_handle = { 0 };
sbt_msg_queue_t msg_queue = { 0 };
sbt_storage_status_t storage_status = storage_not_initialized;

uint8_t is_element_uninitialized(sbt_msg_queue_element_t *element)
{
        sbt_msg_queue_element_t empty_element = { 0 };

        if (memcmp(&empty_element, element, sizeof(sbt_msg_queue_element_t)) == 0) {
                debug_log("Given element is empty.");
                return EXIT_SUCCESS;
        }
        return EXIT_FAILURE;
}

uint8_t sbt_storage_init()
{
        if (storage_status == storage_not_initialized) {
                ad_nvms_init();
                storage_status = storage_initialized;
        }

        part_handle = ad_nvms_open(NVMS_GENERIC_PART);
        if (part_handle == NULL) {
                return EXIT_FAILURE;
        }

        storage_handle.part_size = ad_nvms_get_size(part_handle);
        storage_handle.max_capacity = (uint)storage_handle.part_size
                / sizeof(sbt_storage_data_point_t);
        msg_queue.max_capacity = SBT_MSG_QUEUE_MAX;
        ad_nvms_erase_region(part_handle, 0, storage_handle.part_size);

#ifdef SBT_STORAGE_DEBUG_ENABLED
        debug_log("SBT STORAGE: Storage successfully initialized, part size: %"PRIu32"",
                (uint32_t)storage_handle.part_size);
#endif

        return EXIT_SUCCESS;
}

static uint8_t storage_write(uint32_t addr, const uint8_t *buf, uint32_t size)
{
        int written_length = 0;

        while (size > 0) {
                written_length = ad_nvms_write(part_handle, addr, buf, size);
                if (written_length < 0) {
                        return EXIT_FAILURE;
                }
                size -= written_length;
                addr += written_length;
                buf += written_length;
        }
        return EXIT_SUCCESS;
}

uint8_t storage_read(uint32_t addr, uint8_t *buf, uint32_t size)
{
        int read_length = 0;

        while (size > 0) {
                read_length = ad_nvms_read(part_handle, addr, buf, size);
                if (read_length < 0) {
                        return EXIT_FAILURE;
                }
                size -= read_length;
                addr += read_length;
                buf += read_length;
        }
        return EXIT_SUCCESS;
}

bool sbt_is_storage_empty(void)
{
        bool chk =
                (storage_handle.data_point_cnt > 0) || (msg_queue.element_cnt > 0) ? false : true;
        return chk;
}

uint32_t sbt_get_data_point_cnt(void)
{
        return storage_handle.data_point_cnt;
}

uint8_t sbt_storage_add_datapoint(sbt_storage_data_point_t *data_point)
{
        uint8_t chk = 0;
        ad_nvms_erase_region(part_handle, storage_handle.tail, sizeof(sbt_storage_data_point_t));
        chk = storage_write(storage_handle.tail, (uint8_t *)data_point,
                sizeof(sbt_storage_data_point_t));
        storage_handle.tail = (storage_handle.tail + sizeof(sbt_storage_data_point_t))
                % storage_handle.part_size;
        if (storage_handle.data_point_cnt < storage_handle.max_capacity) {
                storage_handle.data_point_cnt++;
        }
        return chk;
}

uint8_t sbt_storage_get_next_data_point(sbt_storage_data_point_t *data_point)
{
        uint8_t chk = EXIT_FAILURE;

        if (sbt_is_storage_empty() == false) {
                chk = storage_read(storage_handle.head, (uint8_t *)data_point,
                        sizeof(sbt_storage_data_point_t));
                storage_handle.head = (storage_handle.head + sizeof(sbt_storage_data_point_t))
                        % storage_handle.part_size;
                storage_handle.data_point_cnt--;
        } else {
                storage_handle.head = 0;
        }
        return chk;
}

uint32_t sbt_msg_queue_get_msg_id(uint8_t **trans_string)
{
        uint32_t packet_id = 0;

        for (uint8_t i = 7; i > 3; i--) {
                packet_id = packet_id | ((*trans_string)[i] << ((7 - i) * 8));
        }

        return packet_id;
}

uint16_t sbt_msg_queue_data_points_to_store()
{
        int elements_to_store = 0;
        int max_elements = 0;

        if (msg_queue.element_cnt < SBT_MSG_QUEUE_MAX && storage_handle.data_point_cnt > 0) {
                max_elements = (SBT_MSG_QUEUE_MAX - msg_queue.element_cnt) * SBT_ELEMENTS_PER_FRAME;
                elements_to_store =
                        storage_handle.data_point_cnt < max_elements ?
                                storage_handle.data_point_cnt : max_elements;
        } else {
                elements_to_store = 0;
        }
        return (uint16_t)elements_to_store;
}

void sbt_msg_queue_append(uint8_t **trans_string, uint16_t string_size)
{
        if (msg_queue.element_cnt == 0) {
                msg_queue.head = OS_MALLOC(sizeof(sbt_msg_queue_element_t));
        }
        sbt_msg_queue_element_t * current = msg_queue.head;

        if (msg_queue.element_cnt == 0) {
                current->msg = *trans_string;
                current->msg_length = string_size;
                current->next = NULL;

        } else {
                while (current->next != NULL) {
                        current = current->next;
                }
                current->next = OS_MALLOC(sizeof(sbt_msg_queue_element_t));
                current->next->msg = *trans_string;
                current->next->msg_length = string_size;
                current->next->next = NULL;
        }
        msg_queue.element_cnt++;
}

uint8_t sbt_msg_queue_remove_by_id(uint32_t id)
{
        sbt_msg_queue_element_t * current = msg_queue.head;

        if (sbt_msg_queue_get_msg_id(&current->msg) == id) {

                if (current->next != NULL) {
                        msg_queue.head = current->next;
                }

                OS_FREE(current->msg);
                OS_FREE(current);
                msg_queue.element_cnt--;
                return EXIT_SUCCESS;
        }

        while (current->next != NULL) {

                if (sbt_msg_queue_get_msg_id(&current->next->msg) == id) {
                        sbt_msg_queue_element_t temp_node = { 0 };
                        temp_node.next = current->next->next;
                        OS_FREE(current->next->msg);
                        OS_FREE(current->next);
                        current->next = temp_node.next;
                        msg_queue.element_cnt--;
                        return EXIT_SUCCESS;
                }

                current = (current->next == NULL) ? current : current->next;
        }

        return EXIT_FAILURE;
}

uint16_t sbt_msg_queue_get_cnt()
{
        return msg_queue.element_cnt;
}

uint8_t is_element_in_queue(sbt_msg_queue_element_t *element_to_find)
{
        sbt_msg_queue_element_t _current = { 0 };
        uint8_t chk = EXIT_SUCCESS;
        uint8_t found = EXIT_FAILURE;

        while (chk == EXIT_SUCCESS && sbt_msg_queue_get_cnt() > 0) {
                chk = sbt_msg_queue_iterate_through(&_current);
                if (chk == EXIT_FAILURE) {
                        break;
                }

                if (_current.id == element_to_find->id) {
                        found = EXIT_SUCCESS;
                }
        }

        if (found == EXIT_FAILURE) {
                debug_log("Have not found element with id %02X", element_to_find->id);
        }
        return found;
}

uint8_t sbt_msg_queue_iterate_through(sbt_msg_queue_element_t *current)
{
        uint8_t chk = EXIT_FAILURE;

        if (current->msg == 0) {
                current->msg = (uint8_t *)msg_queue.head->msg;
                current->msg_length = msg_queue.head->msg_length;
                current->next = msg_queue.head->next;
                current->id = sbt_msg_queue_get_msg_id(&current->msg);
                chk = EXIT_SUCCESS;
        }

        else if (current->next != NULL) {
                current->msg = current->next->msg;
                current->msg_length = current->next->msg_length;
                current->next = current->next->next;
                current->id = sbt_msg_queue_get_msg_id(&current->msg);
                chk = EXIT_SUCCESS;
        }

        if (current->next == NULL && chk != EXIT_SUCCESS) {
                return EXIT_FAILURE;
        }

        return chk;
}

void print_msg_list()
{
        sbt_msg_queue_element_t _current = { 0 };
        uint8_t chk = EXIT_SUCCESS;
        if (sbt_msg_queue_get_cnt() > 0) {
                debug_log("Printing MSG LIST, %d elements in queue", sbt_msg_queue_get_cnt());
        }
        while (chk == EXIT_SUCCESS && sbt_msg_queue_get_cnt() > 0) {
                chk = sbt_msg_queue_iterate_through(&_current);
                if (chk == EXIT_FAILURE) {
                        break;
                }
                printf("MSG: \t ");
                for (int i = 0; i < _current.msg_length; i++) {
                        printf("%02X", _current.msg[i]);
                }
                printf("\r\n");

        }
        if (sbt_msg_queue_get_cnt() > 0) {
                printf("\r\n");
        }
}

uint8_t is_last_element_of_msg_queue(uint32_t id)
{
        sbt_msg_queue_element_t _current = { 0 };
        uint8_t chk = EXIT_SUCCESS;

        while (chk == EXIT_SUCCESS && sbt_msg_queue_get_cnt() > 0) {
                chk = sbt_msg_queue_iterate_through(&_current);
                if (chk == EXIT_FAILURE) {
                        break;
                }
        }

        if (id == _current.id) {
                chk = EXIT_SUCCESS;
        } else {
                chk = EXIT_FAILURE;
        }
        debug_log("ID to check: %02X \t ID of last element: %02X", id, _current.id);
        return chk;
}
