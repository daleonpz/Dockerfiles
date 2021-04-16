/*
 * com_service.c
 *
 *  Created on: 21.01.2019
 *      Author: Felix Sch�tte
 */
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "SEGGER_RTT.h"
#include "ble_storage.h"
#include "ble_service.h"
#include "ble_uuid.h"
#include "ble_bufops.h"
//#include "si7060.h"
//#include "tsl2591.h"
#include "hw_wkup.h"
#include "measurement_routine.h"
#include "aes-ccm.h"
#include "sbt.h"
#include "FreeRTOS.h"
#include "sys_rtc.h"
#include "tasks.h"
#include "FreeRTOS.h"
#include "task.h"
#include "sys_watchdog.h"
#include "debug_log.h"
#include "digital_roller.h"
#include "led.h"
/*
 * Definition of the needed UUIDs for the communication service (COM)
 * and its characteristics (IN & OUT)
 *  */

#define BLE_NOTIF_TIMER     30000

PRIVILEGED_DATA static OS_MUTEX mutex;

PRIVILEGED_DATA static OS_TIMER test_sample_timer;

static void connected_evt(ble_service_t *svc, const ble_evt_gap_connected_t *evt);

static void disconnected_evt(ble_service_t *svc, const ble_evt_gap_connected_t *evt);

aes_ccm_key_t session_keyz = { { 0x18, 0x61, 0x29, 0x28, 0xB7, 0x58, 0x53, 0xD8, 0xBF, 0x17, 0xDF,
        0xEC, 0x7A, 0xD1, 0x3B, 0xC1 } };

uint8_t dummy[] = { 0x5C, 0xE6, 0x93, 0x21, 0xE9, 0x59, 0x3A, 0xEC, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x69, 0xB0, 0x62, 0x4C, 0xBC, 0x9B, 0xA6, 0xAE, 0xF8, 0x0F, 0xE1, 0x50, 0xF4,
        0xC8, 0x06, 0xD6, 0x71, 0xB0, 0x90, 0xF7, 0xD5, 0xCC, 0x26, 0x5C, 0x4D, 0x94, 0xCD, 0xE5,
        0x72, 0xD0, 0xF7, 0x9A, 0x78, 0xF3, 0x2B, 0xC2, 0xB8, 0xB6, 0x5B, 0x12, 0xAB, 0x58, 0xBF,
        0xB5, 0x8B, 0x1B, 0xD9 };

/*
 * Definition of handles for the characteristics and descriptors
 * Needed for the handling of read and write requests
 * */
typedef struct {
        ble_service_t svc;

        /* Handles */
        uint16_t IN_h;
        uint16_t OUT_h;
        uint16_t OUT_ccc_h;

} COM_Service_t;

uint8_t selfCountChar = 0;

static void cleanup(ble_service_t *svc)
{
        COM_Service_t *COM_Service = (COM_Service_t *)svc;
        OS_FREE(COM_Service);
}

static void connected_evt(ble_service_t *svc, const ble_evt_gap_connected_t *evt)
{
        uint16_t conn_idx = evt->conn_idx;
        reset_current_msg_queue_element();
        debug_log("CONNECTED conn_idx= %d", conn_idx);
        OS_TASK_NOTIFY(OS_GET_CURRENT_TASK(), SECOND_CNT_NOTIF, OS_NOTIFY_SET_BITS);
}

static void disconnected_evt(ble_service_t *svc, const ble_evt_gap_connected_t *evt)
{
        uint16_t conn_idx = evt->conn_idx;
        reset_current_msg_queue_element();
        debug_log("DISCONNECTED conn_idx=%d", conn_idx);
        start_ble_adv_transInt_timer();
}

