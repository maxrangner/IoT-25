#include "utils.h"

#include <stdlib.h> 
#include <avr/io.h>
#include <string.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include <ctype.h>
#include "config.h"
#include "clients_db.h"

uint16_t get_random_seed(void) {
    uint16_t seed;
    uint8_t seed_low_bits;
    uint8_t seed_high_bits;

    DDRC &= ~ (1 << PC0); // Set pin to input
    PORTC &= ~(1 << PC0); // Make sure pullup is not enabled
    
    // REFS1:0 = 01 -> AVCC ref
    // MUX3:0 = 0000 -> ADC0
    ADMUX = (1 << REFS0);
    // ADMUX &= ~ (1 << REFS1 | 1 << MUX0 | 1 << MUX1 | 1 << MUX2 | 1 << MUX3); // MUX3:0 to 0 enables ADC0. 

    // ADEN = 1 -> Enable ADC.
    // ADPS2:0 = 111 -> Sets prescaler to 128
    ADCSRA = (1 << ADEN) | 
             (1 << ADPS2) |
             (1 << ADPS1) | 
             (1 << ADPS0); 

    // ADSC to 1 starts the ADC conversion
    // First conversion may be wrong. Keep second reading
    for (uint8_t i = 0; i < 2; i++) {
        ADCSRA |= (1 << ADSC);
        while (ADCSRA & (1 << ADSC));
    }
    seed_low_bits = ADCL;
    seed_high_bits = ADCH;
    seed = (seed_high_bits << 8) | seed_low_bits;

    return seed ^ TCNT0; // Mix seed with Timer0 for extra randomness
}

void read_config(ClientManager* mgr)
{
    int client_count = 0;

    char line_buffer[CONFIG_PARSE_BUFFER_SIZE];
    uint16_t buffer_idx = 0;
    bool done = false;
    
    while (!done) {
        uint16_t line_idx = 0;
        while (1) {
            char c = pgm_read_byte(&clients_db[buffer_idx++]);
            if (c == '\n') break;
            if (c == '\0') {
                done = true;
                break;
            }
            if (line_idx < CONFIG_PARSE_BUFFER_SIZE - 1) {
                line_buffer[line_idx++] = c;
            }
        }
        if (!done) {
            line_buffer[line_idx] = '\0';
            Client new_client;
            parse_client(line_buffer, &new_client);
            mgr->clients[client_count++] = new_client;
            mgr->num_clients++;
        }
    }
}

void parse_client(char* line, Client* client)
{
    char* token = strtok(line, ",");
    strcpy(client->name, token);
    client->price = atoi(strtok(NULL, ","));
    client->display_option = string_to_billboard_selection_option(strtok(NULL, ","));
    client->num_billboards = atoi(strtok(NULL, ","));
    for (int i = 0; i < client->num_billboards; i++) {
        char* billboard_text = strtok(NULL, ",");
        strcpy(client->billboards[i].billboard_text, billboard_text);
        client->billboards[i].billboard_effect = string_to_billboard_effect(strtok(NULL, ","));
    }
    printf("Client: %s -- LOADED!\n", client->name);
    
}

int string_to_billboard_effect(char* input)
{
    if (strcmp(input, "fixed") == 0 ) { return fixed; }
    if (strcmp(input, "scroll") == 0 ) { return scroll; }  
    if (strcmp(input, "blink") == 0 ) { return blink; } 
    return fixed;
}

int string_to_billboard_selection_option(char* input)
{
    if (strcmp(input, "one_random") == 0 ) { return one_random; }
    if (strcmp(input, "one_even_odd_min") == 0 ) { return one_even_odd_min; }  
    return one_random;
}

void line_break_string(const char* text, char* top, char* bottom)
{
    top[0] = '\0';
    bottom[0] = '\0';

    if (strlen(text) <= 16) {
        strcpy(top, text);
        return;
    }

    uint8_t white_space_idx = 0;
    for (uint8_t i = 0; i <= 16; i++) {
        if (isspace(text[i])) {
            white_space_idx = i;
        }
    }

    if (white_space_idx == 0) {
        white_space_idx = 15;
    }

    strncpy(top, text, white_space_idx);
    top[white_space_idx] = '\0';

    const char* text_rest = &text[white_space_idx + 1];
    uint8_t text_rest_len = strlen(text_rest);
    strncpy(bottom, text_rest, 16);
    bottom[16] = '\0';

    // printf("text_len: %d white_space_idx: %d text_rest_len: %d\n", strlen(text), white_space_idx, text_rest_len);
    // printf("top: %s bottom: %s\n", top, bottom);
}

void build_scroll_string(char* text)
{
    
}

