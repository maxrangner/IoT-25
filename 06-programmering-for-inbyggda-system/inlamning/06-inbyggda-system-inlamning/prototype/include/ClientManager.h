#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H
#include "config.h"

typedef char content[NUM_MAX_BILLBOARD_CHAR];

enum billboard_effect {
    fixed,
    scroll,
    blink
};

enum billboard_selection_option {
    one_random,
    one_even_odd_min
};

typedef struct {
    content billboard_text;
    int billboard_effect;
} Billboard;

typedef struct {
    char name[50];
    int price;
    int display_option;
    int num_billboards;
    Billboard billboards[3];
} Client;

typedef struct {
    Client clients[NUM_CLIENTS];
    Client* prev_client;
    int num_clients;
    int total_price;
} ClientManager;

void client_manager_init(ClientManager* mgr);
Billboard* get_next_billboard(ClientManager* mgr);

#endif