static void handle_read_req(ble_service_t *svc, const ble_evt_gatts_read_req_t *evt)
{
        OS_MUTEX_GET(mutex, OS_MUTEX_FOREVER);
        COM_Service_t *COM_Service = (COM_Service_t *)svc;
        sbt_transmission_string trans_string = { 0 };
        uint8_t chk = EXIT_FAILURE;

        debug_log("Read Request");
        print_msg_list();
        sbt_msg_queue_fill();
        if (evt->handle == COM_Service->OUT_h) {
                chk = sbt_get_next_trans_string(&trans_string);
                if (chk == EXIT_SUCCESS) {
                        ble_gatts_read_cfm(evt->conn_idx, evt->handle, ATT_ERROR_OK,
                                trans_string.size * sizeof(uint8_t), trans_string.string);
#if SBT_DEBUG_ENABLED
                        debug_log("FRAME SENT VIA BLE: ");
                        for (int i = 0; i < trans_string.size; i++) {
                                printf("%02X", trans_string.string[i]);
                        }
                        printf("\r\n");
#endif
                        sbt_delete_pending_actuator_ack(&trans_string);
                        OS_FREE(trans_string.string);
                }

}      else {
                ble_gatts_read_cfm(evt->conn_idx, evt->handle, ATT_ERROR_READ_NOT_PERMITTED, 0,
                NULL);
        }
        OS_MUTEX_PUT(mutex);
}

static void handle_write_req(ble_service_t *svc, const ble_evt_gatts_write_req_t *evt)
{
        OS_MUTEX_GET(mutex, OS_MUTEX_FOREVER);
        COM_Service_t *COM_Service = (COM_Service_t *)svc;
        att_error_t err = ATT_ERROR_WRITE_NOT_PERMITTED;

        if (evt->handle == COM_Service->IN_h) {
                debug_log("COM service IN:  %d bytes got written", evt->length);
                sbt_packet_t packet = { 0 };
                packet.msg_datagram = OS_MALLOC(sizeof(sbt_msg_datagram_t));
                sbt_process_msg((uint8_t *)evt->value, evt->length, &packet);
                err = ATT_ERROR_OK;
                OS_FREE(packet.msg_datagram);
        }

        else if (evt->handle == COM_Service->OUT_ccc_h) {
                debug_log("Write Request on OUT");
                uint16_t ccc;

                if (evt->offset) {
                        err = ATT_ERROR_ATTRIBUTE_NOT_LONG;
                } else if (evt->length != sizeof(ccc)) {
                        err = ATT_ERROR_APPLICATION_ERROR;
                } else {
                        ccc = get_u16(evt->value);
                        ble_storage_put_u32(evt->conn_idx, COM_Service->OUT_ccc_h, ccc,
                        false);
                        err = ATT_ERROR_OK;
                }
        }

        ble_gatts_write_cfm(evt->conn_idx, evt->handle, err);
        OS_MUTEX_PUT(mutex);
}

ble_service_t *COM_Service_init()
{

        COM_Service_t *COM_Service = OS_MALLOC(sizeof(COM_Service_t));
        memset(COM_Service, 0, sizeof(COM_Service_t));

        COM_Service->svc.read_req = handle_read_req;
        COM_Service->svc.write_req = handle_write_req;
        COM_Service->svc.cleanup = cleanup;
        COM_Service->svc.connected_evt = connected_evt;
        COM_Service->svc.disconnected_evt = (disconnected_evt_t)disconnected_evt;

        /* COM Service UUID */
        att_uuid_t uuid;
        ble_uuid_from_string(UUID_COM_SERVICE, &uuid);

        /* Define COM service consisting of 2 characterisitics and 1 descriptor */
        uint16_t num_attr = ble_service_get_num_attr(0, 2, 1);
        ble_gatts_add_service(&uuid, GATT_SERVICE_PRIMARY, num_attr);

        /* IN characteristic */
        ble_uuid_from_string(UUID_IN_CHARACTERISTIC, &uuid);
        ble_gatts_add_characteristic(&uuid, GATT_PROP_WRITE, ATT_PERM_WRITE, 200 * sizeof(uint8_t),
                GATTS_FLAG_CHAR_READ_REQ, NULL, &COM_Service->IN_h);

        /* OUT characteristic */
        ble_uuid_from_string(UUID_OUT_CHARACTERISTIC, &uuid);
        ble_gatts_add_characteristic(&uuid, GATT_PROP_READ, ATT_PERM_RW, 5120 * sizeof(uint8_t),
                GATTS_FLAG_CHAR_READ_REQ, NULL, &COM_Service->OUT_h);
        ble_uuid_create16(UUID_GATT_CLIENT_CHAR_CONFIGURATION, &uuid);
        ble_gatts_add_descriptor(&uuid, ATT_PERM_RW, 2, 0, &COM_Service->OUT_ccc_h);

        /* Register service */
        ble_gatts_register_service(&COM_Service->svc.start_h, &COM_Service->IN_h,
                &COM_Service->OUT_h, &COM_Service->OUT_ccc_h, 0);

        // uint8_t num_attr = 1;
        COM_Service->svc.end_h = COM_Service->svc.start_h + num_attr;

        ble_service_add(&COM_Service->svc);

        return &COM_Service->svc;
}

