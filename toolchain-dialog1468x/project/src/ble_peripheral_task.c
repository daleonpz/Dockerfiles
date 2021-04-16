/**
 ****************************************************************************************
 *
 * @file ble_peripheral_task.c
 *
 * @brief BLE peripheral task
 *
 * Copyright (C) 2015-2018 Dialog Semiconductor.
 * This computer program includes Confidential, Proprietary Information
 * of Dialog Semiconductor. All Rights Reserved.
 *
 ****************************************************************************************
 */

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
#include "ble_service.h"
#include "ble_uuid.h"
#include "ble_peripheral_config.h"
#include "bas.h"
#include "cts.h"
#include "dis.h"
#include "scps.h"
#include <stdio.h>
#include "sbt.h"
#include "sys_trng.h"
#include "tasks.h"
#include "com_service.h"
#include "debug_log.h"
#include "hw_trng.h"
#include "debug_log.h"
#include "sbt_config.h"
/*
 * Notification bits reservation
 * bit #0 is always assigned to BLE event queue notification
 */
#define PRESENCE_ADV_TIMEOUT(rand)          (700000 + (rand % 21))
#define WAKEUP_ADV_TIMEOUT                  (50000)

PRIVILEGED_DATA static OS_TIMER presence_adv_timeout;
PRIVILEGED_DATA static OS_TIMER wakeup_adv_timeout;

static uint8_t scan_rsp_data[28] = { 0 };

static uint8_t adv_data[27] = { 0x1A, 0xFF, 0x4C, 0x00, 0x02, 0x15 };

/*
 * Device Information Service data
 */
#if CFG_DIS
#if CFG_DIS_FULL
static const dis_system_id_t dis_sys_id = { .oui = { 0x80, 0xEA, 0xCA }, // Dialog Semiconductor Hellas SA
        .manufacturer = { 0x0A, 0x0B, 0x0C, 0x0D, 0x0E }, };

// copied from "Personal Health Devices Transcoding White Paper", available on bluetooth.org
static const uint8_t dis_reg_cert[] = { 0x00, 0x02, 0x00, 0x12, 0x02, 0x01, 0x00, 0x08, 0x01, 0x05,
        0x00, 0x01, 0x00, 0x02, 0x80, 0x08, 0x02, 0x02, 0x00, 0x02,
        0x00, 0x00, };

static const dis_pnp_id_t dis_pnp_id = { .vid_source = 0x01,     // Bluetooth SIG
        .vid = 0x00D2,     //  Dialog Semiconductor B.V.
        .pid = 0x0001, .version = 0x0001, };
#endif

static const dis_device_info_t dis_info = { .manufacturer = "Q-loud GmbH", .model_number =
        "SBT Device",
        #if CFG_DIS_FULL
        // sample data
        .serial_number = "SBT-00-00-01", .hw_revision = "Rev 1", .fw_revision = "1.0",
        .sw_revision = "1.1", .system_id =
                &dis_sys_id,
        .reg_cert_length = sizeof(dis_reg_cert), .reg_cert = dis_reg_cert, .pnp_id = &dis_pnp_id,
#endif
        };
#endif // CFG_DIS

/*
 * Main code
 */
static void handle_evt_gap_connected(ble_evt_gap_connected_t *evt)
{
        /**
         * Manage connection information
         */

}

static void handle_evt_gap_disconnected(ble_evt_gap_disconnected_t *evt)
{
}

static void handle_evt_gap_adv_completed(ble_evt_gap_adv_completed_t *evt)
{
        // restart advertising so we can connect again
        ble_gap_adv_start(GAP_CONN_MODE_UNDIRECTED);
}

static void get_scan_rsp_data()
{
        // construct scan response object with device id string + presence uuid
        scan_rsp_data[0] = 9;
        scan_rsp_data[1] = GAP_DATA_TYPE_LOCAL_NAME;
        memcpy(scan_rsp_data + 2, dev_scan_local_name, 8);
        scan_rsp_data[10] = 17;
        scan_rsp_data[11] = GAP_DATA_TYPE_UUID128_LIST;
        for (int i = 0; i < 16; i++) {
                scan_rsp_data[i + 12] = sbt_uuid_presence[15 - i];
        }
}

