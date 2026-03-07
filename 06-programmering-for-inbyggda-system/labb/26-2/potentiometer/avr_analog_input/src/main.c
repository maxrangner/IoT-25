#include <stdio.h>
#include <avr/interrupt.h>
#include "analogRead.h"
#include "millis.h"
#include "uart.h"

#define IN_PIN PC0

#define BIT_SET(a, b) (a |= (1U << b))
#define BIT_CLEAR(a, b) (a &= ~(1U << b))
#define BIT_FLIP(a, b) (a ^= (1U << b))
#define BIT_CHECK(a, b) (a & (1U << b))

int main() {
	BIT_CLEAR(DDRC, IN_PIN);

	millis_init();
	sei();
	init_serial();

	uint16_t value;
	uint16_t old_value = 0;
	millis_t millis_since_last_print = 0;
	millis_t current_millis = 0;
	millis_t sensor_read_interval = 100;

	char* noice_levels[] = {
		"quiet",
		"medium",
		"loud",
		"insane"
	};

	while (1) {
		current_millis = millis();
		
		if ((current_millis - millis_since_last_print) > sensor_read_interval) {
			value = analogRead(IN_PIN);

			if (old_value != value) {
				switch (value) {
					case 0 ... 200:
						printf("%s\n", noice_levels[0]);
						break;
					case 201 ... 500:
						printf("%s\n", noice_levels[1]);
						break;
					case 501 ... 800:
						printf("%s\n", noice_levels[2]);
						break;
					case 801 ... 1024:
						printf("%s\n", noice_levels[3]);
						break;
				}
				old_value = value;
			}
			millis_since_last_print = current_millis;
		}
	}
	return 0;
}