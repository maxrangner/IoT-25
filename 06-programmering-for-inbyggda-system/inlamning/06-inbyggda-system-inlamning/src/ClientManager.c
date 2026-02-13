#include "ClientManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void client_manager_init(ClientManager* mgr) {
    Client newClient1 = {
        .name = "Hederlige Harrys Bilar",
        .price = 5000,
        .billboards = {
            {.billboard_content = 10, .billboard_effect = fixed},
            {.billboard_content = 11, .billboard_effect = fixed},
            {.billboard_content = 12, .billboard_effect = fixed}
        }
    };
    Client newClient2 = {
        .name = "Farmor Ankas Pajer AB",
        .price = 3000,
        .billboards = {
            {.billboard_content = 20, .billboard_effect = fixed},
            {.billboard_content = 21, .billboard_effect = fixed},
            {.billboard_content = 22, .billboard_effect = fixed}
        }
    };
    Client newClient3 = {
        .name = "Svarte Petters Svartbyggen",
        .price = 1500,
        .billboards = {
            {.billboard_content = 30, .billboard_effect = fixed},
            {.billboard_content = 31, .billboard_effect = fixed},
            {.billboard_content = 32, .billboard_effect = fixed}
        }
    };
    Client newClient4 = {
        .name = "Långbens Detektivbyrå",
        .price = 4000,
        .billboards = {
            {.billboard_content = 30, .billboard_effect = fixed},
            {.billboard_content = 31, .billboard_effect = fixed},
            {.billboard_content = 32, .billboard_effect = fixed}
        }
    };
        Client newClient5 = {
        .name = "Self promotion",
        .price = 1000,
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
    mgr->prev_client = &newClient5;
}


static void calc_total_price(ClientManager* mgr, int* total_price)
{
    for (int i = 0; i < mgr->num_clients; i++) {
        // printf("%d - %d\n", i, mgr->clients[i].price);
        *total_price += mgr->clients[i].price;
    }
}

Client* get_next_billboard(ClientManager* mgr)
{
    int total_sum_prices = 0;
    calc_total_price(mgr, &total_sum_prices);
    total_sum_prices -= mgr->prev_client->price;

    int random_num = rand() % total_sum_prices;
    int cumulative_price = 0;
    
    for (int i = 0; i < mgr->num_clients; i++) {
        if (strcmp(mgr->clients[i].name, mgr->prev_client->name) != 0) {
            cumulative_price += mgr->clients[i].price;
            if (cumulative_price > random_num) {
                mgr->prev_client = &mgr->clients[i];
                return  &mgr->clients[i];
            }
        }
    } 
}
