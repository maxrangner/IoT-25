#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#define WALK_GREEN PB0
#define WALK_RED PB1
#define CAR_GREEN PB2
#define CAR_YELLOW PB3
#define CAR_RED PB4
#define BUTTON_PIN PB5
#define NUM_SEQ 4

void lightCarsStop(void) {
    PORTB &= ~(1 << CAR_GREEN);
    PORTB |= (1 << CAR_YELLOW);
    _delay_ms(2000);
    PORTB &= ~(1 << CAR_YELLOW);
    PORTB |= (1 << CAR_RED);
}

void lightCarsGo(void) {
    PORTB |= ((1 << CAR_YELLOW) | (1 << CAR_RED));
    _delay_ms(2000);
    PORTB &= ~((1 << CAR_YELLOW) | (1 << CAR_RED));
    PORTB |= (1 << CAR_GREEN);
}

void lightWalkGo() {
    _delay_ms(2000);
    PORTB &= ~(1 << WALK_RED);
    PORTB |= (1 << WALK_GREEN);
}

void lightWalkStop() {
    _delay_ms(2000);
    PORTB &= ~(1 << WALK_GREEN);
    PORTB |= (1 << WALK_RED);
}

void buttonPressed() {
    lightCarsStop();
    lightWalkGo();
    _delay_ms(5000);
    lightWalkStop();
    lightCarsGo();
}


int main(void) {
    DDRB = (1 << WALK_GREEN) | (1 << WALK_RED) | (1 << CAR_GREEN) | (1 << CAR_YELLOW) | (1 << CAR_RED); // Output
    DDRB &= ~(1 << BUTTON_PIN); // Input
    PORTB |= (1 << BUTTON_PIN); // Pullup
    PORTB |= ((1 << CAR_GREEN) | (1 << WALK_RED)); // Tänd LED

    while((!(PINB & (1 << BUTTON_PIN)))) {
        _delay_ms(10);
    }
    while(1) {
        if (!(PINB & (1 << BUTTON_PIN))) {
            buttonPressed();
        }
    }

    return 0;
}