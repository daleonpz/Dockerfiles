#include <msp430.h> 
#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "clock.h"
#include "gpio.h"
#include "timer.h"
#include "rtc.h"
#include "board.h"
#include "config.h"
// #include "uart_bitbang.h"
#include "uart.h"
#include "hw_memmap.h"
#include "app_usart_to_extender.h"
#include "radio.h"

void disable_leds() 
{
    LED_BLUE_PxOUT &= ~LED_BLUE_BIT;
    LED_RED_PxOUT &= ~LED_RED_BIT;
}


int main(void) 
{
    wdt_stop();
    __enable_interrupt();
    gpio_init();
    clock_init();
    setup_timer();
    setup_rtc();
    sleep_sec(5);
    disable_leds();
    uart_init();

    uart_debug(">>>>>>> NEW DEBUG SECTION\r\n");
    
    radio_turn_on();
    uint32_t timestamp = 0;
    timestamp = radio_get_timestamp();
    rtc_set_time(&timestamp);

    usart_init_configuration();
    usart_connect_cloud();

    uint8_t* rbuf;
    t_usart_msg_to_ext extender; 

    uart_reset_a1_buf();
    while(1)
    {
        if( radio_network_registration(1) || (usart_get_powermode() == POWER_OFF) )
        {
            if( uart_is_read_a1_buf_complete() )
            {
                rbuf = usart_read_from_IoT_board();
                if( usart_msg2ext( rbuf, &extender) )
                {
                    usart_parse_ocd( &extender );
                }
                uart_reset_a1_buf();
            }
        }
        else
        {
            usart_disconnect_cloud();
            usart_connect_cloud();
        }
    }
}