void stop_timeout_timers()
{
        OS_TIMER_RESET(presence_adv_timeout, OS_TIMER_FOREVER);
        OS_TIMER_RESET(wakeup_adv_timeout, OS_TIMER_FOREVER);
        OS_TIMER_STOP(presence_adv_timeout, OS_TIMER_FOREVER);
        OS_TIMER_STOP(wakeup_adv_timeout, OS_TIMER_FOREVER);
}

static void start_presence_adv(void)
{
        OS_TIMER_CHANGE_PERIOD(presence_adv_timeout, PRESENCE_ADV_TIMEOUT(sys_trng_rand()),
                OS_TIMER_FOREVER);
        OS_TIMER_START(presence_adv_timeout, OS_TIMER_FOREVER);
        ble_gap_adv_stop();
        memcpy(adv_data + 6, sbt_uuid_presence, 16);
        memcpy(adv_data + 22, sbt_device_id, 4);
        adv_data[26] = 0xB6;
        get_scan_rsp_data();
        ble_gap_adv_data_set(sizeof(adv_data), adv_data, sizeof(scan_rsp_data), scan_rsp_data);
        ble_gap_adv_mode_set(GAP_DISC_MODE_GEN_DISCOVERABLE);
        ble_gap_adv_start(GAP_CONN_MODE_UNDIRECTED);
}

static void start_wakeup_adv(void)
{
        OS_TIMER_START(wakeup_adv_timeout, OS_TIMER_FOREVER);
        ble_gap_adv_stop();
        memcpy(adv_data + 6, sbt_uuid_wakeup, 16);
        memcpy(adv_data + 22, sbt_device_id, 4);
        adv_data[26] = 0xB6;
        get_scan_rsp_data();
        ble_gap_adv_data_set(sizeof(adv_data), adv_data, sizeof(scan_rsp_data), scan_rsp_data);
        ble_gap_adv_mode_set(GAP_DISC_MODE_GEN_DISCOVERABLE);
        ble_gap_adv_start(GAP_CONN_MODE_UNDIRECTED);
}

static void start_data_available_adv(void)
{
        stop_timeout_timers();
        ble_gap_adv_stop();
        memcpy(adv_data + 6, sbt_uuid_data, 16);
        memcpy(adv_data + 22, sbt_device_id, 4);
        adv_data[26] = 0xB6;
        get_scan_rsp_data();
        ble_gap_adv_data_set(sizeof(adv_data), adv_data, sizeof(scan_rsp_data), scan_rsp_data);
        ble_gap_adv_mode_set(GAP_DISC_MODE_GEN_DISCOVERABLE);
        ble_gap_adv_start(GAP_CONN_MODE_UNDIRECTED);
}

void presence_timeout_cb(OS_TIMER timer)
{
        debug_log("BLE: Presence timeout");
        stop_timeout_timers();
        start_wakeup_adv();
}

void wakeup_timeout_cb(OS_TIMER timer)
{
        debug_log("BLE: Wake up timeout");
        stop_timeout_timers();
        start_presence_adv();
}

void set_device_address()
{
        own_address_t addr;

        // generate random address
        hw_trng_enable(NULL);
        while (hw_trng_get_fifo_level() < 2)
                ;
        uint32_t random = hw_trng_get_number();
        addr.addr[0] = (random >> 24) & 0xff;
        addr.addr[1] = (random >> 16) & 0xff;
        addr.addr[2] = (random >> 8) & 0xff;
        addr.addr[3] = random & 0xff;
        random = hw_trng_get_number();
        addr.addr[4] = (random >> 8) & 0xff;
        addr.addr[5] = random & 0xff;
        addr.addr[5] |= 0xc0;   // set upper two bits to mark this as static random address
        hw_trng_disable();

        debug_log("BLE device address generated: %s",
                ble_address_to_string((const bd_address_t *)&addr));


        addr.addr_type = PRIVATE_STATIC_ADDRESS;
        ble_gap_address_set(&addr, 0);
}

