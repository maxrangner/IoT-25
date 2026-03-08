#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include "ClientManager.h"

void display_init();
void display_billboard(Billboard* next_billboard, uint32_t now);

#endif