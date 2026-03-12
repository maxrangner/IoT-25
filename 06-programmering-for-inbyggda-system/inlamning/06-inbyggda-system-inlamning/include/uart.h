#ifndef UART_H
#define UART_H

#include <stdio.h>

void uart_stdout_init(FILE* uart_stdout);
void uart_init(void);
int uart_putchar(char c, FILE *stream);

#endif