void disconnect_clients()
{
        uint8_t num_conn;
        uint16_t *conn_idx;
        ble_gap_get_connected(&num_conn, &conn_idx);

        while (num_conn--) {
                ble_gap_disconnect(conn_idx[num_conn], BLE_HCI_ERROR_AUTH_FAILURE);
        }

        if (conn_idx) {
                OS_FREE(conn_idx);
        }
}

void second_cnt_cb(OS_TIMER timer)
{
        printf("SYSTEM: Heap size: %d \r\n", xPortGetFreeHeapSize());
        printf("SBT STATUS: %d \t (0: No time set, 1: not initialized, 2: initialized)\r\n",
                sbt_get_device_status());
        printf("SYSTEM: Elements stored %"PRIu32" \r\n", sbt_get_data_point_cnt());
        printf("MSG QUEUE: %d elements in queue. \r\n", sbt_msg_queue_get_cnt());

        if (sbt_msg_queue_get_cnt() != 0) {
                print_session_key();
                print_msg_list();
        }
}

void COM_Service_Task(void *params)
{
        int8_t wdog_id = sys_watchdog_register(false);

        printf("COM Service Task alive \r\n");
        ble_service_t *COM_Service = params;

        test_sample_timer = OS_TIMER_CREATE("COM Service", OS_MS_2_TICKS(BLE_NOTIF_TIMER), true,
                (void *) OS_GET_CURRENT_TASK(), second_cnt_cb);
        OS_ASSERT(test_sample_timer);

        OS_TASK_CREATE("Measurement Task", measurement_routine_task, NULL, 1024,
                MEASUREMENT_TASK_PRIORITY, measurement_task_handle);
        OS_ASSERT(measurement_task_handle);

        OS_TIMER_START(test_sample_timer, OS_TIMER_FOREVER);
        sbt_init();

        led_error_constant_bright_func();

        OS_MUTEX_CREATE(mutex);

        while (1) {
                OS_BASE_TYPE ret;
                uint32_t notif;

// notify watchdog on each loop
                sys_watchdog_notify(wdog_id);

// suspend watchdog while blocking on OS_TASK_NOTIFY_WAIT()
                sys_watchdog_suspend(wdog_id);
//printf("SYSTEM [COM SERVICE TASK]: Stack size: %d \r\n", (int) uxTaskGetStackHighWaterMark(OS_GET_CURRENT_TASK()));
// wait on any notification, and then clear all bits
                ret = OS_TASK_NOTIFY_WAIT(0, OS_TASK_NOTIFY_ALL_BITS, &notif,
                        OS_TIME_TO_TICKS(100000));

// resume watchdog
                sys_watchdog_notify_and_resume(wdog_id);

                if (ret == OS_TASK_NOTIFY_FAIL) {

                        /* no notification */
                        printf("No Notification for COM Service... \r\n");
                        continue;
                }

                if (notif & DISCONNECT_CLIENTS_NOTIF) {
                        printf("COM Service: disconnecting all clients now \r\n");
                        disconnect_clients();
                }

                if (notif & SECOND_CNT_NOTIF) {
                        if (sbt_get_device_status() == initialized) {
                                // sbt_msg_queue_fill();
                        }
                }

                if (sbt_is_storage_empty() == false && sbt_get_device_status() == initialized) {
                        // send_ble_notification(COM_Service);
                }

        }
}

