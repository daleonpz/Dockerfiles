#include <stdio.h>
#include <inttypes.h>
#include "sbt.h"
#include <stdlib.h>
#include "aes-ccm.h"
#include "sys_trng.h"
#include "sys_rtc.h"
#include "osal.h"
#include "string.h"
#include "tasks.h"
#include "debug_log.h"
#include "digital_roller.h"
#include "sbt_config.h"

static uint32_t get_unique_packet_id();

static void generate_session_key(uint8_t *session_key);

PRIVILEGED_DATA static OS_TIMER init_timeout_timer;
PRIVILEGED_DATA static OS_TIMER ttl_timeout_timer;
volatile sbt_device_status_t device_status = no_time_set;
volatile uint64_t device_timestamp = 0;
static uint64_t last_timestamp = 0;
uint32_t rtc_time_of_initialization = 0;
sbt_msg_queue_element_t current = { 0 };
aes_ccm_key_t session_key = { { 0 } };
sbt_packet_t init_req_packet = { 0 };
uint64_t rtc_ack_start = 0;
uint8_t empty_string[SBT_EMPTY_STRING_SIZE] = { 0 };

void print_session_key()
{
        printf("SESSION KEY: \t");
        for (int i = 0; i < 16; i++) {
                printf("%02X", session_key.key[i]);
        }
        printf("\r\n");
}

uint8_t sbt_is_msg_pending()
{
        if (sbt_is_storage_empty() == false || sbt_msg_queue_get_cnt() > 0) {
                return EXIT_SUCCESS;
        }
        else {
                return EXIT_FAILURE;
        }
}

void reset_current_msg_queue_element(void)
{
        debug_log("Resetting current msg queue element");
        current.id = 0;
        current.msg = 0;
        current.msg_length = 0;
        current.next = NULL;
}

void sbt_delete_pending_actuator_ack(sbt_transmission_string *trans_string)
{
        if (sbt_msg_queue_get_cnt() == 0) {
                return;
        }
        if (trans_string->size == 18) {
                uint32_t _id = sbt_msg_queue_get_msg_id(trans_string);
                debug_log("deleting pending actuator ack with ID: %02X", &_id);
                sbt_msg_queue_remove_by_id(_id);
        }
}

static void reverse_mem_cpy(uint8_t *destination, uint8_t *source, uint16_t length)
{
        for (uint16_t i = 0; i < length; i++) {
                destination[length - 1 - i] = source[i];
        }
}

void init_msg_timeout_cb(OS_TIMER timer)
{
        if (sbt_get_device_status() != initialized) {
                sbt_set_device_status(no_time_set);
                last_timestamp = 0;
                init_req_packet = sbt_get_init_request();
#ifdef SBT_DEBUG_ENABLED
                debug_log("SBT: Init time out! ");
#endif
        }
        OS_TIMER_RESET(timer, OS_TIMER_FOREVER);
        OS_TIMER_STOP(timer, OS_TIMER_FOREVER);
}

void ttl_timeout_cb(OS_TIMER timer)
{
#ifdef SBT_DEBUG_ENABLED
        debug_log("SBT: TTL Timer -> Session ends now");
#endif
        OS_TIMER_RESET(timer, OS_TIMER_FOREVER);
        OS_TIMER_STOP(timer, OS_TIMER_FOREVER);
        sbt_set_device_status(no_time_set);
}

void sbt_init()
{
        init_timeout_timer = OS_TIMER_CREATE("Init MSG Timeout Timer",
                OS_MS_2_TICKS(SBT_INIT_TIMEOUT), true, (void *) OS_GET_CURRENT_TASK(),
                init_msg_timeout_cb);
        OS_ASSERT(init_timeout_timer);
        ttl_timeout_timer = OS_TIMER_CREATE("TTL Timeout Timer",
                OS_MS_2_TICKS(SBT_DEFAULT_SESSION_TTL), true, (void *) OS_GET_CURRENT_TASK(),
                ttl_timeout_cb);
        OS_ASSERT(ttl_timeout_timer);
        sbt_storage_init();
        /* set fin and ncr bit */
}

