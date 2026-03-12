#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "utils.h"
#include "uart.h"
#include "spi.h"
#include "rc522.h"
#include "millis.h"
#include "servo.h"
#include "inputs.h"

void init_led(void);
void turn_on_led(void);
void turn_off_led(void);
bool is_valid_uid(rc522_tag_t* tag, uint8_t* tag_key);
uint8_t tag_key[4] = {0x18, 0x74, 0x69, 0x52};
uint8_t passkey[3] = {0, 1, 2};

int main(void)
{
    init_serial();
    millis_init();
    spi_master_init();
    rc522_init();
    init_servo();
    inputs_init();
    init_led();
    sei();
    
    bool is_pass_locked = true;
    bool is_tag_locked = true;

    uint32_t now = 0;
    uint32_t prev_tag_read = 0;
    uint32_t tag_read_interval = 1000;
    uint32_t prev_input_read = 0;
    uint32_t input_read_interval = 5;

    rc522_tag_t tag;
    bool servo = true;
    uint16_t pot_read[3] = {0, 0, 0};

    printf("[ Setup complete ]\r\n");
    
    while (1) {
        now = millis();
        
        if (now - prev_input_read > input_read_interval) {
            if (btn_pressed()) {
                pot_read[0] = pot_read[1];
                pot_read[1] = pot_read[2];
                pot_read[2] = read_analog(POT_CHANNEL) / 100;
                printf("%d %d %d\n", pot_read[0], pot_read[1], pot_read[2]);
            }
            prev_input_read = now;
        }

        is_pass_locked = false;
        for (uint8_t i = 0; i < 3; i++) {
            if (pot_read[i] != passkey[i]) {
                is_pass_locked = true;
                break;
            }
        }

        if (is_pass_locked) {
            turn_off_led();
            servo_set_percentage(-50);
        } else {
            turn_on_led();
            if (now - prev_tag_read > tag_read_interval) {
                tag = rc522_read_tag();
                if (tag.status == RC522_OK) {
                    is_tag_locked = is_valid_uid(&tag, tag_key);
                } else is_tag_locked = true;
                prev_tag_read = now;
            }
        }
        if (!is_tag_locked) {
            servo_set_percentage(50);
        }
    }
}

bool is_valid_uid(rc522_tag_t* tag, uint8_t* tag_key)
{
    for (uint8_t i = 0; i < RC522_UID_SIZE; i++) {
        printf("%d ", tag_key[i]);
        if (tag->uid[i] != tag_key[i]) {
            printf("%02X != %02X - Wrong UID!\n", tag->uid[i], tag_key[i]);
            return true;
        }
    }
    printf("Success!\n");
    return false;
}

void init_led(void)
{
    SET_BIT(DDRD, PD3);
}

void turn_on_led(void)
{
    SET_BIT(PORTD, PD3);
}

void turn_off_led(void)
{
    CLEAR_BIT(PORTD, PD3);
}
