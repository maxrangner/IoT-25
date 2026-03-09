#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/io.h>
#include "ClientManager.h"
#include "display.h"
#include "millis.h"
#include "lcd.h"
#include "utils.h"
#include "uart.h"

int main(void) {
    ClientManager mgr;
    uint8_t random_seed;
    uint32_t update_interval = 10000;
    uint32_t now = 0;
    uint32_t prev_update = 0 - update_interval;
    Billboard* next_billboard;
    static FILE uart_stdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
    
    uart_stdout_init(&uart_stdout);
    millis_init();
    random_seed = get_random_seed();
    srand(random_seed);
    client_manager_init(&mgr);
    display_init();

    Billboard temp_bill = {
        .billboard_effect = blink,
        .billboard_text = "Mysterier? Ring Langben"
    };

    while(1) {
        now = millis();
        if ((now - prev_update) >= update_interval) {
            next_billboard = get_next_billboard(&mgr, now);
            prev_update = now;
        }
        display_billboard(next_billboard, now);
    }
    return 0;
}