void set_aes_ccm_encryption_config(aes_ccm_config_t *cfg, uint8_t *key, sbt_packet_t *packet)
{
        uint32_t flags = (*(uint16_t *)&packet->flags);
        cfg->nonce = OS_MALLOC(SBT_NONCE_SIZE * sizeof(uint8_t));
        uint8_t *cursor = NULL;

        reverse_mem_cpy(cfg->nonce, (uint8_t *)&packet->time, 4);
        reverse_mem_cpy(cfg->nonce + 4, (uint8_t *)&packet->packet_id, 4);
        reverse_mem_cpy(cfg->nonce + 8, (uint8_t *)&flags, 2);
        cfg->msg_length = packet->msg_datagram_size;
        cfg->nonce_length = 10;
        if (packet->msg_datagram[0].type == sbt_init_msg) {
                cfg->msg = OS_MALLOC(cfg->msg_length * sizeof(uint8_t));
                reverse_mem_cpy(cfg->msg, (uint8_t *)&(packet->msg_datagram[0].type), 1);
                reverse_mem_cpy(cfg->msg + 1, (uint8_t*)&packet->msg_datagram[0].length, 2);
                reverse_mem_cpy(cfg->msg + 3, (uint8_t*)&packet->msg_datagram[0].payload.init.kapt,
                        1);
                reverse_mem_cpy(cfg->msg + 4, (uint8_t*)&packet->msg_datagram[0].payload.init.ttl,
                        2);
                memcpy(cfg->msg + 6, packet->msg_datagram[0].payload.init.session_key, 16);

        } else if (packet->msg_datagram[0].type == sbt_sensor_data_msg) {
                cfg->msg = OS_MALLOC(cfg->msg_length * sizeof(uint8_t));
                cursor = cfg->msg;
                for (int i = 0; i < packet->msg_datagram_cnt; i++) {
                        reverse_mem_cpy(cursor, (uint8_t *)&(packet->msg_datagram[i].type), 1);
                        cursor += 1;
                        reverse_mem_cpy(cursor, (uint8_t*)&packet->msg_datagram[i].length, 2);
                        cursor += 2;
                        reverse_mem_cpy(cursor,
                                (uint8_t*)&packet->msg_datagram[i].payload.sensor_data.data_time,
                                4);
                        cursor += 4;
                        reverse_mem_cpy(cursor,
                                (uint8_t*)&packet->msg_datagram[i].payload.sensor_data.data_key, 2);
                        cursor += 2;
                        reverse_mem_cpy(cursor,
                                (uint8_t*)packet->msg_datagram[i].payload.sensor_data.data_value,
                                packet->msg_datagram[i].length);
                        cursor += packet->msg_datagram[i].length;
                }
        }

        cfg->additional_data_size = 4;
        cfg->additional_data = OS_MALLOC(cfg->additional_data_size * sizeof(uint8_t));
        reverse_mem_cpy(cfg->additional_data, (uint8_t*)&(packet->ack), 4);
        cfg->auth_field_size = 4;
        memcpy(cfg->key.key, key, 16);
}

static void set_aes_ccm_decryption_config(aes_ccm_config_t *cfg, sbt_packet_t *packet,
        uint8_t *enc_msg, uint8_t msg_length, uint8_t *mac, aes_ccm_key_t key)
{
        uint32_t flags = (*(uint16_t *)&packet->flags);
        cfg->nonce = OS_MALLOC(SBT_NONCE_SIZE * sizeof(uint8_t));
        cfg->nonce_length = 10;
        reverse_mem_cpy(cfg->nonce, (uint8_t *)&packet->time, 4);
        reverse_mem_cpy(cfg->nonce + 4, (uint8_t *)&packet->packet_id, 4);
        reverse_mem_cpy(cfg->nonce + 8, (uint8_t *)&flags, 2);

        if (msg_length > 0) {
                cfg->msg = OS_MALLOC(msg_length * sizeof(uint8_t));
                memcpy(cfg->msg, enc_msg, msg_length);
        }

        cfg->msg_length = msg_length;
        cfg->additional_data = OS_MALLOC(SBT_MAC_SIZE * sizeof(uint8_t));
        cfg->additional_data_size = SBT_MAC_SIZE;
        reverse_mem_cpy(cfg->additional_data, (uint8_t *)&packet->ack, 4);
        cfg->auth_field_size = SBT_MAC_SIZE;
        cfg->key = key;
}

