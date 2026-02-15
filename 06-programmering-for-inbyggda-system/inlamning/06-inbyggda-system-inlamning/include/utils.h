#ifndef UTILS_H
#define UTILS_H
#include "ClientManager.h"

void read_config(ClientManager* mgr);
int string_to_billboard_effect(char* input);
int string_to_billboard_selection_option(char* input);

#endif