#include "millis.h"
#include <avr/power.h>
#include <util/atomic.h>
#include <avr/interrupt.h>
#include "bit_utils.h"

static volatile uint32_t ms;

void millis_init(void)
{
    SET_BIT(TCCR0A, WGM01);
    SET_BIT(TCCR0B, CS00);
    SET_BIT(TCCR0B, CS01);
    OCR0A = 249;
    SET_BIT(TIMSK0, OCIE0A);
    sei();
    ms = 0;
}

ISR(TIMER0_COMPA_vect)
{
    ++ms;
}

uint32_t millis(void)
{
    return ms;
}