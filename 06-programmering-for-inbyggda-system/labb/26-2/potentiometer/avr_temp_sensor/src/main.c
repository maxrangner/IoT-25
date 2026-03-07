#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <avr/interrupt.h>
#include "analogRead.h"
#include "millis.h"
#include "uart.h"

#define IN_PIN PC0
#define TEMP_PIN PC1
#define LED_R PB2
#define LED_G PB1
#define LED_B PB0

#define BIT_SET(a, b) (a |= (1U << b))
#define BIT_CLEAR(a, b) (a &= ~(1U << b))
#define BIT_FLIP(a, b) (a ^= (1U << b))
#define BIT_CHECK(a, b) (a & (1U << b))

 int32_t translate(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max)
 {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
 }

int main() {
	BIT_CLEAR(DDRC, TEMP_PIN);
	BIT_SET(DDRB, LED_R);
	BIT_SET(DDRB, LED_G);
	BIT_SET(DDRB, LED_B);

	millis_init();
	sei();
	init_serial();

	uint8_t leds[3] = {LED_R, LED_G, LED_B};

	uint16_t value = 0;
	float celsius = 0;
	int16_t integer = 0;
	int16_t decimals = 0;
	millis_t last_sensor_read = 0;
	millis_t now = 0;
	millis_t temp_sensor_interval = 1000;

	while (1) {
		now = millis();
		
		if (now - last_sensor_read >= temp_sensor_interval) {
			value = analogRead(TEMP_PIN);
			celsius = 1 / (log(1 / (1023. / value - 1)) / 3950. + 1.0 / 298.15) - 273.15;
			integer = (int)celsius;
			celsius -= integer;
			decimals = (int)(abs)(celsius * 100);
			printf("raw_value: %d, temp: %d,%dC\n", value, integer, decimals);
			int16_t translated_val = translate(value, 953, 115, -24, 80);
			printf("%d\n", translated_val);

			for (uint8_t i = 0; i < 3; i++) {
				BIT_CLEAR(PORTB, leds[i]);
			}
			switch (integer) {
				case -200 ... 9:
					BIT_SET(PORTB, LED_B);
					break;
				case 10 ... 29:
					BIT_SET(PORTB, LED_G);
					break;
				case 30 ... 99:
					BIT_SET(PORTB, LED_R);
					break;
			}

			last_sensor_read = now;
		}
	}
	return 0;
}