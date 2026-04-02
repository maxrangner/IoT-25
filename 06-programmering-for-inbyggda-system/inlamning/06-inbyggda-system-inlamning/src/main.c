#include <stdlib.h>
#include "client_manager.h"
#include "display.h"
#include "millis.h"
#include "utils.h"

int main(void) {
    ClientManager mgr;
    uint16_t random_seed;
    uint32_t now = 0;
    uint32_t prev_update = now - MAIN_UPDATE_INTERVAL;
    Billboard* next_billboard = NULL;
    
    millis_init();
    random_seed = get_random_seed();
    srand(random_seed);
    client_manager_init(&mgr);
    display_init();

    while(1) {
        now = millis();
        if ((now - prev_update) >= MAIN_UPDATE_INTERVAL) {
            next_billboard = get_next_billboard(&mgr, now);
            prev_update = now;
        }
        display_billboard(next_billboard, now);
    }
    return 0;
}
