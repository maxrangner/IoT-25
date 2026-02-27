#include <avr/io.h>
#include <stdbool.h>
#include "millis.h"
#include "bit_utils.h"

#define BTN_PIN PB0
#define LED_PIN PB1

bool btn_state = 1;
bool btn_raw_read = 1;
bool btn_raw_read_prev = 1;
bool ledIsOn = false;
uint32_t now = 0;
uint32_t btn_prev = 0;
uint32_t btn_debounce = 20;
uint32_t led_prev = 0;
uint32_t led_debounce = 0;

int main(void)
{
    CLEAR_BIT(DDRB, BTN_PIN);
    SET_BIT(PORTB, BTN_PIN);
    SET_BIT(DDRB, LED_PIN);

    millis_init();
    
    while(1) {
        now = millis();
        btn_raw_read = IS_BTN_PRESSED(BTN_PIN);
        if (btn_raw_read != btn_raw_read_prev) {
            btn_prev = now;
        }
        if ((now - btn_prev >= btn_debounce) && (btn_raw_read != btn_state)) {
            if (btn_raw_read == 1) {
                FLIP_BIT(PORTB, LED_PIN);
            }
            btn_state = btn_raw_read;
        }
        btn_raw_read_prev = btn_raw_read;
    }
}
