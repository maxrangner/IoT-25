#include "utils.h"


#include <stdlib.h> 
#include <avr/io.h>
#include <string.h>
#include <avr/pgmspace.h>
#include "config.h"
#include "clients_db.h"

uint8_t get_random_seed() {
    SET_BIT(DDRC, PC0);
    return CHECK_BIT(DDRC, PB0);
}

void read_config(ClientManager* mgr)
{
    int client_count = 0;

    char line_buffer[CONFIG_PARSE_BUFFER_SIZE];
    uint16_t buffer_idx = 0;
    uint8_t done = 0;
    
    while (!done) {
        uint16_t line_idx = 0;
        while (1) {
            char c = pgm_read_byte(&clients_db[buffer_idx++]);
            if (c == '\n') break;
            if (c == '\0') {
                done = 1;
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
