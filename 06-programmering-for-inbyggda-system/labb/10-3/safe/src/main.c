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

bool is_valid_uid(rc522_tag_t* tag, uint8_t* tag_key);
uint8_t tag_key[4] = {0x18, 0x74, 0x69, 0x52};

int main(void)
{
    init_serial();
    spi_master_init();
    rc522_init();
    init_servo();
    millis_init();
    sei();
    
    rc522_tag_t tag;
    bool is_locked = true;
    uint32_t now = 0;
    uint32_t now_prev = 0;
    uint32_t update_interval = 1000;
    bool servo = true;

    printf("RC522 ready! Wee!\r\n");

    while (1) {
        now = millis();
        if (now - now_prev > update_interval) {
            tag = rc522_read_tag();
            if (tag.status == RC522_OK) {
                is_locked = is_valid_uid(&tag, tag_key);
            } else is_locked = true;
            now_prev = now;
        }
        if (is_locked) {
            servo_set_percentage(-50);
        } else {
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