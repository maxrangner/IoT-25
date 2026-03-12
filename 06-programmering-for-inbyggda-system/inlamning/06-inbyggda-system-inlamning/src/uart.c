#include "uart.h"

#include <stdlib.h>
#include <avr/io.h>

void uart_stdout_init(FILE* uart_stdout) {
    uart_init();
    stdout = uart_stdout;
}

void uart_init(void) {
    UBRR0H = 0;
    UBRR0L = 103; // 9600 baud at 16MHz
    UCSR0B = (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

int uart_putchar(char c, FILE *stream) {
    (void)stream;
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = c;
    return 0;
}