void free_aes_config(aes_ccm_config_t *cfg, sbt_packet_t *packet)
{
        OS_FREE(cfg->nonce);
        if (packet->msg_datagram[0].type == sbt_init_msg
                || packet->msg_datagram[0].type == sbt_sensor_data_msg) {
                OS_FREE(cfg->msg);
        }
        OS_FREE(cfg->additional_data);
}

sbt_packet_t sbt_get_time_request()
{
        sbt_packet_t packet = { 0 };
        uint32_t random_time = 0;
        sys_trng_get_bytes((uint8_t*)&random_time, 4);
        packet.time = random_time;
        packet.packet_id = get_unique_packet_id();
        packet.flags.ncr = 1;
        packet.flags.fin = 0;
        packet.ack = 0;
        packet.msg_datagram = OS_MALLOC(sizeof(sbt_msg_datagram_t));
        packet.msg_datagram[0].type = sbt_time_msg;
        packet.msg_datagram[0].length = 0;
        packet.msg_datagram[0].payload.timestamp = 0;
        packet.msg_datagram_size = SBT_TIME_REQ_SIZE;
        return packet;
}

sbt_packet_t sbt_get_init_request()
{
        sbt_packet_t packet = { 0 };

        packet.time = get_timestamp();
        packet.packet_id = get_unique_packet_id();
        packet.flags.psk = 1;
        packet.flags.fin = 1;
        packet.ack = 0;
        packet.msg_datagram = OS_MALLOC(sizeof(sbt_msg_datagram_t));
        packet.msg_datagram[0].type = sbt_init_msg;
        packet.msg_datagram[0].length = 16;
        packet.msg_datagram[0].payload.init.kapt = 0;
        packet.msg_datagram[0].payload.init.ttl = 0x05A0;
        generate_session_key((uint8_t *)&packet.msg_datagram[0].payload.init.session_key);
        packet.msg_datagram_size = SBT_INIT_MSG_SIZE;
        return packet;
}

sbt_packet_t sbt_get_sensor_data_msg_packet(sbt_storage_data_point_t *data_points,
        uint32_t msg_datagram_cnt)
{
        sbt_packet_t packet = { 0 };

        packet.time = get_timestamp();
        packet.packet_id = get_unique_packet_id();
        packet.flags.fin = 0;
        packet.ack = 0;
        packet.msg_datagram = OS_MALLOC(msg_datagram_cnt * sizeof(sbt_msg_datagram_t));
        for (int i = 0; i < msg_datagram_cnt; i++) {
                packet.msg_datagram[i].type = sbt_sensor_data_msg;
                packet.msg_datagram[i].length = 2;
                packet.msg_datagram[i].payload.sensor_data.data_key = data_points[i].key;
                packet.msg_datagram[i].payload.sensor_data.data_time = get_timestamp()
                        - (rtc_time_of_initialization - data_points[i].timestamp);
                memcpy(packet.msg_datagram[i].payload.sensor_data.data_value,
                        (uint8_t *)&data_points[i].value, 2);
                packet.msg_datagram_size += SBT_SENSOR_DATA_MSG_SIZE(packet.msg_datagram[i].length);
        }
        packet.msg_datagram_cnt = msg_datagram_cnt;
        return packet;
}

static sbt_packet_t get_actuator_ack(sbt_packet_t *actuator_cmd_packet)
{
        debug_log("generating ack command for recieved actuator command");
        sbt_packet_t ack_packet = { 0 };
        ack_packet.time = get_timestamp();
        ack_packet.packet_id = get_unique_packet_id();
        ack_packet.flags.ack = 1;
        ack_packet.ack = actuator_cmd_packet->packet_id;
        ack_packet.msg_datagram->type = sbt_actuator_cmd_msg;
        ack_packet.msg_datagram_size = 0;
        return ack_packet;
}

void sbt_get_last_packet(sbt_transmission_string *trans_string)
{
        trans_string->string = OS_MALLOC(SBT_EMPTY_STRING_SIZE * sizeof(uint8_t));
        trans_string->size = SBT_EMPTY_STRING_SIZE;
        /* set fin and ncr bit */
        memcpy(trans_string->string, empty_string, SBT_EMPTY_STRING_SIZE);
        trans_string->string[9] = 0x11;
}

static uint32_t get_unique_packet_id()
{
        uint32_t packet_id = 0;
        sys_trng_get_bytes((uint8_t*)&packet_id, 4);
        return packet_id;
}

