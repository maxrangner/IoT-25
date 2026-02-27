/*
PCINTn
Sätt PIN1 i PORTD hög när du får en falling edge på PIN0 i PORTB, och låg när du får en rising edge på PIN0 i PORTB.

INT0
Sätt PIN1 i PORTD hög när du får en falling edge på PIN2 på PORTD.
*/

#include <stdio.h>
#include <avr/interrupt.h>
#include "analogRead.h"
#include "millis.h"
#include "uart.h"

#define INT1_PIN PB0
#define INT2_PIN PD2
#define LED_PIN PD1

#define BIT_SET(a, b) (a |= (1U << b))
#define BIT_CLEAR(a, b) (a &= ~(1U << b))
#define BIT_FLIP(a, b) (a ^= (1U << b))
#define BIT_CHECK(a, b) (a & (1U << b))

// PCINT0 = PORTB
ISR(PCINT0_vect) {
  const uint8_t pinMask = 1 << INT1_PIN;
  static uint8_t prevState = 0;
  uint8_t currState = PINB;
  uint8_t changedPins = currState ^ prevState;
  
  if (changedPins & pinMask) {
    if (!(prevState & pinMask) && (currState & pinMask)) {
      BIT_SET(PORTD, LED_PIN);
    }
    else {
      BIT_CLEAR(PORTD, LED_PIN);
    }
  }
  prevState = currState;
}

// PCINT2 = PORTD
ISR(PCINT2_vect) {
  const uint8_t pinMask = 1 << PD2;
  static uint8_t prevState = 0;
  uint8_t currState = PIND;
  uint8_t changedPins = currState ^ prevState;
  
  if (changedPins & pinMask) {
    if (!(prevState & pinMask) && (currState & pinMask)) {
      BIT_SET(PORTD, LED_PIN);
    }
    else {
      BIT_CLEAR(PORTD, LED_PIN);
    }
  }
  prevState = currState;
}

int main() {
	BIT_SET(PCMSK0, PCINT0);
  BIT_SET(PCMSK2, PCINT18);
	BIT_SET(PCICR, PCIE0);
  BIT_SET(PCICR, PCIE2);
	sei();

  BIT_CLEAR(DDRB, INT1_PIN);
	BIT_SET(PORTB, INT1_PIN);

  BIT_CLEAR(DDRD, INT2_PIN);
	BIT_SET(PORTD, INT2_PIN);

  BIT_SET(DDRD, LED_PIN);
	
	while (1) {
		
	}
	return 0;
}