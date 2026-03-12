#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include "client_manager.h"

void display_init(void);
void display_billboard(Billboard* next_billboard, uint32_t now);

#endif
