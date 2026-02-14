#include "ClientManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void client_manager_init(ClientManager* mgr) {
    Client newClient1 = {
        .name = "Hederlige Harrys Bilar",
        .price = 5000,
        .display_option = one_random,
        .num_billboards = 3,
        .billboards = {
            {.billboard_text = "Köp bil hos Harry", .billboard_effect = scroll},
            {.billboard_text = "En god bilaffär (för Harry!)", .billboard_effect = fixed},
            {.billboard_text = "Hederlige Harrys Bilar", .billboard_effect = blink}
        }
    };
    Client newClient2 = {
        .name = "Farmor Ankas Pajer AB",
        .price = 3000,
        .display_option = one_random,
        .num_billboards = 2,
        .billboards = {
            {.billboard_text = "Köp paj hos Farmor Anka", .billboard_effect = scroll},
            {.billboard_text = "Skynda innan Mårten ätit alla pajer" , .billboard_effect = fixed}
        }
    };
    Client newClient3 = {
        .name = "Svarte Petters Svartbyggen",
        .price = 1500,
        .display_option = one_even_odd_min,
        .num_billboards = 2,
        .billboards = {
            {.billboard_text = "Låt Petter bygga åt dig", .billboard_effect = scroll},
            {.billboard_text = "Bygga svart? Ring Petter" , .billboard_effect = scroll}
        }
    };
    Client newClient4 = {
        .name = "Långbens Detektivbyrå",
        .price = 4000,
        .display_option = all,
        .num_billboards = 2,
        .billboards = {
            {.billboard_text = "Mysterier? Ring Långben", .billboard_effect = fixed},
            {.billboard_text = "Långben fixar biffen", .billboard_effect = fixed}
        }
    };
    Client newClient5 = {
        .name = "Self promotion",
        .price = 1000,
        .display_option = all,
        .num_billboards = 1,
        .billboards = {
            {.billboard_text =  "Synas här? IOT:s Reklambyrå", .billboard_effect = fixed},
        }
    };

    Client clients[NUM_CLIENTS] = {newClient1, newClient2, newClient3, newClient4, newClient5};
    mgr->num_clients = 0; 
    for (int i = 0; i < NUM_CLIENTS; i++) {
        mgr->clients[i] = clients[i];
        mgr->num_clients++;
    }
    mgr->prev_client = &mgr->clients[mgr->num_clients - 1];
}


static int calc_total_price(const ClientManager* mgr)
{
    int return_val = 0;
    for (int i = 0; i < mgr->num_clients; i++) {
        return_val += mgr->clients[i].price;
    }

    return return_val;
}

static int generate_rand_num(ClientManager* mgr)
{
    int total_sum_prices = 0;
    total_sum_prices = calc_total_price(mgr);
    total_sum_prices -= mgr->prev_client->price;
    int random_num = rand() % total_sum_prices;

    return random_num;
}

Client* get_next_client(ClientManager* mgr)
{
    Client* prev_client = mgr->prev_client;
    Client* next_client = NULL;
    int random_num = generate_rand_num(mgr);
    printf("random_num: %d, prev_client: %s\n", random_num, prev_client->name);
    int cumulative_price = 0;
    for (int i = 0; i < mgr->num_clients; i++) {
        Client* current_client = &mgr->clients[i];
        
        if (current_client != prev_client) {
            cumulative_price += current_client->price;
            printf("cumulative_price: %d\n", cumulative_price);
            if (cumulative_price > random_num) {
                printf("cumulative_price: %d > %d\n", cumulative_price, random_num);
                mgr->prev_client = current_client;
                next_client = current_client;
                break;
            }
        }
    }
    printf("next_client: %s\n", next_client->name);
    return next_client;
}

// Billboard* get_next_billboard(ClientManager* mgr)
// {
//     Client* next_client = get_next_client(mgr);
//     Billboard* return_billboard = &next_client->billboards[0];

//     switch (next_client->display_option) {
//         case 0: // one_random
//             return_billboard = &next_client->billboards[rand() % next_client->num_billboards];
//             break;
//         case 1: // one_even_odd_min
//             break;
//         case 2: //all
//             break;
//     }

//     return return_billboard;
// }
