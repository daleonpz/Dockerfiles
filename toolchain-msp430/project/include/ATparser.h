#ifndef _AT_PARSER_H_
#define _AT_PARSER_H_

#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "uart.h"
#include "std_casted.h"

void ATparser_send_command(const char *command, ...);
uint8_t *ATparser_receive_reply(uint16_t timeout_ms);
bool ATparser_is_expected_reply(uint16_t timeout_ms, uint8_t* expected_reply);

void ATparser_send_certificate(uint8_t * cert_ca);

#endif
