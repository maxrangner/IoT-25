#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H
#include "config.h"

typedef int content;

enum billboard_effect {
    fixed,
    scroll,
    blink
};

typedef struct {
    content billboard_content;
    int billboard_effect;
} Billboard;

typedef struct {
    char name[50];
    int price;
    Billboard billboards[3];
} Client;

typedef struct {
    Client clients[NUM_CLIENTS];
    Client* prev_client;
    int num_clients;
    int total_price;
} ClientManager;

void client_manager_init(ClientManager* mgr);
Client* get_next_billboard(ClientManager* mgr);
// static void config_extractor(config* client_config, Client* clients);

#endif