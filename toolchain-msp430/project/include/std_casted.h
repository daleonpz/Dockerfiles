#ifndef _STD_CASTED_H_ 
#define _STD_CASTED_H_ 

#include <stdint.h>

/////////////
// Lib
//   replaced functions
#include <string.h>
uint8_t *strstr_u8(uint8_t *haystack, uint8_t *needle);
size_t strlen_u8( uint8_t *s);

#include <stdlib.h>
uint8_t atoi_u8( uint8_t* nptr);
uint32_t atoi_u32( uint8_t* nptr);



void itoa_u32(uint32_t n, uint8_t s[]);

#endif 
