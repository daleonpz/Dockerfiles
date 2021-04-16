/*
 * ATparser.c
 *
 *  Created on: 17.06.2020
 *  Maintainer: Daniel Paredes
 */

#include "ATparser.h"

#define MAX_AT_BUF_SIZE (256)
static char _buffer[MAX_AT_BUF_SIZE];

void ATparser_send_command(const char *command, ...)
{
    va_list args;

    va_start(args, command);
    vsnprintf(_buffer,MAX_AT_BUF_SIZE, command, args); 
    va_end(args);

    uart_debug("AT Command: %s",_buffer);

    uart_write( uart_a0, "%s\r\n", _buffer );
}

void ATparser_send_certificate(uint8_t * cert_ca)
{
//     uart_write( uart_a0, "%s\r\n", cert_ca);
    uart_write_direct( uart_a0, cert_ca);
}

uint8_t *ATparser_receive_reply(uint16_t timeout_ms)
{

    uart_read( uart_a0, timeout_ms);
    uint8_t *_buf = uart_a0_get_rbuf();

    uart_debug("Reply: %s",_buf);
    return _buf;
}

bool ATparser_is_expected_reply(uint16_t timeout_ms, uint8_t* expected_reply)
{
    uart_read( uart_a0, timeout_ms);

    uart_debug("AT Reply: %s", uart_a0_get_rbuf()); 

    return (strstr_u8( uart_a0_get_rbuf() , expected_reply) == NULL? false: true); 
}
