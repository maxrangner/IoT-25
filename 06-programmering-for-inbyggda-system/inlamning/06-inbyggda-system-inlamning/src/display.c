#include "display.h"

#include <stdio.h>
#include <string.h>
#include "lcd.h"
#include "utils.h"
#include "config.h"

static void display_rows(Billboard* next_billboard, char* top, char* bottom);
static void display_scroll_frame(char* top_display, char* top_padded, char* bottom_display, char* bottom_padded, uint8_t* scroll_pos);
static void add_white_space_padding(Billboard* next_billboard,
    char* top,
    char* bottom,
    char* top_padded,
    char* bottom_padded
);
static void create_scroll_frame(char* buffer_display, char* buffer_padded, uint8_t scroll_pos);

void display_init(void)
{
    lcd_init();
    lcd_clear();
}

void display_billboard(Billboard* next_billboard, uint32_t now)
{
    if (next_billboard == NULL) return;
    static Billboard* prev_billboard = NULL;
    static uint32_t prev_update = 0 - UPDATE_INIT_VAL;
    static uint8_t blink_state = 1;
    static uint8_t blink_state_prev = 0;
    static uint8_t scroll_pos = 0;

    char top[LCD_BUF_LEN] = "";
    char bottom[LCD_BUF_LEN] = "";
    char top_padded[LCD_BUF_LEN * 3 + 1] = "";
    char bottom_padded[LCD_BUF_LEN * 3 + 1] = "";
    char top_display[LCD_BUF_LEN] = "";
    char bottom_display[LCD_BUF_LEN] = "";

    if (prev_billboard != next_billboard) {
        scroll_pos = 0;
        prev_update = 0 - UPDATE_INIT_VAL;
    }

    switch (next_billboard->billboard_effect) {
        case fixed:
            if (now - prev_update >= FIXED_UPDATE_INTERVAL) {
                display_rows(next_billboard, top, bottom);
                prev_update = now;
            }
            break;
        case scroll:
            if (now - prev_update >= SCROLL_UPDATE_INTERVAL) {
                add_white_space_padding(next_billboard, top, bottom, top_padded, bottom_padded);
                display_scroll_frame(top_display, top_padded, bottom_display, bottom_padded, &scroll_pos);

                prev_update = now;
            }
            break;
        case blink:
            blink_state = (now / BLINK_UPDATE_INTERVAL) % 2 == 0;

            if (blink_state != blink_state_prev) {
                if (blink_state) {
                    display_rows(next_billboard, top, bottom);
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

static void display_rows(Billboard* next_billboard, char* top, char* bottom)
{
    lcd_clear();
    line_break_string(next_billboard->billboard_text, top, bottom);
    lcd_set_cursor(0, 0);
    lcd_printf("%s", top);
    lcd_set_cursor(0, 1);
    lcd_printf("%s", bottom);
}

static void display_scroll_frame(char* top_display, char* top_padded, char* bottom_display, char* bottom_padded, uint8_t* scroll_pos)
{
    if (*scroll_pos > LCD_TEXT_WIDTH * 2) {
        *scroll_pos = 0;
    }

    create_scroll_frame(top_display, top_padded, *scroll_pos);
    create_scroll_frame(bottom_display, bottom_padded, *scroll_pos);

    lcd_clear();
    lcd_set_cursor(0, 0);
    lcd_printf("%s", top_display);
    lcd_set_cursor(0, 1);
    lcd_printf("%s", bottom_display);

    (*scroll_pos)++;
}

static void add_white_space_padding(Billboard* next_billboard,
    char* top,
    char* bottom,
    char* top_padded,
    char* bottom_padded
)
{
    const char white_space_padding[LCD_BUF_LEN] = "                ";

    line_break_string(next_billboard->billboard_text, top, bottom);
    strcat(top_padded, top);
    strcat(top_padded, white_space_padding);
    strcat(bottom_padded, bottom);
    strcat(bottom_padded, white_space_padding);
}

static void create_scroll_frame(char* buffer_display, char* buffer_padded, uint8_t scroll_pos)
{
    uint8_t i = 0;
    for (; i < LCD_TEXT_WIDTH; i++) {
        if (i + scroll_pos >= ((LCD_TEXT_WIDTH * 3) + 1) || buffer_padded[i + scroll_pos] == '\0') break;
        buffer_display[i] = buffer_padded[i + scroll_pos];
    }
    for (; i < LCD_TEXT_WIDTH; i++) {
        buffer_display[i] = ' ';
    }
    buffer_display[LCD_TEXT_WIDTH] = '\0';
}
