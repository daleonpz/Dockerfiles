/*
 * uart.c
 *
 *  Created on: 02.06.2020
 *      Author: hdr
 *  Maintainer: Daniel Paredes
 */

#include <msp430.h>
#include <inttypes.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include "eusci_a_uart.h"
#include "timer.h"
#include "uart.h"
#include "board.h"


static volatile uint8_t received_char = 'B';
static uint8_t read_a0_buf[A0_BUF_LENGTH_MAX] ;
static uint8_t read_a0_buf_index = 0;
static uint8_t read_a1_buf[A1_BUF_LENGTH_MAX] ;
static uint8_t read_a1_buf_index = 0;

#define MAX_BUF_DEBUG  (256)
#define MAX_BUF_WRITE  (256)
static char write_buffer[MAX_BUF_WRITE];
static char debug_buffer[MAX_BUF_DEBUG];

static volatile uint8_t _READ_DONE_A1 = 1;

inline uint8_t uart_is_read_a1_buf_complete(void)
{
    if( timer1_get_timeout_flag() == 1 )
    {
        _READ_DONE_A1 = 1;
    }
    return _READ_DONE_A1;
}

/****************************/
/* STATIC FUNCTIONS         */
/****************************/
static void uart_putc_port0(unsigned char c)
{
    // TX buffer ready?
    while (!(UCA0IFG&UCTXIFG));

    EUSCI_A_UART_transmitData(EUSCI_A0_BASE, c);
    sleep_msec(5);

}

static void uart_putc_port1(uint8_t c)
{
    // TX buffer ready?
    while (!(UCA1IFG&UCTXIFG));

    EUSCI_A_UART_transmitData(EUSCI_A1_BASE, c);
    sleep_msec(5);
}

static void uart_puts(uint8_t *str, uart_port port)
{
    if ( port == uart_a0)
    {
        while(*str) uart_putc_port0(*str++);
    }
    else if ( port == uart_a1 )
    {
        while(*str) uart_putc_port1(*str++);
    }
}

/****************************/
/* FUNCTIONS IMPLEMENTATION */
/****************************/
void uart_init(void) 
{

    // Useful calculator
    // http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSP430BaudRateConverter/index.html 
    UCA0CTL1 |= UCSSEL__SMCLK + UCSWRST;
    UCA0BR0 = USCI_A0_BR0_VAL;
    UCA0BR1 = USCI_A0_BR1_VAL;
    UCA0MCTLW = USCI_A0_BRS_VAL;
    UCA0CTL1 &= ~UCSWRST;
    EUSCI_A_UART_enableInterrupt(EUSCI_A0_BASE,EUSCI_A_UART_RECEIVE_INTERRUPT);

    UCA1CTL1 |= UCSSEL__SMCLK + UCSWRST;
    UCA1BR0 = 0x04; //USCI_A1_BR0_VAL;
    UCA1BR1 = 0x00; //USCI_A1_BR1_VAL;
//     UCA1MCTLW = USCI_A1_BRS_VAL;
    UCA1MCTLW_H = 0x05;
    UCA1MCTLW_L = 0x30 + UCOS16;
    UCA1CTL1 &= ~UCSWRST;
    EUSCI_A_UART_enableInterrupt(EUSCI_A1_BASE,EUSCI_A_UART_RECEIVE_INTERRUPT);

}

void uart_clear_a0_buf(void)
{
    __disable_interrupt();
    memset(read_a0_buf, 0, A0_BUF_LENGTH_MAX);
    __enable_interrupt();
}

void uart_clear_a1_buf(void)
{
    __disable_interrupt();
    memset(read_a1_buf, 0, A1_BUF_LENGTH_MAX);
    __enable_interrupt();
}

void uart_clear_buffers(void)
{
    __disable_interrupt();
    memset(read_a0_buf, 0, A0_BUF_LENGTH_MAX);
    memset(read_a1_buf, 0, A1_BUF_LENGTH_MAX);
    __enable_interrupt();
}

void uart_reset_a1_buf(void) 
{
    uart_clear_a1_buf();
    read_a1_buf_index = 0;
    _READ_DONE_A1 = 0;
    timer1_reset_timeout_flag();
    UCA1IE |= UCRXIE;
}


void uart_read(uart_port port, uint16_t timeout_ms ) 
{
    if (port == uart_a0) 
    {
        uart_clear_a0_buf();
        read_a0_buf_index = 0;
        UCA0IE |= UCRXIE;
        timer2_wait_timeout_msec(timeout_ms);
    } 
    else if (port == uart_a1) 
    {
        uart_clear_a1_buf();
        read_a1_buf_index = 0;
        UCA1IE |= UCRXIE;
        timer1_wait_timeout_msec(timeout_ms);
    }
}

void uart_write(uart_port port, const char *command, ...)
{
    va_list args;

    va_start(args, command);

    vsnprintf(write_buffer, MAX_BUF_WRITE, command, args);
    va_end(args);

    uart_puts((uint8_t *)write_buffer, port);
}

void uart_write_direct(uart_port port, uint8_t* buf)
{
    uart_puts(buf,  port);
}


inline uint8_t* uart_a1_get_rbuf(void)
{
    return read_a1_buf;
}

inline uint8_t* uart_a0_get_rbuf(void)
{
    return read_a0_buf;
}



void uart_debug(const uint8_t *command, ...)
{
    va_list args;

    va_start(args, command);
    vsnprintf(debug_buffer, MAX_BUF_DEBUG, (char*) command, args); 
    va_end(args);

    uart_write( uart_a1, "%s\r\n", debug_buffer );

}

/* INTERRUPTIONS */

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCI_A0_VECTOR))) USCI_A0_ISR (void)
#else
#error Compiler not supported!
#endif
{
    switch (__even_in_range(UCA0IV, 4)) 
    {
        case 0:
            break;                             // Vector 0 - no interrupt
        case 2:                                   // Vector 2 - RXIFG
            received_char = UCA0RXBUF;
            // read as many chars as possible until timeout
            read_a0_buf[read_a0_buf_index] = received_char;
            read_a0_buf_index++;
            read_a0_buf[read_a0_buf_index] = '\0';

            if ( read_a0_buf_index >= A0_BUF_LENGTH_MAX)
            {
                UCA0IE &= ~UCRXIE;
            }
            break;

        case 4:
            break;                             // Vector 4 - TXIFG
        default:
            break;
    }
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCI_A1_VECTOR))) USCI_A1_ISR (void)
#else
#error Compiler not supported!
#endif
{
    switch (__even_in_range(UCA1IV, 4)) 
    {
        case 0:
            break;                             // Vector 0 - no interrupt
        case 2:                                   // Vector 2 - RXIFG

            if( _READ_DONE_A1 == 1 )
            {
                break;
            }
            if( read_a1_buf_index == 0)
            {
                timer1_timeout_200msec(); 
            }

            received_char = UCA1RXBUF;

            // read as many chars as possible until timeout
            read_a1_buf[read_a1_buf_index] = received_char;
            read_a1_buf_index++;
            read_a1_buf[read_a1_buf_index] = '\0';



            if ( read_a1_buf_index >= A1_BUF_LENGTH_MAX)
            {
                UCA1IE &= ~UCRXIE;
            }

            break;

        case 4:
            break;                             // Vector 4 - TXIFG
        default:
            break;
    }
}

