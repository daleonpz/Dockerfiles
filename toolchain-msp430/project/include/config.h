#ifndef CONFIG_H_
#define CONFIG_H_

/*
 * This is the way the configuration data is expected in infomem.
 */
typedef struct {
    uint32_t sensor_id;     //  4   4
    uint8_t  aes_key[16];       // 16  20
    uint32_t aes_timebase;  //  4  28
    uint32_t max_interval;  //  4  24

    uint8_t  reserved[33];  // 33  61

    uint8_t  options;       //  1  62

    uint16_t config_crc;    //  2  64
} __attribute__ ((packed)) config_type;

config_type *_config;

/*
 * options
 */
// #define RESERVED 0x0080
// #define RESERVED 0x0040
// #define RESERVED 0x0020
// #define RESERVED 0x0010
// #define RESERVED 0x0008
// #define RESERVED 0x0004
#define NO_LED           0x0002
#define BYPASS_ENCRYPTION 0x0001

/*
 * reads config from infomem
 * compares checksum
 * returns non-zero on error
 */
int check_config(config_type * config);

#endif /* CONFIG_H_ */
