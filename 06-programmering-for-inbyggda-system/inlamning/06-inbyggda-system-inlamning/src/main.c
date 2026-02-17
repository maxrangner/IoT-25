#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ClientManager.h"
#include "display.h"
#include <util/delay.h>
#include <avr/io.h>

ClientManager mgr;

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
    srand(42);
    
    client_manager_init(&mgr);
    Billboard* next_billboard;

    while(1) {
        next_billboard = get_next_billboard(&mgr);
        printf("billboard: %s\n\n", next_billboard->billboard_text);
        _delay_ms(2000);
    }
    printf("Bye!");
    return 0;
}
