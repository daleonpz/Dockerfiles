#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "config.h"

//#include "cpu.h"

int check_config(config_type *config) 
{
// 	// uint16_t pointer to config for checksum calculation
// 	uint16_t *configtest = (uint16_t *)config;
// 	uint8_t errors = 0;
// 
// 	// calculate and compare checksum
// 	uint16_t checksum = 0x1234;
// 	for (uint8_t i = 0; i < ((sizeof(config_type) - 2) / 2); i++) {
// 		checksum += *configtest;
// 		#ifdef DEBUG_CONFIG
// 			printf("DEBUG: config: test: %02u, %04x (%04x)\n", i, *configtest, checksum);
// 		#endif
// 		configtest++;
// 	}
// 
// 	// pointer now point to the last word, containing the checksum
// 	if (*configtest != checksum) {
// 		#ifdef DEBUG_CONFIG
// 			printf("ERROR: config: test: checksum mismatch: expect %04x, calculated %04x\n", *configtest, checksum);
// 		#endif
// 		errors++;
// 		// do not attempt anything else
// 		return errors;
// 	}
// #ifdef DEBUG_CONFIG
// 	else {
// 		printf("DEBUG: config: test: checksum matches. (%04x)\n", checksum);
// 	}
// #endif
// 
// 	// copy config to ram
// 	//_config = (config_type *)malloc(sizeof(config_type));
// 	//memcpy(_config, _config_flash, sizeof(config_type));
// 	#ifdef DEBUG_CONFIG
// 		printf("DEBUG: config: Sensor-ID: %08lx\n", config->sensor_id);
// 		printf("DEBUG: config: Loading key:");
// 		for (uint8_t i = 0; i < 16; i++) {
// 			if (i % 2 == 0)
// 				printf(" ");
// 			printf("%02x", config->aes_key[i]);
// 		}
// 		printf("\n");
// 		printf("DEBUG: config: AES timebase: %lu\n", config->aes_timebase);
// 		printf("DEBUG: config: max interval: %u\n", config->max_interval);
// 	#endif
// 
	return 0;
}

