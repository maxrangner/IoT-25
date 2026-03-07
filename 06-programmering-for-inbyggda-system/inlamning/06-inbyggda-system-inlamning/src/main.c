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
    uint32_t now = 0;
    uint32_t prev = 0;
    uint32_t duration = 5000;
    static FILE uart_stdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
    
    uart_stdout_init(&uart_stdout);
    lcd_init();
    millis_init();
    random_seed = get_random_seed();
    srand(random_seed);
    client_manager_init(&mgr);
    Billboard* next_billboard;

    lcd_clear();
    lcd_printf("Welcome!");
    _delay_ms(1000);

    while(1) {
        now = millis();
        if ((now - prev) >= duration) {
            next_billboard = get_next_billboard(&mgr);
            printf("billboard: %s\n\n", next_billboard->billboard_text);
            lcd_clear();
            lcd_printf(next_billboard->billboard_text);
            prev = now;
        }
    }
    printf("Bye!");
    return 0;
}
