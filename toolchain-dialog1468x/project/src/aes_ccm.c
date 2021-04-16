/*
 * aes-ccm.c
 *
 *  Created on: 20.03.2019
 *      Author: Felix Schütte
 */
#include "osal.h"
#include <inttypes.h>
#include <stdlib.h>

#include <string.h>
#include "stdbool.h"
#include <math.h>
#include "sys_trng.h"
#include "ad_crypto.h"
#include "hw_crypto.h"
#include "hw_ecc.h"
#include "hw_ecc_curves.h"
#include "hw_aes_hash.h"
#include "aes-ccm.h"

static uint8_t aes_ccm_get_iv(aes_ccm_config_t *cfg, aes_ccm_block_t *iv);

static uint8_t aes_ccm_init(aes_ccm_config_t *cfg);

static uint8_t aes_ccm_encode_aad_length(aes_ccm_config_t *cfg, aes_ccm_aad_length_encoded_t *aad_length);

static uint8_t
aes_ccm_get_auth_blocks(aes_ccm_config_t *cfg, aes_ccm_block_t **blocks, uint64_t *total_number_of_blocks);

static void
get_aad_blocks(aes_ccm_config_t *cfg, aes_ccm_block_t **aad_blocks, aes_ccm_aad_length_encoded_t *enc_aad_length);

static void aes_ccm_get_msg_blocks(aes_ccm_config_t *cfg, aes_ccm_block_t **msg_blocks);

static void aes_ccm_xor_blocks(aes_ccm_block_t *first_block, aes_ccm_block_t *second_block, aes_ccm_block_t *result);

static aes_ccm_block_t aes_ccm_set_counter(aes_ccm_config_t *cfg, uint64_t counter);

static void aes_ccm_get_key_stream_blocks(aes_ccm_block_t **blocks, aes_ccm_config_t *cfg);

