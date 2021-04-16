/*
 * gpio.c
 *
 *  Created on: 09.11.2017
 *      Author: martinfehre
 */

#include <msp430.h>
#include "gpio.h"
#include "board.h"

void gpio_init() 
{
    PM5CTL0 &= ~LOCKLPM5;                    // Disable the GPIO power-on default high-impedance mode
    //set all outputs to OUT;0
    P1DIR = 0xFF;
    P1OUT = 0;
    P2DIR = 0xFF;
    P2OUT = 0;
    P3DIR = 0xFF;
    P3OUT = 0;

    //set ldo pins and enable ldo
    LDO_POWER_SUPPLY_PxDIR |= LDO_POWER_SUPPLY_PIN;
    LDO_POWER_SUPPLY_PxOUT |= LDO_POWER_SUPPLY_PIN;

    //set m66 pins
    PWRKEY_RADIO_PxDIR |= PWRKEY_RADIO_PIN;
    PWRKEY_RADIO_PxOUT &= ~PWRKEY_RADIO_PIN;

    //enable led_blue
    LED_BLUE_PxDIR |= LED_BLUE_BIT;
    LED_BLUE_PxOUT |= LED_BLUE_BIT;

    //enable led_red
    LED_RED_PxDIR |= LED_RED_BIT;
    LED_RED_PxOUT |= LED_RED_BIT;

    // Configure UART pins
    P2SEL0 |= BIT6 | BIT5;                    // 2 UART pins for EnergyCam communication
    P1SEL0 |= BIT4 | BIT5;                    // 2 UART pins for BC95 communication

    P1DIR &= ~BIT4;
    P1OUT |= BIT4;
    P1REN |= BIT4;
}

void gpio_reset_radio(void) 
{
    //set ldo pins and enable ldo
    LDO_POWER_SUPPLY_PxOUT |= LDO_POWER_SUPPLY_PIN;

    P1DIR &= ~BIT4;
    P1OUT |= BIT4;
    P1REN |= BIT4;
}