uint32_t get_timestamp()
{
        uint64_t _timestamp = 0;
        if (sbt_get_device_status() == no_time_set) {
                _timestamp = (uint64_t)rtc_get() / RTC_FREQUENCY;
        } else {
                _timestamp = rtc_get();
                if (last_timestamp == 0) {
                        last_timestamp = _timestamp;
                }
                device_timestamp += (uint64_t)((_timestamp - last_timestamp) / RTC_FREQUENCY);
                last_timestamp = _timestamp;
                _timestamp = device_timestamp;
        }
        return _timestamp;
}

static uint32_t set_timestamp(uint64_t timestamp)
{
        device_timestamp = timestamp;
        last_timestamp = 0;
        return EXIT_SUCCESS;
}

static void generate_session_key(uint8_t *session_key)
{
        sys_trng_get_bytes(session_key, 16);
}

uint8_t sbt_get_next_trans_string(sbt_transmission_string *trans_string)
{
        sbt_packet_t packet = { 0 };
        uint8_t chk = EXIT_FAILURE;
        uint8_t is_last = EXIT_FAILURE;

        switch (device_status) {

        case no_time_set:
                packet = sbt_get_time_request();
                sbt_build_transmission_string(trans_string, &packet);
                chk = EXIT_SUCCESS;
                break;

        case not_initialized:
                packet = init_req_packet;
                sbt_build_transmission_string(trans_string, &packet);
                chk = EXIT_SUCCESS;
                break;

        case initialized:
                if (sbt_msg_queue_get_cnt() == 0) {
                        sbt_get_last_packet(trans_string);
                        chk = EXIT_SUCCESS;
                        break;
                }
                if (is_element_uninitialized(&current) == EXIT_SUCCESS) {
                        debug_log("Starting at first element");
                        chk = sbt_msg_queue_iterate_through(&current);
                }
                else if ((is_element_in_queue(&current) == EXIT_FAILURE)) {
                        debug_log("element is not queue, resetting");
                        reset_current_msg_queue_element();
                        chk = sbt_msg_queue_iterate_through(&current);
                }
                else if (is_last_element_of_msg_queue(current.id) == EXIT_SUCCESS) {
                        debug_log("is last element");
                        is_last = EXIT_SUCCESS;
                        sbt_get_last_packet(trans_string);
                        reset_current_msg_queue_element();
                        chk = EXIT_SUCCESS;
                }
                else if (is_last_element_of_msg_queue(current.id) == EXIT_FAILURE) {
                        debug_log("element is not first not last");
                        chk = sbt_msg_queue_iterate_through(&current);
                        debug_log("chk: %d", chk);
                }
                else {
                        debug_log("strange");
                        sbt_get_last_packet(trans_string);
                        chk = EXIT_SUCCESS;
                }

                if (chk == EXIT_SUCCESS && is_last == EXIT_FAILURE) {
                        debug_log("EXIT SUCCESS");
                        trans_string->string = OS_MALLOC(
                                current.msg_length * sizeof(uint8_t));
                        memcpy(trans_string->string, current.msg, current.msg_length);
                        trans_string->size = current.msg_length;
                        break;
                }
                else if (chk == EXIT_FAILURE) {
                        debug_log("chk == EXIT_FAILURE, sending delimiter frame");
                        sbt_get_last_packet(trans_string);
                        chk = EXIT_SUCCESS;
                        break;
                }
        }
        return chk;
}

