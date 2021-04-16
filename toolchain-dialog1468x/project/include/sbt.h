//
// Created by Felix Sch�tte on 18.03.2019.
//
#include <inttypes.h>
#include "sbt_storage.h"
#include "aes-ccm.h"

#ifndef SBT_PROTOCOL_SBT_LAYER_H
#define SBT_PROTOCOL_SBT_LAYER_H

#define SBT_DEBUG_ENABLED                       (1)
#define SBT_DATAGRAM_FRAME_OVERHEAD             (18)
#define SBT_FRAME_SIZE(msg_datagram_size)       (SBT_DATAGRAM_FRAME_OVERHEAD + msg_datagram_size)
#define SBT_TIME_MSG_SIZE                       (7)
#define SBT_TIME_REQ_SIZE                       (3)
#define SBT_INIT_MSG_SIZE                       (22)
#define SBT_SENSOR_DATA_MSG_SIZE(value_length)  (9 + (value_length))
#define SBT_ACTUATOR_CMD_SIZE                   (9 + (cmd_length))
#define SBT_MAC_SIZE                            (4)
#define SBT_MAX_FRAME_SIZE                      (200)
#define SBT_MIN_FRAME_SIZE                      (17)
#define SBT_TIME_RESP_DATAGRAM_SIZE             (21)
#define SBT_INIT_RESP_DATAGRAM_SIZE             (40)
#define SBT_DATA_RESP_DATAGRAM_SIZE             (18)
#define SBT_MIN_ACT_CMD_SIZE                    (24)
#define SBT_ACT_ACK_FRAME_SIZE                  (18)
#define SBT_NONCE_SIZE                          (10)
#define UUID_COM_SERVICE                     "342EC847-69E1-4A5B-A531-095B60F93682"
#define UUID_IN_CHARACTERISTIC               "A2ADEE26-C400-424B-913E-FA29BBEAF050"
#define UUID_OUT_CHARACTERISTIC              "F89FD874-FD5C-40D7-8051-028A4413C500"
#define UUID_PRESENCE                        "706C5986-FBA2-4C73-9BF6-49AF1CB15F70"
#define UUID_WAKEUP                          "584201EC-f8E2-4967-8841-4D2C5EB4DFE6"
#define UUID_DATA                            "F4C41312-9B1D-4833-805A-1474A55DE57D"
#define SBT_TIME_MSG_TYPE                       (0)
#define SBT_TIME_INIT_TYPE                      (1)
#define SBT_DATA_MSG_TYPE                       (2)
#define SBT_ACTUATOR_CMD_TYPE                   (3)
#define SBT_INIT_TIMEOUT                        (7000)
#define SBT_DEFAULT_SESSION_TTL                 (1440*60*1000)
#define SBT_SESSION_TTL(ttl)                    ((ttl * 60 * 1000) - 120)
#define SBT_ACTUATOR_TTL                        (5000)
#define RTC_FREQUENCY                           (32768)
#define SBT_DATA_POINTS_PER_PACKERT             (5)
#define SBT_EMPTY_STRING_SIZE                   (14)
#define PRESENCE_ADVERTISEMENT (1 << 2)
#define WAKEUP_ADVERTISEMENT (1 << 3)
#define DATA_ADVERTISEMENT (1 << 4)

typedef struct {
        uint8_t fin :1;
        uint8_t ack :1;
        uint8_t aad :1;
        uint8_t psk :1;
        uint8_t ncr :1;
        uint8_t cis :3;
        uint8_t res :5;
        uint8_t ver :3;
} sbt_flags_t;

typedef struct {
        uint8_t kapt;
        uint16_t ttl;
        uint8_t session_key[16];
} sbt_init_t;

typedef struct {
        uint32_t data_time;
        uint16_t data_key;
        uint8_t data_value[2];
} sbt_sensor_data_t;

typedef struct {
        uint16_t data_key;
        uint8_t *cmd;
} sbt_actuator_cmd_t;

typedef union {
        sbt_init_t init;
        uint32_t timestamp;
        sbt_sensor_data_t sensor_data;
        sbt_actuator_cmd_t act_cmd;
} msg_payload_t;

typedef struct {
        uint8_t type;
        uint16_t length;
        msg_payload_t payload;
} sbt_msg_datagram_t;

typedef struct {
        uint32_t time;
        uint32_t packet_id;
        sbt_flags_t flags;
        uint32_t ack;
        sbt_msg_datagram_t *msg_datagram;
        uint32_t mac;
        uint32_t msg_datagram_size;
        uint16_t msg_datagram_cnt;
} sbt_packet_t;

typedef enum {
        sbt_time_msg = 0,
        sbt_init_msg = 1,
        sbt_sensor_data_msg = 2,
        sbt_actuator_cmd_msg = 3
} sbt_message_types;

typedef struct {
        uint32_t time_stamp;
        uint32_t packet_id;
        uint16_t flags;
} sbt_nonce;

typedef enum {
        no_time_set = 0,
        not_initialized = 1,
        initialized = 2,
} sbt_device_status_t;

typedef struct {
        uint8_t *string;
        uint16_t size;
} sbt_transmission_string;

/* Functions */
void print_session_key();
void sbt_delete_pending_actuator_ack();
void reset_current_msg_queue_element(void);
void sbt_init();
sbt_packet_t sbt_get_time_request();
sbt_packet_t sbt_get_init_request();
uint8_t sbt_is_msg_pending();
sbt_packet_t sbt_get_sensor_data_msg_packet(sbt_storage_data_point_t *data_points,
        uint32_t msg_datagram_cnt);
uint8_t sbt_get_next_trans_string(sbt_transmission_string *trans_string);
uint8_t sbt_build_transmission_string(sbt_transmission_string *transmission_string,
        sbt_packet_t *packet);
uint8_t sbt_process_msg(uint8_t *msg, uint16_t msg_length, sbt_packet_t *packet);
uint8_t sbt_get_device_status();
uint8_t sbt_set_device_status(sbt_device_status_t status);
uint32_t get_timestamp();
uint8_t sbt_msg_queue_fill();
void set_aes_ccm_encryption_config(aes_ccm_config_t *cfg, uint8_t *key, sbt_packet_t *packet);
void free_aes_config(aes_ccm_config_t *cfg, sbt_packet_t *packet);
#endif //SBT_PROTOCOL_SBT_LAYER_H
