#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define GREEN PB0
#define YELLOW PB1
#define RED PB2
#define NUM_SEQ 4

volatile uint32_t ticks = 0;
uint32_t lightChange = 500;
uint32_t now = 0;
uint32_t prevTrig = 0;

ISR(TIMER1_COMPA_vect) {
    ticks++;
}

uint8_t lightSeq[] = {
    (1 << GREEN), 
    (1 << YELLOW),
    (1 << RED),
    (1 << RED) | (1 << YELLOW)
};

void timerInit(void) {
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;
    OCR1A = 249;
    TCCR1B = (1 << WGM12); // Sätt timer1 att räka till OCR1A, trigga interrupt, sen reset
    TCCR1B |= (1 << CS11); // Prescaler
    TIMSK1 |= (1 << OCIE1A); // Tillåter interrupt vid match
    sei(); // Slå på interrupts
}

static inline uint32_t millis(void) {
    uint32_t t;
    cli();
    t = ticks;
    sei();
    return t / 8;
}

int main(void) {
    DDRB = (1 << PB0) | (1 << PB1) | (1 << PB2);
    timerInit();
    uint8_t idx = 0;

    while(1) {
        now = millis();
        if (now - prevTrig >= lightChange) {
            PORTB = lightSeq[idx++ % 4];
            prevTrig = now;
        }
    }

    return 0;
}