uint8_t sbt_build_transmission_string(sbt_transmission_string *trans_string, sbt_packet_t *packet)
{
        aes_ccm_config_t cfg = { 0 };
        uint8_t mac[4] = { 0 };
        uint16_t flags = (*(uint16_t *)&packet->flags);

        trans_string->size = SBT_FRAME_SIZE(packet->msg_datagram_size);

        if (packet->msg_datagram[0].type == sbt_time_msg)
                trans_string->size -= 4;

        trans_string->string = OS_MALLOC(trans_string->size * sizeof(uint8_t));
        reverse_mem_cpy(trans_string->string, (uint8_t *)&packet->time, 4);
        reverse_mem_cpy(trans_string->string + 4, (uint8_t *)&packet->packet_id, 4);
        reverse_mem_cpy(trans_string->string + 8, (uint8_t *)&flags, 2);
        reverse_mem_cpy(trans_string->string + 10, (uint8_t *)&packet->ack, 4);

        if (packet->msg_datagram[0].type == sbt_time_msg) {
                reverse_mem_cpy(trans_string->string + 14, (uint8_t *)&packet->msg_datagram[0].type,
                        1);
                reverse_mem_cpy(trans_string->string + 15,
                        (uint8_t *)&packet->msg_datagram[0].length, 2);
                free_aes_config(&cfg, packet);
                OS_FREE(packet->msg_datagram);

        } else if (packet->msg_datagram[0].type == sbt_init_msg) {
                uint8_t enc_msg[22] = { 0 };
                set_aes_ccm_encryption_config(&cfg, master_key.key, packet);
                aes_ccm_encrypt(&cfg, enc_msg, mac);
                memcpy(trans_string->string + 14, enc_msg, packet->msg_datagram_size);
                memcpy(trans_string->string + 14 + packet->msg_datagram_size, mac, SBT_MAC_SIZE);
                free_aes_config(&cfg, packet);
                OS_FREE(packet->msg_datagram);

        } else if (packet->msg_datagram[0].type == sbt_sensor_data_msg) {
                set_aes_ccm_encryption_config(&cfg, session_key.key, packet);
                uint8_t *enc_msg = OS_MALLOC(packet->msg_datagram_size * sizeof(uint8_t));
                aes_ccm_encrypt(&cfg, enc_msg, mac);
                memcpy(trans_string->string + 14, enc_msg, packet->msg_datagram_size);
                memcpy(trans_string->string + 14 + packet->msg_datagram_size, mac, SBT_MAC_SIZE);
                OS_FREE(enc_msg);
                free_aes_config(&cfg, packet);
                OS_FREE(packet->msg_datagram);
        }
        else if (packet->msg_datagram[0].type == sbt_actuator_cmd_msg) {
                aes_ccm_config_t aes_cfg = { 0 };
                uint8_t *msg = NULL;
                set_aes_ccm_encryption_config(&aes_cfg, session_key.key, packet);
                aes_ccm_encrypt(&aes_cfg, msg, mac);
                memcpy(trans_string->string + 14, mac, SBT_MAC_SIZE);
        }
        return EXIT_SUCCESS;
}

static uint8_t deconstruct_time_msg_datagram(uint8_t *msg, uint16_t msg_length,
        sbt_packet_t *packet)
{
        uint8_t chk = EXIT_SUCCESS;
        if (msg_length != SBT_TIME_RESP_DATAGRAM_SIZE) {
                return EXIT_FAILURE;
        }
        reverse_mem_cpy((uint8_t *)&packet->msg_datagram[0].payload.timestamp, msg + 17, 4);
        return chk;
}

static uint8_t deconstruct_init_datagram(uint8_t *msg, uint16_t msg_length, sbt_packet_t *packet)
{
        uint8_t chk = EXIT_SUCCESS;
        uint8_t enc_msg[22] = { 0 };
        uint8_t decrypted_msg[22] = { 0 };
        uint8_t mac[4] = { 0 };
        aes_ccm_config_t cfg = { 0 };

        memcpy(enc_msg, msg + 14, 22);
        memcpy(mac, msg + 36, 4);
        set_aes_ccm_decryption_config(&cfg, packet, enc_msg, msg_length, mac, session_key);
        chk = aes_ccm_decrypt(&cfg, decrypted_msg, mac);
        OS_FREE(cfg.nonce);
        OS_FREE(cfg.additional_data);
        OS_FREE(cfg.msg);

        if (chk == EXIT_SUCCESS) {
                reverse_mem_cpy((uint8_t *)&packet->msg_datagram[0].type, decrypted_msg, 1);
                reverse_mem_cpy((uint8_t *)&packet->msg_datagram[0].length, decrypted_msg + 1, 2);
                reverse_mem_cpy((uint8_t *)&packet->msg_datagram[0].payload.init.kapt,
                        decrypted_msg + 3, 1);
                reverse_mem_cpy((uint8_t *)&packet->msg_datagram[0].payload.init.ttl,
                        decrypted_msg + 4, 2);
                reverse_mem_cpy((uint8_t *)&packet->msg_datagram[0].payload.init.session_key,
                        decrypted_msg + 6, 16);
        }
        if (packet->msg_datagram[0].type != 0x01)
                chk = EXIT_FAILURE;
        return chk;
}

