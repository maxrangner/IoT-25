#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "max72xx.h"
#include "uart.h"
#include "millis.h"
#include "analogRead.h"

#define SET_BIT(reg, bit) ((reg) |= (1UL << bit))
#define CLEAR_BIT(reg, bit) ((reg) &= ~(1UL << bit))
#define FLIP_BIT(reg, bit) ((reg) ^= (1UL << bit))
#define CHECK_BIT(reg, bit) ((reg) & (1UL << bit))

#define JOY_PIN_X PC1
#define JOY_PIN_Y PC0

int main() {
	init_serial();
	millis_init();
	max7219_init();

	SET_BIT(DDRC, JOY_PIN_X);
	SET_BIT(DDRC, JOY_PIN_Y);

	sei();

	int now = 0;
	int prev_now = 0;
	int update_interval = 100;
	
	int joy_x;
	int joy_y;
	int x = 0;
	int y = 0;

	struct worm {
		
	}

	while (1) {
		now = millis();
		if (now - prev_now >= update_interval) {
			joy_x = analogRead(JOY_PIN_X);
			joy_y = analogRead(JOY_PIN_Y);
			if (joy_x < 500) x++;
			if (joy_x > 520) x--;
			if (joy_y < 500) y++;
			if (joy_y > 520) y--;
			if (x < 0) x = 0;
			if (x > 15) x = 15;
			if (y < 0) y = 0;
			if (y > 7) y = 7;
			printf("JoyH: %d, JoyV: %d    |    x: %d y: %d\n", joy_x, joy_y, x, y);
			max7219b_set(x, y);
			max7219b_out();
			prev_now = now;
		}

		// for(int i = 0; i < 16; i++) {
		// 	printf("%d\n", i);

		// 	max7219b_set(i, y);
		// 	max7219b_clr((i + 13) % 16 , y); // (i + (16 - 3)) % 16
		// 	max7219b_out();
			
		// 	_delay_ms(500);
		// }
	}
	return 0;
}
