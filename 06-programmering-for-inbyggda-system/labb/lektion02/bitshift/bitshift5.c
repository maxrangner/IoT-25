unsigned char DDRB;
unsigned char PORTB;
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define BIT_SET(a, b) (a |= (1U << b))
#define BIT_CLEAR(a, b) (a &= ~(1U << b))
#define BIT_FLIP(a, b) (a ^= (1U << b))
#define BIT_CHECK(a, b) (!!(a & (1U << b))) 

void printBits(void const* const ptr)
{
    unsigned char* b = (unsigned char*)ptr;
    unsigned char byte;
    int j;

    for (j = 7; j >= 0; j--)
    {
        byte = (b[0] >> j) & 1;
        printf("%u", byte);
    }
    printf("\n");
}

void _delay_ms(int ms)
{
    struct timespec ts;
    ts.tv_sec = ms / 1000ul;            // whole seconds
    ts.tv_nsec = (ms % 1000ul) * 1000;  // remainder, in nanoseconds
    nanosleep(&ts, NULL);
}

void blink()
{
	// set PINB0 to output in DDRB
	DDRB |= 0b11111111;
    PORTB |= 0b01010101;

	while (1)
	{
        printBits(&PORTB);
        PORTB ^= 0b11111111;
		_delay_ms(1000);
	}
}

int main(void) {
    blink();
    return 0;
}