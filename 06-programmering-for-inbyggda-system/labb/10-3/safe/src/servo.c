#include <avr/io.h>
#include <avr/interrupt.h>
#include "servo.h"
 
#define TIME_VALUE	(40000) 
#define RESET_VALUE	(65636UL - TIME_VALUE)
#define STOP_VALUE	(TIME_VALUE * 0.075) // (TIME_VALUE * 0.076)
#define RANGE		(TIME_VALUE * 0.0482) // (TIME_VALUE * 0.025)
 
ISR(TIMER1_OVF_vect) {
	TCNT1 = RESET_VALUE;
 
	PORT_SERVO |= (1 << PIN_SERVO);
}
 
ISR(TIMER1_COMPA_vect) {
	PORT_SERVO &= ~(1 << PIN_SERVO);
}

void init_servo(void) {
	// Config pins as output
	DDR_SERVO |= (1 << PIN_SERVO);
 
	// Use mode 0, clkdiv = 8
	TCCR1A = 0;
	TCCR1B = (0 << CS12) | (1 << CS11) | (0 << CS10);
	// Interrupts on OCA and OVF
	TIMSK1 = (1 << OCIE1A) | (1 << TOIE1);
 
	TCNT1 = RESET_VALUE;
 
	servo_set_percentage(0);
}
 
void servo_set_percentage(signed char percentage) {
	if (percentage >= -100 && percentage <= 100) {
		OCR1A = RESET_VALUE + STOP_VALUE + (RANGE / 100 * percentage);
	}
}