static uint8_t deconstruct_data_response(uint8_t *msg, sbt_packet_t *packet)
{
        uint8_t mac[4] = { 0 };
        uint8_t mac_to_chk[4] = { 0 };
        aes_ccm_config_t cfg = { 0 };
        uint8_t enc_msg[1] = { 0 };
        /* Just for classification purpose */
        packet->msg_datagram[0].type = SBT_DATA_MSG_TYPE;
        memcpy(mac, msg + 14, 4);
        set_aes_ccm_decryption_config(&cfg, packet, NULL, 0, mac, session_key);
        aes_ccm_encrypt(&cfg, enc_msg, mac_to_chk);
        OS_FREE(cfg.nonce);
        OS_FREE(cfg.additional_data);
        OS_FREE(cfg.msg);
        uint8_t n = memcmp(mac, mac_to_chk, SBT_MAC_SIZE);
        if (n == 0) {
                return EXIT_SUCCESS;
        }
        return EXIT_FAILURE;
}

static uint8_t deconstruct_actuator_cmd(uint8_t *msg, uint16_t frame_length, sbt_packet_t *packet)
{
        uint8_t chk = EXIT_SUCCESS;
        uint16_t cmd_msg_length = frame_length - SBT_DATAGRAM_FRAME_OVERHEAD;
        uint8_t *enc_cmd_msg = OS_MALLOC(cmd_msg_length);
        uint8_t *decrypted_cmd_msg = OS_MALLOC(cmd_msg_length);
        uint8_t mac[4] = { 0 };
        aes_ccm_config_t cfg = { 0 };
        memcpy(enc_cmd_msg, msg + 14, cmd_msg_length);
        memcpy(mac, msg + cmd_msg_length + 14, 4);
        set_aes_ccm_decryption_config(&cfg, packet, enc_cmd_msg, cmd_msg_length, mac, session_key);
        chk = aes_ccm_decrypt(&cfg, decrypted_cmd_msg, mac);

        packet->msg_datagram[0].type = SBT_ACTUATOR_CMD_TYPE;
        packet->msg_datagram[0].length = (decrypted_cmd_msg[1] << 8) | decrypted_cmd_msg[2];
        packet->msg_datagram[0].payload.act_cmd.data_key = (decrypted_cmd_msg[3] << 8)
                | decrypted_cmd_msg[4];
        packet->msg_datagram[0].payload.act_cmd.cmd = OS_MALLOC(packet->msg_datagram[0].length);
        reverse_mem_cpy(packet->msg_datagram[0].payload.act_cmd.cmd, decrypted_cmd_msg + 5,
                packet->msg_datagram[0].length);

        if (packet->msg_datagram[0].length != cmd_msg_length - 5) {
                debug_log("ERR ACT_CMD: wrong length field specified");
                OS_FREE(packet->msg_datagram[0].payload.act_cmd.cmd);
                chk = EXIT_FAILURE;
        }

        OS_FREE(enc_cmd_msg);
        OS_FREE(decrypted_cmd_msg);
        OS_FREE(cfg.nonce);
        OS_FREE(cfg.additional_data);
        OS_FREE(cfg.msg);
        return chk;
}

