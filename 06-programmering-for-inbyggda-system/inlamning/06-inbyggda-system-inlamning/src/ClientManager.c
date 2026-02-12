#include "ClientManager.h"

void client_manager_init(ClientManager* mgr) {
    Client newClient1 = {
        .price = 100,
        .billboards = {
            {.billboard_content = 10, .billboard_effect = fixed},
            {.billboard_content = 11, .billboard_effect = fixed},
            {.billboard_content = 12, .billboard_effect = fixed}
        }
    };
    Client newClient2 = {
        .price = 100,
        .billboards = {
            {.billboard_content = 20, .billboard_effect = fixed},
            {.billboard_content = 21, .billboard_effect = fixed},
            {.billboard_content = 22, .billboard_effect = fixed}
        }
    };
    Client newClient3 = {
        .price = 200,
        .billboards = {
            {.billboard_content = 30, .billboard_effect = fixed},
            {.billboard_content = 31, .billboard_effect = fixed},
            {.billboard_content = 32, .billboard_effect = fixed}
        }
    };

    Client clients[] = {newClient1, newClient2, newClient3};

    for (int i = 0; i < 3; i++) {
        mgr->clients[i] = clients[i];
    }
}