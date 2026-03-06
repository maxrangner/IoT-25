#include "ClientManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void client_manager_init(ClientManager* mgr) 
{
    mgr->num_clients = 0;
    read_config(mgr);    
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

static Client* get_next_client(ClientManager* mgr)
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
            if (cumulative_price > random_num) {
                printf("cumulative_price: %d > %d -- MATCH!\n", cumulative_price, random_num);
                mgr->prev_client = current_client;
                next_client = current_client;
                break;
            } else {
                printf("cumulative_price: %d < %d\n", cumulative_price, random_num);
            }
        }
    }

    printf("next_client: %s\n", next_client->name);
    return next_client;
}

Billboard* get_next_billboard(ClientManager* mgr)
{
    Client* next_client = get_next_client(mgr);
    switch (next_client->display_option) {
        case 0: // one_random
            return &next_client->billboards[rand() % next_client->num_billboards];
            break;
        case 1: {// one_even_odd_min
            // time_t now = time(NULL);
            // struct tm* converted_time = localtime(&now);
            // printf("min_now: %d\n", converted_time->tm_min);
            int minutes = 0;
            return ((minutes % 2) == 0) ? &next_client->billboards[0] : &next_client->billboards[1];
            break;
        }
        default: //fallback to one_random
            return &next_client->billboards[rand() % next_client->num_billboards];
            break;
    }
}