static uint8_t aes_ccm_init(aes_ccm_config_t *cfg) {
    uint64_t aes_ccm_max_size = 0xFFFFFFFFFFFFFFFF;
    if ((cfg->auth_field_size > 16) || (cfg->auth_field_size < 2) || ((cfg->auth_field_size / 2) * 2 != cfg->auth_field_size)) {
#if AES_CCM_DEBUG
        printf("Authentication field M has wrong size \r\n");
#endif
        return EXIT_FAILURE;
    }
    if (cfg->nonce_length > 13 || cfg->nonce_length < 7) {
#if AES_CCM_DEBUG
        printf("Nonce has wrong size \r\n");
#endif
        return EXIT_FAILURE;
    }
    if (cfg->msg_length > aes_ccm_max_size) {
#if AES_CCM_DEBUG
        printf("Message has wrong size \r\n");
#endif
        return EXIT_FAILURE;
    }
    if (cfg->additional_data_size > aes_ccm_max_size) {
#if AES_CCM_DEBUG
        printf("Additional Data has wrong size \r\n");
#endif
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

static uint8_t aes_ccm_get_iv(aes_ccm_config_t *cfg, aes_ccm_block_t *iv) {
    aes_ccm_flags_field_t flags = { 0 };
    uint8_t bytes_left = (uint8_t) (16 - (cfg->nonce_length + 1));
    if ((1 << bytes_left * 8) - 1 < cfg->msg_length) {
#if AES_CCM_DEBUG
        printf("Message is too long! \r\n");
#endif
        return EXIT_FAILURE;
    }

    flags.a_data = (cfg->additional_data_size != 0) ? (uint8_t) 1 : (uint8_t) 0;
    flags.reserved = 0;
    flags.l_encoded = (uint8_t) ((15 - cfg->nonce_length - 1));
    flags.m_encoded = (uint8_t) (((cfg->auth_field_size - 2) / 2));
    iv->block[0] = (*(uint8_t *) &flags);
    memcpy((iv->block + 1), cfg->nonce, cfg->nonce_length);
    for (int i = cfg->nonce_length + 1; i < 16; i++) {
        iv->block[i] = (uint8_t) ((cfg->msg_length) & ((uint64_t) (0xFF) << (bytes_left - 1) * (8)));
        bytes_left--;
    }
    return EXIT_SUCCESS;
}

static uint8_t aes_ccm_encode_aad_length(aes_ccm_config_t *cfg, aes_ccm_aad_length_encoded_t *aad_length) {
    if (cfg->additional_data_size == 0) {
        aad_length->encoded_aad_length = NULL;
        aad_length->size = 0;
    } else if (cfg->additional_data_size < (1 << 16) - (1 << 8)) {
        aad_length->encoded_aad_length = OS_MALLOC(2 * sizeof(uint8_t));
        aad_length->size = 2;
        uint16_t _aad = ((uint16_t) cfg->additional_data_size);
        uint8_t bits_to_shift = 2;
        uint8_t _aad_array[2] = { 0 };
        for (int i = 0; i < (aad_length->size); i++) {
            _aad_array[i] = (uint8_t) ((_aad >> bits_to_shift * 8) & 0xFF);
            bits_to_shift -= 2;
        }
        memcpy(aad_length->encoded_aad_length, &_aad_array, 2);

    } else if ((1 << 16) - (1 << 8) <= (cfg->additional_data_size) && (cfg->additional_data_size) < (uint64_t) 1 << 32) {
        // TODO: Not tested
        aad_length->encoded_aad_length = OS_MALLOC(6 * sizeof(uint8_t));
        aad_length->size = 6;
        uint32_t _aad = ((uint32_t) cfg->additional_data_size);
        uint8_t bits_to_shift = 6;
        uint8_t _aad_array[6] = { 0 };
        _aad_array[0] = 0xff;
        _aad_array[1] = 0xfe;
        for (int i = 0; i < (aad_length->size); i++) {
            _aad_array[i + 2] = (uint8_t) ((_aad >> bits_to_shift * 8) & 0xFF);
            bits_to_shift -= 2;
        }
        memcpy(aad_length->encoded_aad_length, &_aad, 6);
    } else if ((uint64_t) 1 << 32 <= (cfg->additional_data_size) && (cfg->additional_data_size) < 0xFFFFFFFFFFFFFFFF) {
        // TODO: Not tested
        aad_length->encoded_aad_length = OS_MALLOC(10 * sizeof(uint8_t));
        aad_length->size = 10;
        uint64_t _aad = ((uint64_t) cfg->additional_data_size);
        uint8_t bits_to_shift = 14;
        uint8_t _aad_array[10] = { 0 };
        _aad_array[0] = 0xff;
        _aad_array[1] = 0xff;
        for (int i = 0; i < (aad_length->size); i++) {
            _aad_array[i + 2] = (uint8_t) ((_aad >> bits_to_shift * 8) & 0xFF);
            bits_to_shift -= 2;
        }
        memcpy(aad_length->encoded_aad_length, &_aad, 10);
    } else {
#if AES_CCM_DEBUG
        printf("Couldn't encode additional data length! \r\n");
#endif
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

static uint8_t aes_ccm_get_auth_blocks(aes_ccm_config_t *cfg, aes_ccm_block_t **blocks, uint64_t *total_number_of_blocks) {
    aes_ccm_aad_length_encoded_t encoded_aad_length = { 0 };
    aes_ccm_block_t iv = { { 0 } };
    uint64_t number_of_aad_blocks = 0;
    uint64_t number_of_msg_blocks = 0;
    aes_ccm_block_t *aad_blocks = NULL;
    aes_ccm_block_t *msg_blocks = NULL;

    if (aes_ccm_init(cfg) != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }
    if (aes_ccm_get_iv(cfg, &iv) != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }
    if (aes_ccm_encode_aad_length(cfg, &encoded_aad_length) != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }
    number_of_aad_blocks = (uint64_t) ceil((double) (encoded_aad_length.size + cfg->additional_data_size) / 16);
    number_of_msg_blocks = (uint64_t) ceil((double) cfg->msg_length / 16);
    *total_number_of_blocks = (uint64_t) (1 + number_of_aad_blocks + number_of_msg_blocks);
    *blocks = OS_MALLOC(*total_number_of_blocks * sizeof(aes_ccm_block_t));
    memcpy((*blocks)->block, iv.block, 16);

    if (cfg->msg_length > 0) {
        aes_ccm_get_msg_blocks(cfg, &msg_blocks);
        for (uint64_t i = 0; i < number_of_msg_blocks; i++) {
            memcpy((*blocks + (i + 1 + number_of_aad_blocks))->block, msg_blocks + (i), 16);
        }
        OS_FREE(msg_blocks);
    }

    if (cfg->additional_data_size > 0) {
        get_aad_blocks(cfg, &aad_blocks, &encoded_aad_length);
        for (uint64_t i = 0; i < number_of_aad_blocks; i++) {
            memcpy((*blocks + (i + 1))->block, aad_blocks + (i), 16);
        }
        OS_FREE(aad_blocks);
        OS_FREE(encoded_aad_length.encoded_aad_length);
    }
    return EXIT_SUCCESS;
}

static void get_aad_blocks(aes_ccm_config_t *cfg, aes_ccm_block_t **aad_blocks, aes_ccm_aad_length_encoded_t *enc_aad_length) {
    uint64_t write_offset = 0;
    uint64_t bytes_to_write = 0;
    uint64_t bytes_left = cfg->additional_data_size;
    uint64_t aad_block_length = 0;

    aad_block_length = (uint64_t) ceil((double) (enc_aad_length->size + cfg->additional_data_size) / 16);
    *aad_blocks = OS_MALLOC(aad_block_length * sizeof(aes_ccm_block_t));
    memcpy((*aad_blocks)->block, (uint16_t *) enc_aad_length->encoded_aad_length, enc_aad_length->size);
    if ((cfg->additional_data_size <= (16 - enc_aad_length->size))) {
        write_offset = cfg->additional_data_size;
        memset(&(**aad_blocks).block[enc_aad_length->size] + write_offset, 0, 16 - write_offset - enc_aad_length->size);
    } else {
        write_offset = (uint64_t) (16 - enc_aad_length->size);
    }
    memcpy(&(**aad_blocks).block[enc_aad_length->size], cfg->additional_data, write_offset);
    bytes_left -= write_offset;
    for (int i = 1; i < aad_block_length; i++) {
        bytes_to_write = (bytes_left > 16) ? 16 : bytes_left;
        memcpy((*aad_blocks + i)->block, (cfg->additional_data + write_offset), bytes_to_write);
        bytes_left -= bytes_to_write;
        if (bytes_left == 0 && bytes_to_write < 16) {
            memset((*aad_blocks + i)->block + bytes_to_write, 0, 16 - bytes_to_write);
        }
    }
}

static void aes_ccm_get_msg_blocks(aes_ccm_config_t *cfg, aes_ccm_block_t **msg_blocks) {
    uint64_t number_of_blocks = (uint64_t) ceil((double) cfg->msg_length / 16);
    uint64_t bytes_left = cfg->msg_length;

    if (number_of_blocks > 0) {
        *msg_blocks = OS_MALLOC(number_of_blocks * sizeof(aes_ccm_block_t));

        for (uint32_t i = 0; i < number_of_blocks; i++) {
            if (bytes_left > 16) {
                memcpy((*msg_blocks + i)->block, cfg->msg + i * (16), 16);
            } else {
                memcpy((*msg_blocks + i)->block, cfg->msg + i * (16), bytes_left);
                memset((*msg_blocks + i)->block + bytes_left, 0, 16 - bytes_left);
            }
            bytes_left -= 16;
        }
    }
}

static void aes_ccm_xor_blocks(aes_ccm_block_t *first_block, aes_ccm_block_t *second_block, aes_ccm_block_t *result) {
    for (int i = 0; i < 16; i++) {
        (*result).block[i] = (*first_block).block[i] ^ (*second_block).block[i];
    }
}

static aes_ccm_block_t aes_ccm_set_counter(aes_ccm_config_t *cfg, uint64_t counter) {
    aes_ccm_block_t start_block = { { 0 } };
    aes_ccm_flags_field_t flags = { 0 };
    uint8_t val = 0;
    uint8_t counter_size = 16 - cfg->nonce_length - 1;
    uint8_t bits_to_shift = (counter_size - 1) * 8;
    flags.a_data = 0;
    flags.l_encoded = (uint8_t) ((15 - cfg->nonce_length - 1));
    flags.m_encoded = 0;
    flags.reserved = 0;

    start_block.block[0] = (*(uint8_t *) &flags);
    memcpy((start_block.block + 1), cfg->nonce, cfg->nonce_length);
    memset((start_block.block + 1 + cfg->nonce_length), 0, counter_size);
    for (int i = 1 + cfg->nonce_length; i < 16; i++) {
        val = 0xFF & (counter >> bits_to_shift);
        memcpy((start_block.block + i), &val, 1);
        bits_to_shift -= 8;
    }
    return start_block;
}

static uint8_t aes_ccm_cbc_mode(aes_ccm_config_t *cfg, uint8_t * plaintext, uint8_t * ciphertext) {
    hw_aes_hash_setup setup = { 0 };

    setup.mode = HW_AES_CBC;
    setup.aesDirection = HW_AES_ENCRYPT;
    setup.aesKeySize = HW_AES_128;
    setup.aesKeyExpand = true;
    setup.aesKeys = (uint32_t) cfg->key.key;
    setup.aesWriteBackAll = false;
    setup.moreDataToCome = false;
    setup.sourceAddress = (uint32_t) plaintext;
    setup.destinationAddress = (uint32_t) ciphertext;
    setup.dataSize = 16;
    setup.enableInterrupt = false;
    hw_aes_hash_init(&setup);
    hw_aes_hash_start();
    while(hw_aes_hash_is_active());
#if AES_CCM_DEBUG
    for (uint8_t i = 0; i < 16; i++) {
        printf("%02"PRIx8"", *(ciphertext + i));
    }
    printf("\r\n");
#endif
    return EXIT_SUCCESS;
}

static void aes_ccm_get_key_stream_blocks(aes_ccm_block_t **blocks, aes_ccm_config_t *cfg) {
    uint8_t number_of_blocks = (uint8_t) ceil((double) cfg->msg_length / 16) + 1;
    aes_ccm_block_t next_block = { { 0 } };
    *blocks = OS_MALLOC(number_of_blocks * sizeof(aes_ccm_block_t));
    for (int i = 0; i < number_of_blocks; i++) {
        next_block = aes_ccm_set_counter(cfg, i);
        memcpy(*blocks + i, &next_block, sizeof(aes_ccm_block_t));
    }
    /* Apply AES */
    for (int i = 0; i < number_of_blocks; i++) {
        aes_ccm_cbc_mode(cfg, (*blocks + i)->block, (*blocks + i)->block);
    }
}

uint8_t get_cbc_mac(aes_ccm_config_t *cfg, aes_ccm_block_t *cbc_mac) {
    aes_ccm_block_t *blocks = NULL;
    uint64_t block_size = 0;
    uint8_t chk = EXIT_FAILURE;

    chk = aes_ccm_get_auth_blocks(cfg, &blocks, &block_size);
    aes_ccm_cbc_mode(cfg, (*blocks).block, cbc_mac->block);
    for (int i = 1; i < block_size; i++) {
        aes_ccm_xor_blocks((blocks + i), cbc_mac, cbc_mac);
        aes_ccm_cbc_mode(cfg, cbc_mac->block, cbc_mac->block);
    }
    OS_FREE(blocks);
    return chk;
}

static void encrypt_msg_blocks(aes_ccm_config_t *cfg, aes_ccm_block_t *msg_blocks, aes_ccm_block_t *blocks, uint8_t *encrpyted_msg) {
    uint32_t bytes_to_write = 0;
    uint32_t bytes_left = cfg->msg_length;

    aes_ccm_get_msg_blocks(cfg, &msg_blocks);
    for (int i = 1; i <= (uint8_t) ceil((double) cfg->msg_length / 16); i++) {
        bytes_to_write = (bytes_left > 16) ? 16 : bytes_left;
        aes_ccm_xor_blocks((msg_blocks + (i - 1)), (blocks + i), (msg_blocks + (i - 1)));
        memcpy(encrpyted_msg + (i - 1) * 16, (msg_blocks + (i - 1)), bytes_to_write);
        bytes_left -= 16;
    }
    OS_FREE(msg_blocks);
}

uint8_t aes_ccm_encrypt(aes_ccm_config_t *cfg, uint8_t *encrpyted_msg, uint8_t *mac) {
    uint8_t chk = EXIT_FAILURE;
    aes_ccm_block_t *key_stream_blocks = NULL;
    aes_ccm_block_t *msg_blocks = NULL;
    aes_ccm_block_t cbc_mac = { { 0 } };

    chk = get_cbc_mac(cfg, &cbc_mac); /* look here */
    aes_ccm_get_key_stream_blocks(&key_stream_blocks, cfg);
    aes_ccm_xor_blocks(&cbc_mac, (key_stream_blocks), &cbc_mac);
    memcpy(mac, cbc_mac.block, cfg->auth_field_size);
    /* CTR MAC is done now */
    encrypt_msg_blocks(cfg, msg_blocks, key_stream_blocks, encrpyted_msg);

    /* msg is encrypted now */
    OS_FREE(key_stream_blocks);
    return chk;
}

uint8_t aes_ccm_decrypt(aes_ccm_config_t *cfg, uint8_t *decrypted_msg, uint8_t *mac_to_check) {
    aes_ccm_block_t *msg_blocks = NULL;
    aes_ccm_block_t *key_stream_blocks = NULL;
    aes_ccm_block_t cbc_mac = { { 0 } };
    aes_ccm_block_t ctr_mac = { { 0 } };
    uint8_t chk = EXIT_SUCCESS;

    /* Decrypt msg */
    aes_ccm_get_key_stream_blocks(&key_stream_blocks, cfg);
    aes_ccm_get_msg_blocks(cfg, &msg_blocks);
    encrypt_msg_blocks(cfg, msg_blocks, key_stream_blocks, decrypted_msg);

    /* Check CTR MAC */
    memcpy(cfg->msg, decrypted_msg, cfg->msg_length);
    get_cbc_mac(cfg, &cbc_mac);
    aes_ccm_xor_blocks(&cbc_mac, (key_stream_blocks), &cbc_mac);
    memcpy(&ctr_mac, cbc_mac.block, cfg->auth_field_size);
    OS_FREE(key_stream_blocks);
    OS_FREE(msg_blocks);

    for (int i = 0; i < cfg->auth_field_size; i++) {
        if (mac_to_check[i] != cbc_mac.block[i])
            chk = EXIT_FAILURE;
    }
    return chk;
}

void aes_debug_func(void) {
    uint8_t nonce[10] = { 0x00, 0x00, 0x6B, 0x4F, 0xCB, 0x60, 0x33, 0x57, 0x00, 0x09 };
    uint8_t msg[22] = { 0x01, 0x00, 0x10, 0x00, 0x05, 0xA0, 0x1E, 0xE3, 0x9E, 0x92, 0x22, 0x1D, 0x5D, 0x69, 0x5B, 0xE5, 0xC9, 0x39, 0x01, 0xE1, 0xDF, 0x86 };
    uint8_t enc_tst[22] = { 0xcc, 0x46, 0xfc, 0xa, 0xf3, 0x18, 0x8f, 0xe3, 0x84, 0x10, 0xbd, 0xb2, 0x0d, 0xdd, 0x44, 0xed, 0xb0, 0xb4, 0x26, 0x97, 0xa3, 0x2e };
    uint8_t aad[4] = { 0 };

    aes_ccm_config_t cfg = { .nonce = nonce, .nonce_length = sizeof(nonce), .msg = msg, .msg_length = sizeof(msg), .additional_data = aad,
                             .additional_data_size = sizeof(aad), .auth_field_size = 10, .key = { { 0xD7, 0x82, 0x8D, 0x13, 0xB2, 0xB0, 0xBD, 0xC3, 0x25, 0xA7,
                                                                                                    0x62, 0x36, 0xDF, 0x93, 0xCC, 0x6B } }, };
    uint8_t enc_msg[22] = { 0 };
    uint8_t mac[4] = { 0 };
    aes_ccm_encrypt(&cfg, enc_msg, mac);

    //    aes_ccm_block_t cbc_mac = { { 0 } };
//    get_cbc_mac(&cfg, &cbc_mac);
//    aes_ccm_block_t *key_stream_blocks = NULL;
//    aes_ccm_get_key_stream_blocks(&key_stream_blocks, &cfg);
//    OS_FREE(key_stream_blocks);
}
