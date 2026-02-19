#include <avr/io.h>
#include "bit_utils.h"
#include "millis.h"

int main(void)
{
    SET_BIT(DDRB, PB5);
    SET_BIT(PORTB, PB5);
    millis_init();

    uint32_t now = 0;
    uint32_t prev = 0;
    uint32_t duration = 1000;

    while(1) {
        now = millis();
        if ((now - prev) >= duration) {
            FLIP_BIT(PORTB, PB5);
            prev = now;
        }
    }
}