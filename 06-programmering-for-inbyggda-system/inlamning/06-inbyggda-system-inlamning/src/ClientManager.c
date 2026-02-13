#include "ClientManager.h"
#include <stdio.h>
#include <string.h>

void client_manager_init(ClientManager* mgr) {
    Client newClient1 = {
        .name = "Hederlige Harrys Bilar",
        .price = 100,
        .billboards = {
            {.billboard_content = 10, .billboard_effect = fixed},
            {.billboard_content = 11, .billboard_effect = fixed},
            {.billboard_content = 12, .billboard_effect = fixed}
        }
    };
    Client newClient2 = {
        .name = "Farmor Ankas Pajer AB",
        .price = 100,
        .billboards = {
            {.billboard_content = 20, .billboard_effect = fixed},
            {.billboard_content = 21, .billboard_effect = fixed},
            {.billboard_content = 22, .billboard_effect = fixed}
        }
    };
    Client newClient3 = {
        .name = "Svarte Petters Svartbyggen",
        .price = 200,
        .billboards = {
            {.billboard_content = 30, .billboard_effect = fixed},
            {.billboard_content = 31, .billboard_effect = fixed},
            {.billboard_content = 32, .billboard_effect = fixed}
        }
    };
    Client newClient4 = {
        .name = "Långbens Detektivbyrå",
        .price = 200,
        .billboards = {
            {.billboard_content = 30, .billboard_effect = fixed},
            {.billboard_content = 31, .billboard_effect = fixed},
            {.billboard_content = 32, .billboard_effect = fixed}
        }
    };
        Client newClient5 = {
        .name = "Self promotion",
        .price = 200,
        .billboards = {
            {.billboard_content = 30, .billboard_effect = fixed},
            {.billboard_content = 31, .billboard_effect = fixed},
            {.billboard_content = 32, .billboard_effect = fixed}
        }
    };

    Client clients[NUM_CLIENTS] = {newClient1, newClient2, newClient3, newClient4, newClient5};
    mgr->num_clients = 0; 
    for (int i = 0; i < NUM_CLIENTS; i++) {
        mgr->clients[i] = clients[i];
        mgr->num_clients++;
    }
    mgr->prev_client = newClient5;
}


static void calc_total_price(ClientManager* mgr)
{
    mgr->total_price = 0;
    for (int i = 0; i < mgr->num_clients; i++) {
        mgr->total_price += mgr->clients[i].price;
    }
}

Billboard get_next_billboard(ClientManager* mgr)
{
    Client next_available_clients[mgr->num_clients - 1];
    int num_added_clients = 0;
    for (int i = 0; i < mgr->num_clients; i++) {
        if (strcmp(mgr->clients[i].name, mgr->prev_client.name) != 0) {
            next_available_clients[num_added_clients++] = mgr->clients[i];
        }
    }
    for (int i = 0; i < num_added_clients; i++) {
        printf("%s\n", next_available_clients[i].name);
    }
    mgr->prev_client = next_available_clients[num_added_clients - 1];
    printf("\n");
}