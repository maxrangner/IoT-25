#include "Display.h"

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include "utils.h"

void display_init()
{
    lcd_init();
    lcd_clear();
    _delay_ms(1000);
}

void display_billboard(Billboard* next_billboard, uint32_t now)
{
    static uint32_t prev_update = 0;
    uint32_t fixed_update_interval = 5000;
    uint32_t scroll_update_interval = 20000;
    uint32_t blink_update_interval = 1000;

    static uint8_t blink_state = 1;
    static uint8_t blink_state_prev = 0;

    char top[17];
    char bottom[17];

    switch (next_billboard->billboard_effect) {
        case 0: // fixed
            if (now - prev_update >= fixed_update_interval) {
                lcd_clear();
                line_break_string(next_billboard->billboard_text, top, bottom);
                lcd_set_cursor(0, 0);
                lcd_printf("%s", top);
                lcd_set_cursor(0, 1);
                lcd_printf("%s", bottom);
                prev_update = now;
            }
            break;
        case 1: // scroll
            lcd_printf("%s", "SCROLL!");
            break;
        case 2: // blink
            blink_state = (now / blink_update_interval) % 2 == 0;

            if (blink_state != blink_state_prev) {
                if (blink_state) {
                    lcd_clear();
                    line_break_string(next_billboard->billboard_text, top, bottom);
                    lcd_set_cursor(0, 0);
                    lcd_printf("%s", top);
                    lcd_set_cursor(0, 1);
                    lcd_printf("%s", bottom);
                } else {
                    lcd_clear();
                }
                blink_state_prev = blink_state;
            }
            break;
        default: break;
    }
}