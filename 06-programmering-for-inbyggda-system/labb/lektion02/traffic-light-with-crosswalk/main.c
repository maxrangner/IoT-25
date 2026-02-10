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

uint8_t portbState = 0x00;
uint8_t settingsMask = (
    (1 << WALK_GREEN) | 
    (1 << WALK_RED) | 
    (1 << CAR_GREEN) | 
    (1 << CAR_YELLOW) | 
    (1 << CAR_RED)
);
uint8_t prevBtnState = 0;
uint8_t currentBtnState = 0;

void setPortB() {
    uint8_t prevState = (PORTB &~ settingsMask);
    uint8_t toSet = (portbState & settingsMask);
    PORTB = (toSet | prevState);
}

void init() {
    DDRB = settingsMask;
    DDRB &= ~(1 << BUTTON_PIN); // Input
    PORTB |= (1 << BUTTON_PIN); // Pullup
}

bool buttonPressed() {
    bool returnVal = false;
    currentBtnState = !(PINB & (1 << BUTTON_PIN));
    if (currentBtnState && prevBtnState == 0) {
        returnVal = true;
    }
    prevBtnState = currentBtnState;
    return returnVal;
}

void lightCarsStop(void) {
    portbState &= ~(1 << CAR_GREEN);
    portbState |= (1 << CAR_YELLOW);
    setPortB();
    _delay_ms(2000);
    portbState &= ~(1 << CAR_YELLOW);
    portbState |= (1 << CAR_RED);
    setPortB();
}

void lightCarsGo(void) {
    portbState |= ((1 << CAR_YELLOW) | (1 << CAR_RED));
    setPortB();
    _delay_ms(2000);
    portbState &= ~((1 << CAR_YELLOW) | (1 << CAR_RED));
    portbState |= (1 << CAR_GREEN);
    setPortB();
}

void lightWalkGo() {
    _delay_ms(2000);
    portbState &= ~(1 << WALK_RED);
    portbState |= (1 << WALK_GREEN);
    setPortB();
}

void lightWalkStop() {
    _delay_ms(2000);
    portbState &= ~(1 << WALK_GREEN);
    portbState |= (1 << WALK_RED);
    setPortB();
}

void lightSequence() {
    lightCarsStop();
    lightWalkGo();
    _delay_ms(5000);
    lightWalkStop();
    lightCarsGo();
}


int main(void) {
    init();
    portbState |= ((1 << CAR_GREEN) | (1 << WALK_RED)); // Tänd LED
    setPortB();
    
    while(1) {
        if (buttonPressed()) {
            lightSequence();
        }
    }

    return 0;
}