static uint8_t is_time_response(uint8_t *msg, uint16_t msg_length, uint16_t flags)
{
        if (msg_length != SBT_TIME_RESP_DATAGRAM_SIZE) {
                return EXIT_FAILURE;
        }
        if (flags != 0x0013) {
                return EXIT_FAILURE;
        }
        if (sbt_get_device_status() != no_time_set) {
                return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
}

static uint8_t is_init_response(uint8_t *msg, uint16_t msg_length, uint16_t flags)
{
        if (msg_length != SBT_INIT_RESP_DATAGRAM_SIZE) {
                return EXIT_FAILURE;
        }
        if (flags != 0x0003) {
                return EXIT_FAILURE;
        }
        if (sbt_get_device_status() != not_initialized) {
                return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
}

static uint8_t is_sensor_data_response(uint8_t *msg, uint16_t msg_length, uint16_t flags)
{
        if (msg_length != SBT_DATA_RESP_DATAGRAM_SIZE) {
                return EXIT_FAILURE;
        }
        if (flags != 0x0003) {
                return EXIT_FAILURE;
        }
        if (sbt_get_device_status() != initialized) {
                return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
}

static uint8_t is_actuator_cmd(uint8_t *msg, uint16_t msg_length, uint16_t flags)
{
        uint8_t chk = EXIT_SUCCESS;
        if (msg_length < SBT_MIN_ACT_CMD_SIZE) {
                chk = EXIT_FAILURE;
        }
        if (flags != 0) {
                debug_log("unsupported flag field for incoming act cmd!");
                chk = EXIT_FAILURE;
        }
        return chk;
}

static uint8_t convert_bytes_to_packet(uint8_t *msg, uint16_t msg_length, sbt_packet_t *packet)
{
        uint8_t chk = EXIT_SUCCESS;
        uint16_t flags = 0;

        debug_log("converting bytes to packet");

        if (msg_length > SBT_INIT_RESP_DATAGRAM_SIZE || msg_length < SBT_DATA_RESP_DATAGRAM_SIZE) {
                return EXIT_FAILURE;
        }
        reverse_mem_cpy((uint8_t *)&packet->time, msg, 4);
        reverse_mem_cpy((uint8_t *)&packet->packet_id, msg + 4, 4);
        reverse_mem_cpy((uint8_t *)&packet->flags, msg + 8, 2);
        reverse_mem_cpy((uint8_t *)&packet->ack, msg + 10, 4);
        flags = (*(uint16_t *)&packet->flags);

        if (is_time_response(msg, msg_length, flags) == EXIT_SUCCESS) {
                reverse_mem_cpy((uint8_t *)&packet->msg_datagram[0].type, msg + 14, 1);
                reverse_mem_cpy((uint8_t *)&packet->msg_datagram[0].length, msg + 15, 2);
                chk = deconstruct_time_msg_datagram(msg, msg_length, packet);
        } else if (is_init_response(msg, msg_length, flags) == EXIT_SUCCESS) {
                debug_log("is init response");
                chk = deconstruct_init_datagram(msg, SBT_INIT_MSG_SIZE, packet);
        } else if (is_sensor_data_response(msg, msg_length, flags) == EXIT_SUCCESS) {
                reverse_mem_cpy((uint8_t *)&packet->mac, msg + 16, SBT_MAC_SIZE);
                chk = deconstruct_data_response(msg, packet);
        }
        else if (is_actuator_cmd(msg, msg_length, flags) == EXIT_SUCCESS) {
                chk = deconstruct_actuator_cmd(msg, msg_length, packet);
        }

        else {
#ifdef SBT_DEBUG_ENABLED
                debug_log("SBT ERROR: Incoming packet is invalid");
#endif
                return EXIT_FAILURE;
        }
        return chk;
}

uint8_t sbt_process_msg(uint8_t *msg, uint16_t msg_length, sbt_packet_t *packet)
{
        uint8_t chk = convert_bytes_to_packet(msg, msg_length, packet);

        if (chk == EXIT_FAILURE) {
                return EXIT_FAILURE;
        }

        if (packet->msg_datagram[0].type == SBT_TIME_MSG_TYPE) {
                set_timestamp(packet->msg_datagram[0].payload.timestamp);
                sbt_set_device_status(not_initialized);
                init_req_packet = sbt_get_init_request();
                memcpy(session_key.key, init_req_packet.msg_datagram[0].payload.init.session_key,
                        16);
                OS_TIMER_START(init_timeout_timer, OS_TIMER_FOREVER);
#ifdef SBT_DEBUG_ENABLED
                debug_log("SBT: New timestamp set to %"PRIu32"",
                        packet->msg_datagram[0].payload.timestamp);
#endif
        } else if (packet->msg_datagram[0].type == SBT_TIME_INIT_TYPE) {
                if (packet->ack != init_req_packet.packet_id) {
                        chk = EXIT_FAILURE;
#ifdef SBT_DEBUG_ENABLED
                        debug_log("SBT ERROR: init message had the wrong ack");
#endif
                } else {
                        sbt_set_device_status(initialized);
                        rtc_time_of_initialization = (uint32_t)rtc_get() / RTC_FREQUENCY;
                        OS_TIMER_CHANGE_PERIOD(ttl_timeout_timer,
                                SBT_SESSION_TTL(packet->msg_datagram[0].payload.init.ttl), 0xFFFF);
                        OS_TIMER_START(ttl_timeout_timer, OS_TIMER_FOREVER);

#ifdef SBT_DEBUG_ENABLED
                        debug_log("SBT: Device is initalized now");
                        debug_log("SBT: Session TTL: %d minutes",
                                packet->msg_datagram[0].payload.init.ttl);
#endif
                }
        } else if (packet->msg_datagram[0].type == SBT_DATA_MSG_TYPE) {
                uint8_t rmv_chk = EXIT_FAILURE;
                rmv_chk = sbt_msg_queue_remove_by_id(packet->ack);

#ifdef SBT_DEBUG_ENABLED
                if (rmv_chk == EXIT_SUCCESS) {
                        debug_log("SBT ACK: Message with id %02X was acknowledged ",
                                packet->ack);
                } else {
                        debug_log("SBT ACK: Message with id %02X was NOT acknowledged ",
                                packet->ack);

                }
#endif

        }

        else if (packet->msg_datagram[0].type == sbt_actuator_cmd_msg) {
                debug_log("Incoming msg is an actuator cmd");

                // application function to process the actuator command
                actuator_command_t cmd = { 0 };
                cmd.key = packet->msg_datagram->payload.act_cmd.data_key;
                memcpy(&cmd.value, packet->msg_datagram->payload.act_cmd.cmd, packet->msg_datagram->length);
                OS_FREE(packet->msg_datagram->payload.act_cmd.cmd);
                debug_log("Received actuator cmd key: %02X, value %02X", cmd.key, cmd.value);
                roller_processActuatorCommand(cmd);

                // Building the ack
                sbt_packet_t ack = { 0 };
                sbt_transmission_string action_ack_string = { 0 };
                ack = get_actuator_ack(packet);
                sbt_build_transmission_string(&action_ack_string, &ack);
                debug_log("finished constructing ack string, appending it to msg queue");
                sbt_msg_queue_append(&action_ack_string.string, action_ack_string.size);
        }

        else {
#ifdef SBT_DEBUG_ENABLED
                debug_log("SBT ERROR: Message could not be processed");
#endif
        }
        return chk;
}

sbt_device_status_t sbt_get_device_status()
{
        return device_status;
}

uint8_t sbt_set_device_status(sbt_device_status_t status)
{
        if (status != 0 && status != 1 && status != 2) {
                return EXIT_FAILURE;
        }
        device_status = status;
        return EXIT_SUCCESS;
}

uint8_t sbt_msg_queue_fill()
{
        uint16_t elements_to_store_cnt = sbt_msg_queue_data_points_to_store();
        uint8_t msg_datagram_cnt = 0;

        if (elements_to_store_cnt == 0 || sbt_get_device_status() != initialized) {
                return EXIT_FAILURE;
        }

        sbt_storage_data_point_t *data_points = OS_MALLOC(
                elements_to_store_cnt * sizeof(sbt_storage_data_point_t));
        sbt_storage_data_point_t *data_point_cursor = NULL;

        data_point_cursor = data_points;

        for (int i = 0; i < elements_to_store_cnt; i++) {
                uint8_t chk = EXIT_FAILURE;
                while (chk == EXIT_FAILURE) {
                        chk = sbt_storage_get_next_data_point(&data_points[i]);
                }
        }

        int i = 0;
        while (elements_to_store_cnt > 0) {
                sbt_transmission_string trans_string = { 0 };
                sbt_packet_t packet = { 0 };
                msg_datagram_cnt =
                        elements_to_store_cnt > SBT_ELEMENTS_PER_FRAME ?
                        SBT_ELEMENTS_PER_FRAME :
                                                                         elements_to_store_cnt;
                packet = sbt_get_sensor_data_msg_packet(data_point_cursor, msg_datagram_cnt);
                sbt_build_transmission_string(&trans_string, &packet);
                sbt_msg_queue_append(&trans_string.string, trans_string.size);

                elements_to_store_cnt -= msg_datagram_cnt;
                data_point_cursor = data_point_cursor + msg_datagram_cnt;
                i++;
        }

        OS_FREE(data_points);

        return EXIT_SUCCESS;
}
