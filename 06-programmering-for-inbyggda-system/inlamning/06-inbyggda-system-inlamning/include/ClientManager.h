#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

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
    int price;
    Billboard billboards[3];
} Client;

typedef struct {
    Client clients[3];
    int num_clients;
    int total_price;
} ClientManager;

void client_manager_init(ClientManager* mgr);
Billboard get_next_billboard(ClientManager* mgr);
// static void config_extractor(config* client_config, Client* clients);

#endif