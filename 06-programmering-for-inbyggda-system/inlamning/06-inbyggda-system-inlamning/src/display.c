#include "display.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Billboard* get_next_billboard(Client* next_client)
{
    Billboard* return_billboard = &next_client->billboards[0];

    switch (next_client->display_option) {
        case 0: // one_random
            return_billboard = &next_client->billboards[rand() % next_client->num_billboards];
            break;
        case 1: // one_even_odd_min
            time_t now = time(NULL);
            struct tm* converted_time = localtime(&now);
            printf("min_now: %d\n", converted_time->tm_min);
            if ((converted_time->tm_min % 2) == 0) {
                return_billboard = &next_client->billboards[0];
            } else {
                return_billboard = &next_client->billboards[1];
            }
            break;
        default: //all, and fallback
            return_billboard = &next_client->billboards[0];
            break;
    }
    printf("next_client: %s     Returned billboard: %s\n\n", next_client->name, return_billboard->billboard_text);
    return return_billboard;
}