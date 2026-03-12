#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include "client_manager.h"

void display_init(void);
void display_billboard(Billboard* next_billboard, uint32_t now);
void display_rows(Billboard* next_billboard, char* top, char* bottom);
void add_white_space_padding(
    Billboard* next_billboard,
    char* top,
    char* bottom,
    char* top_scroll,
    char* bottom_scroll
);

#endif
