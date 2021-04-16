/*
 * uart.h
 *
 *  Created on: 02.06.2020
 *      Author: hdr
 */

#ifndef INCLUDE_UART_H_
#define INCLUDE_UART_H_

#define A0_BUF_LENGTH_MAX   (256)
#define A1_BUF_LENGTH_MAX   (1024)

#include "def.h"

typedef enum{
    b_9600,
    b_460800
}uart_bautrate;

typedef enum{
    uart_a0,
    uart_a1
}uart_port;

void uart_reset_a1_buf(void);

#ifndef TEST
inline uint8_t uart_is_read_a1_buf_complete(void);
#endif

extern void uart_init(void);
extern uint8_t uart_check_radio_module(uint8_t number_of_tries);
extern uint8_t uart_sim_card_check(void);

void uart_write_direct(uart_port port, uint8_t* buf);
void uart_write(uart_port port, const char *command, ...);
void uart_read(uart_port port, uint16_t timeout_ms ) ;

uint8_t* uart_a0_get_rbuf(void);
uint8_t* uart_a1_get_rbuf(void);

void uart_clear_a1_buf(void);
void uart_clear_a0_buf(void);

void uart_clear_buffers(void);

void uart_debug(const uint8_t *command, ...);

#define USCI_A0_INPUT_CLK            (7962624L)  // in Hz 1MHz = 983040 | 8MHz = 7962624
#define USCI_A0_BAUD_RATE            (9600)
#define USCI_A0_DIV_INT              (USCI_A0_INPUT_CLK/USCI_A0_BAUD_RATE)
#define USCI_A0_BR0_VAL              (USCI_A0_DIV_INT & 0x00FF)
#define USCI_A0_BR1_VAL              ((USCI_A0_DIV_INT >> 8) & 0xFF)
#define USCI_A0_DIV_FRAC_NUMERATOR   (USCI_A0_INPUT_CLK - (USCI_A0_DIV_INT*USCI_A0_BAUD_RATE))
#define USCI_A0_DIV_FRAC_NUM_X_8     (USCI_A0_DIV_FRAC_NUMERATOR*8)
#define USCI_A0_DIV_FRAC_X_8         (USCI_A0_DIV_FRAC_NUM_X_8/USCI_A0_BAUD_RATE)
#if (((USCI_A0_DIV_FRAC_NUM_X_8-(USCI_A0_DIV_FRAC_X_8*USCI_A0_BAUD_RATE))*10)/USCI_A0_BAUD_RATE < 5)
#define USCI_A0_BRS_VAL              (USCI_A0_DIV_FRAC_X_8<< 1)
#else
#define USCI_A0_BRS_VAL              ((USCI_A0_DIV_FRAC_X_8+1)<< 1)
#endif

#define USCI_A1_INPUT_CLK            (7962624L)  // in Hz 1MHz = 983040 | 8MHz = 7962624
#define USCI_A1_BAUD_RATE            (9600)
#define USCI_A1_DIV_INT              (USCI_A1_INPUT_CLK/USCI_A1_BAUD_RATE)
#define USCI_A1_BR0_VAL              (USCI_A1_DIV_INT & 0x00FF)
#define USCI_A1_BR1_VAL              ((USCI_A1_DIV_INT >> 8) & 0xFF)
#define USCI_A1_DIV_FRAC_NUMERATOR   (USCI_A1_INPUT_CLK - (USCI_A1_DIV_INT*USCI_A1_BAUD_RATE))
#define USCI_A1_DIV_FRAC_NUM_X_8     (USCI_A1_DIV_FRAC_NUMERATOR*8)
#define USCI_A1_DIV_FRAC_X_8         (USCI_A1_DIV_FRAC_NUM_X_8/USCI_A1_BAUD_RATE)
#if (((USCI_A1_DIV_FRAC_NUM_X_8-(USCI_A1_DIV_FRAC_X_8*USCI_A1_BAUD_RATE))*10)/USCI_A1_BAUD_RATE < 5)
#define USCI_A1_BRS_VAL              (USCI_A1_DIV_FRAC_X_8<< 1)
#else
#define USCI_A1_BRS_VAL              ((USCI_A1_DIV_FRAC_X_8+1)<< 1)
#endif


#endif /* INCLUDE_UART_H_ */
