/*
 * uart_bitbang.h
 *
 *  Created on: 27.02.2015
 *      Author: QSC AG / mfe
 */

#ifndef UART_BITBANG_H_
#define UART_BITBANG_H_


int writechar(int c);
int bitbang_uart_putchar(int c);
void bitbang_uart_pin_init(void);

#endif /* UART_BITBANG_H_ */
