#include "Display.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include "utils.h"

void display_init(void)
{
    lcd_init();
    lcd_clear();
}

void display_billboard(Billboard* next_billboard, uint32_t now)
{
    static Billboard* prev_billboard = NULL;
    static uint32_t prev_update = 0 - UPDATE_INIT_VAL;
    uint32_t fixed_update_interval = 10000;
    uint32_t scroll_update_interval = 200;
    uint32_t blink_update_interval = 1000;

    static uint8_t blink_state = 1;
    static uint8_t blink_state_prev = 0;

    static uint8_t scroll_pos = 0;

    char top[LCD_BUF_LEN] = "";
    char bottom[LCD_BUF_LEN] = "";
    char top_scroll[LCD_BUF_LEN * 3 + 1] = "                ";
    char bottom_scroll[LCD_BUF_LEN * 3 + 1] = "                ";
    char top_display[LCD_BUF_LEN] = "";
    char bottom_display[LCD_BUF_LEN] = "";
    const char white_space_padding[LCD_BUF_LEN] = "                ";

    if (prev_billboard != next_billboard) {
        printf("New billboard!");
        scroll_pos = 0;
        prev_update = 0 - UPDATE_INIT_VAL;
    }

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
            if (scroll_pos > LCD_TEXT_WIDTH * 2) {
                scroll_pos = 0;
            }
            if (now - prev_update >= scroll_update_interval) {
                line_break_string(next_billboard->billboard_text, top, bottom);
                strcat(top_scroll, top);
                strcat(top_scroll, white_space_padding);
                strcat(bottom_scroll, bottom);
                strcat(bottom_scroll, white_space_padding);

                uint8_t top_i = 0;
                uint8_t bottom_i = 0;
                for (; top_i < LCD_TEXT_WIDTH; top_i++) {
                    if (top_i + scroll_pos >= (LCD_TEXT_WIDTH * 3 + 1) || top_scroll[top_i + scroll_pos] == '\0') break;
                    top_display[top_i] = top_scroll[top_i + scroll_pos];
                }
                for (; top_i < LCD_TEXT_WIDTH; top_i++) {
                    top_display[top_i] = ' ';
                }
                for (; bottom_i < LCD_TEXT_WIDTH; bottom_i++) {
                    if (bottom_i + scroll_pos >= (LCD_TEXT_WIDTH * 3 + 1) || bottom_scroll[bottom_i + scroll_pos] == '\0') break;
                    bottom_display[bottom_i] = bottom_scroll[bottom_i + scroll_pos];
                }
                for (; bottom_i < LCD_TEXT_WIDTH; bottom_i++) {
                    bottom_display[bottom_i] = ' ';
                }
                top_display[16] = '\0';
                bottom_display[16] = '\0';

                lcd_clear();
                lcd_set_cursor(0, 0);
                lcd_printf("%s", top_display);
                lcd_set_cursor(0, 1);
                lcd_printf("%s", bottom_display);

                scroll_pos++;
                prev_update = now;
            }
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
    prev_billboard = next_billboard;
}
