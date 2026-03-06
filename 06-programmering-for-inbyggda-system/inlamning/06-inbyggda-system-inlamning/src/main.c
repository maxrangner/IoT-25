#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/io.h>
#include "ClientManager.h"
#include "display.h"
#include "millis.h"
#include "lcd.h"
#include "utils.h"

void uart_init(void) {
    UBRR0H = 0;
    UBRR0L = 103; // 9600 baud at 16MHz
    UCSR0B = (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

static int uart_putchar(char c, FILE *stream) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = c;
    return 0;
}

static FILE uart_stdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

void uart_stdout_init(void) {
    uart_init();
    stdout = &uart_stdout;
}

int main(void) {
    uart_stdout_init();
    printf("Hello Billboards!\n");
    uint8_t random_seed = get_random_seed();
    printf("%d", random_seed);
    srand(random_seed);

    ClientManager mgr;
    uint32_t now = 0;
    uint32_t prev = 0;
    uint32_t duration = 5000;
    
    lcd_init();
    millis_init();
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
