#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include "client_manager.h"

#define SET_BIT(reg, bit) ((reg) |= (1UL << bit))
#define CLEAR_BIT(reg, bit) ((reg) &= ~(1UL << bit))
#define FLIP_BIT(reg, bit) ((reg) ^= (1UL << bit))
#define CHECK_BIT(reg, bit) ((reg) & (1UL << bit))

uint16_t get_random_seed(void);
void read_config(ClientManager* mgr);
void parse_client(char* line, Client* client);
int string_to_billboard_effect(char* input);
int string_to_billboard_selection_option(char* input);
void line_break_string(const char* text, char* top, char* bottom);
void build_scroll_string();

#endif
