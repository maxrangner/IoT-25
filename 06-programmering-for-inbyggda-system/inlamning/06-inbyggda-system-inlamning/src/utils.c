#include "utils.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "config.h"

void read_config(ClientManager* mgr)
{
    int client_count = 0;
    FILE* config_file = fopen(CONFIG_FILE, "r");
    if (config_file == NULL) printf("Error opening config_file\n");
    char line[CONFIG_PARSE_BUFFER];

    while(fgets(line, CONFIG_PARSE_BUFFER, config_file)) {
        Client new_client;
        char* name = strtok(line, ",");
        strcpy(new_client.name, name);
        printf("Client: %s -- LOADED!\n", new_client.name);
        new_client.price = atoi(strtok(NULL, ","));
        new_client.display_option = string_to_billboard_selection_option(strtok(NULL, ","));
        new_client.num_billboards = atoi(strtok(NULL, ","));
    
        for (int i = 0; i < new_client.num_billboards; i++) {
            char* billboard_text = strtok(NULL, ",");
            strcpy(new_client.billboards[i].billboard_text, billboard_text);
            new_client.billboards[i].billboard_effect = string_to_billboard_effect(strtok(NULL, ","));
        }
        mgr->clients[client_count++] = new_client;
    }
    mgr->num_clients = client_count;
    fclose(config_file);
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
    if (strcmp(input, "all") == 0 ) { return all; } 
    return one_random;
}