void ble_peripheral_task(void *params)
{
        int8_t wdog_id;

        ble_service_t *svc;

        // in case services which do not use svc are all disabled, just surpress -Wunused-variable
        (void)svc;

        /* register ble_peripheral task to be monitored by watchdog */
        wdog_id = sys_watchdog_register(false);

        com_service_handle = OS_GET_CURRENT_TASK();

        srand(time(NULL));

        ble_peripheral_start();

        ble_register_app();

        set_device_address();

        ble_gap_mtu_size_set(512);

        ble_gap_device_name_set("SBT Node", ATT_PERM_READ);

#if CFG_USER_SERVICE
        /* register custom service */

        ble_service_t *COM_Service = COM_Service_init();

        OS_TASK_CREATE("COM Service Task", COM_Service_Task, COM_Service, 4096,
                OS_TASK_PRIORITY_NORMAL, com_service_handle);
        OS_ASSERT(com_service_handle);

        presence_adv_timeout = OS_TIMER_CREATE("Presence ADV Timeout Timer",
                OS_MS_2_TICKS(PRESENCE_ADV_TIMEOUT(sys_trng_rand())), true,
                (void *) OS_GET_CURRENT_TASK(), presence_timeout_cb);
        OS_ASSERT(presence_adv_timeout);
        wakeup_adv_timeout = OS_TIMER_CREATE("Wakeup ADV Timeout Timer",
                OS_MS_2_TICKS(WAKEUP_ADV_TIMEOUT), true, (void *) OS_GET_CURRENT_TASK(),
                wakeup_timeout_cb);
        OS_ASSERT(wakeup_adv_timeout);

#endif

#if CFG_DIS
        /* Add DIS */
        dis_init(NULL, &dis_info);
#endif

        start_presence_adv();
        for (;;) {
                OS_BASE_TYPE ret;
                uint32_t notif;

                /* notify watchdog on each loop */
                sys_watchdog_notify(wdog_id);

                /* suspend watchdog while blocking on OS_TASK_NOTIFY_WAIT() */
                sys_watchdog_suspend(wdog_id);
                //printf("SYSTEM [BLE TASK]: Stack size: %d \r\n", (int) uxTaskGetStackHighWaterMark(OS_GET_CURRENT_TASK()) );
                /*
                 * Wait on any of the notification bits, then clear them all
                 */
                ret = OS_TASK_NOTIFY_WAIT(0, OS_TASK_NOTIFY_ALL_BITS, &notif,
                        OS_TASK_NOTIFY_FOREVER);
                /* Blocks forever waiting for task notification. The return value must be OS_OK */
                OS_ASSERT(ret == OS_OK);

                /* resume watchdog */
                sys_watchdog_notify_and_resume(wdog_id);

                /* notified from BLE manager, can get event */
                if (notif & BLE_APP_NOTIFY_MASK) {
                        ble_evt_hdr_t *hdr;

                        hdr = ble_get_event(false);
                        if (!hdr) {
                                goto no_event;
                        }

                        if (ble_service_handle_event(hdr)) {
                                goto handled;
                        }

                        switch (hdr->evt_code) {
                        case BLE_EVT_GAP_CONNECTED:
                                handle_evt_gap_connected((ble_evt_gap_connected_t *)hdr);
                                break;
                        case BLE_EVT_GAP_ADV_COMPLETED:
                                handle_evt_gap_adv_completed((ble_evt_gap_adv_completed_t *)hdr);
                                break;
                        case BLE_EVT_GAP_DISCONNECTED:
                                handle_evt_gap_disconnected((ble_evt_gap_disconnected_t *)hdr);
                                break;
                        case BLE_EVT_GAP_PAIR_REQ: {
                                ble_evt_gap_pair_req_t *evt = (ble_evt_gap_pair_req_t *)hdr;
                                ble_gap_pair_reply(evt->conn_idx, true, evt->bond);
                                break;
                        }
                        default:
                                ble_handle_event_default(hdr);
                                break;
                        }

                        handled:
                        OS_FREE(hdr);

                        no_event:
                        // notify again if there are more events to process in queue
                        if (ble_has_event()) {
                                OS_TASK_NOTIFY(OS_GET_CURRENT_TASK(), BLE_APP_NOTIFY_MASK,
                                        eSetBits);
                        }
                } else if (notif & PRESENCE_ADVERTISEMENT) {
                        debug_log("BLE: Start presence advertisement");
                        start_presence_adv();
                } else if (notif & WAKEUP_ADVERTISEMENT) {
                        debug_log("BLE: Start Wake up advertisement");
                } else if (notif & DATA_ADVERTISEMENT) {
                        debug_log("BLE: Start Data available advertisement");
                        start_data_available_adv();
                }

        }
}
