/*
 * board.h
 *
 *  Created on: 09.11.2017
 *      Author: martinfehre
 */

#ifndef INCLUDE_BOARD_H_
#define INCLUDE_BOARD_H_

/* LED configuration */
#define LED_RED_BIT                 BIT1
#define LED_RED_PxDIR               P1DIR
#define LED_RED_PxOUT               P1OUT

#define LED_BLUE_BIT                BIT2
#define LED_BLUE_PxDIR              P1DIR
#define LED_BLUE_PxOUT              P1OUT

#define PWRKEY_RADIO_PIN            BIT6
#define PWRKEY_RADIO_PxDIR          P1DIR
#define PWRKEY_RADIO_PxIN           P1IN
#define PWRKEY_RADIO_PxREN          P1REN
#define PWRKEY_RADIO_PxOUT          P1OUT
#define PWRKEY_RADIO_PxSEL          P1SEL

#define LDO_POWER_SUPPLY_PIN        BIT0
#define LDO_POWER_SUPPLY_PxDIR      P1DIR
#define LDO_POWER_SUPPLY_PxIN       P1IN
#define LDO_POWER_SUPPLY_PxREN      P1REN
#define LDO_POWER_SUPPLY_PxOUT      P1OUT
#define LDO_POWER_SUPPLY_PxSEL      P1SEL

#define BB_UART_TX_BIT              BIT3
#define BB_UART_TX_PxOUT            P2OUT
#define BB_UART_TX_PxDIR            P2DIR
#define BB_UART_TX_PxSEL0           P2SEL0
#define BB_UART_TX_PxSEL1           P2SEL1


#endif /* INCLUDE_BOARD_H_ */
