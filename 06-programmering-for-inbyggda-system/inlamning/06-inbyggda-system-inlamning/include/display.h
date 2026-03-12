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
    char* top_padded,
    char* bottom_padded
);
void create_scroll_frame(char* buffer_display, char* buffer_padded, uint8_t scroll_pos);
void display_scroll_frame(char* top_display, char* top_padded, char* bottom_display, char* bottom_padded, uint8_t* scroll_pos);

#endif
