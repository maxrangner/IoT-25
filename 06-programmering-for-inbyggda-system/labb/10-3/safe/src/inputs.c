#include "inputs.h"
#include <avr/io.h>

static uint8_t btn_samples = 0b11111111;
static uint8_t btn_mask = 0b11111111;

void inputs_init(void)
{
    // POT INIT
    SET_BIT(ADMUX, REFS0);
    ADCSRA = (1 << ADEN) |
             (1 << ADPS2) |
             (1 << ADPS1) |
             (1 << ADPS0);
    while(CHECK_BIT(ADCSRA, ADSC)) {
    }

    // BTN INIT
    CLEAR_BIT(DDRD, BTN_PIN);
    SET_BIT(PORTD, BTN_PIN);
}

uint16_t read_analog(uint8_t channel)
{
    ADMUX = (1 << REFS0) |
            (channel & 0x0F);

    for (uint8_t i = 0; i < 2; i++) {
        SET_BIT(ADCSRA, ADSC);
        while(CHECK_BIT(ADCSRA, ADSC)) {
        }
    }
    return ADC;
}

bool btn_update(void)
{
    static bool state = true;


    btn_samples <<= 1;
    btn_samples |= CHECK_BIT(PIND, BTN_PIN) ? 1 : 0;
    
    if (btn_samples == 0xFF) {
        state = true;
    } else if (btn_samples == 0x00) {
        state = false;
    }
    return state;
}

bool btn_pressed(void)
{
    static bool prev_state = 1;
    bool state = btn_update();
    bool pressed = (prev_state == 1 && state == 0);
    prev_state = state;
    return pressed;
}
