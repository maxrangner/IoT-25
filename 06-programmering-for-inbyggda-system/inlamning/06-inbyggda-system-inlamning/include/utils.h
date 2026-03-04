#ifndef UTILS_H
#define UTILS_H
#include "ClientManager.h"

#define SET_BIT(reg, bit) ((reg) |= (1UL << bit))
#define CLEAR_BIT(reg, bit) ((reg) &= ~(1UL << bit))
#define FLIP_BIT(reg, bit) ((reg) ^= (1UL << bit))
#define CHECK_BIT(reg, bit) ((reg) & (1UL << bit))

void read_config(ClientManager* mgr);
void parse_client(char* line, Client* client);
int string_to_billboard_effect(char* input);
int string_to_billboard_selection_option(char* input);

#endif