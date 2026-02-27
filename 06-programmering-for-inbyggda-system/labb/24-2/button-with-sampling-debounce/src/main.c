#include <avr/io.h>
#include <stdbool.h>
#include "millis.h"
#include "bit_utils.h"

#define BTN_PIN PB0
#define LED_PIN PB1

uint32_t now = 0;
uint32_t btn_update_timer = 5;

uint8_t sampling_mask = 0b00111111;
uint8_t btn_samples = 0b11111111;

bool btn_state = 1;
bool btn_new_state = 1;
bool btn_state_prev = 1;
bool btn_update = 0;


int main(void)
{
    CLEAR_BIT(DDRB, BTN_PIN);
    SET_BIT(PORTB, BTN_PIN);
    SET_BIT(DDRB, LED_PIN);

    millis_init();
    
    while(1) {
        now = millis();
        btn_samples <<= 1;
        btn_samples |= IS_BTN_PRESSED(BTN_PIN);

        if ((btn_samples & sampling_mask) == sampling_mask) {
            btn_new_state = 1;
            btn_update = 1;
        } else if ((btn_samples & sampling_mask) == 0) {
            btn_new_state = 0;
            btn_update = 1;
        }
        if ((btn_new_state != btn_state) && btn_update == 1) {
            btn_state = btn_new_state;
            btn_update = 0;
        }
    }
}
