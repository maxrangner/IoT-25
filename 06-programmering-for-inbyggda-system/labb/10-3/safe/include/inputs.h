#ifndef INPUTS_H
#define INPUTS_H

#include "utils.h"
#include <stdint.h>
#include <stdbool.h>

#define BTN_PIN PD4
#define POT_CHANNEL 0

void inputs_init(void);
uint16_t read_analog(uint8_t channel);
bool btn_update(void);
bool btn_pressed(void);

#endif