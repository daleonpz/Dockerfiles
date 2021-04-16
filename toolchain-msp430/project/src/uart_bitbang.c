/*
 * uart_bitbang.c
 *
 *  Created on: 27.02.2015
 *      Author: QSC AG / mfe based on code of hpo
 */

#include <msp430.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "board.h"
#include "uart_bitbang.h"
#include "delay.h"
#include "main.h"


void delay_us(uint16_t count) 
{
    while(count--) 
    {
        __delay_cycles(1);

    }
}

int writechar(int c) 
{
    if (c == '\n') 
    {
        writechar('\r');
    }
    return bitbang_uart_putchar(c);
}

void bitbang_uart_pin_init(void) 
{
    BB_UART_TX_PxDIR |= BB_UART_TX_BIT;
    BB_UART_TX_PxSEL0 &= ~BB_UART_TX_BIT;
    BB_UART_TX_PxSEL1 &= ~BB_UART_TX_BIT;
    BB_UART_TX_PxOUT |= BB_UART_TX_BIT;
}

int bitbang_uart_putchar(int c) 
{
    int i;
    uint16_t data = c;

    // add stop bit
    data |= 0x0100;

    // add start bit
    data <<= 1;

    // shift out data
    uint16_t shift = 1;
    for (i = 0; i < 10; i++)
    {
        if (data & shift)
            BB_UART_TX_PxOUT |= BB_UART_TX_BIT;
        else
            BB_UART_TX_PxOUT &= ~BB_UART_TX_BIT;

        delay_us(82); // 19200 baud @ 1MHz MCLK //12 delus:102 9600 Baudrate by 8MHz MCLK delus:82

        shift <<= 1;
    }

    return c; // POSIX demands putchar to return given character on success
}

int fputc(int _c, register FILE *_fp)
{
    bitbang_uart_putchar(_c);

    return((unsigned char)_c);
}

int fputs(const char *_ptr, register FILE *_fp)
{
    unsigned int i, len;

    len = strlen(_ptr);

    for(i=0 ; i<len ; i++)
    {
        bitbang_uart_putchar(_ptr[i]);
    }

    return len;
}

