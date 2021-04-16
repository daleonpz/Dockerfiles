/*
 * aes-ccm.h
 *
 *  Created on: 20.03.2019
 *      Author: Felix Schütte
 */

#ifndef INC_AES_CCM_H_
#define INC_AES_CCM_H_

#define         AES_CCM_DEBUG   (0)

typedef struct{
    uint8_t key[16];
}aes_ccm_key_t;

typedef struct{
    uint8_t block[16];
}aes_ccm_block_t;

typedef struct{
    uint8_t l_encoded : 3;
    uint8_t m_encoded : 3;
    uint8_t a_data: 1;
    uint8_t reserved: 1;
}aes_ccm_flags_field_t;

typedef struct{
    uint8_t *nonce;
    uint8_t nonce_length;
    uint8_t *msg;
    uint64_t msg_length;
    uint8_t *additional_data;
    uint64_t additional_data_size;
    uint16_t auth_field_size;
    aes_ccm_key_t key;
}aes_ccm_config_t;

typedef struct{
    uint8_t *encoded_aad_length;
    uint8_t size;
}aes_ccm_aad_length_encoded_t;

uint8_t aes_ccm_encrypt(aes_ccm_config_t *cfg, uint8_t *encrpyted_msg, uint8_t *mac);
uint8_t aes_ccm_decrypt(aes_ccm_config_t *cfg, uint8_t *decrpyted_msg, uint8_t *mac_to_check);
uint8_t get_cbc_mac(aes_ccm_config_t *cfg, aes_ccm_block_t *cbc_mac);
void aes_debug_func(void);
#endif /* INC_AES_CCM_H_ */
