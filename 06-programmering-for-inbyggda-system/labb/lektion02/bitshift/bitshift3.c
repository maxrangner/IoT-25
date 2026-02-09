unsigned char DDRB;
unsigned char PORTB;
#include <stdlib.h>
#include <stdio.h>
// For `nanosleep()`:
#define _POSIX_C_SOURCE 199309L
#include <time.h>

void _delay_ms(int ms)
{
    struct timespec ts;
    ts.tv_sec = ms / 1000ul;            // whole seconds
    ts.tv_nsec = (ms % 1000ul) * 1000;  // remainder, in nanoseconds
    nanosleep(&ts, NULL);
}

void test123()
{
	// set PINB0 to output in DDRB
	DDRB |= 0b00000001;

	while (1)
	{
		// set PINB0 high
		PORTB |= 0b00000001;
		_delay_ms(5000);
		// set PINB0 low
		PORTB &= 0b11111110;
		_delay_ms(5000);
	}
}