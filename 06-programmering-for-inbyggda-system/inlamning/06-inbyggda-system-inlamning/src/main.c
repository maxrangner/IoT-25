#include <stdio.h>
#include "ClientManager.h"
#include <windows.h> // for prototyping


int main(void) {
    printf("Hello Billboards!\n");
    ClientManager mgr;
    client_manager_init(&mgr);

    while(1) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                printf("Client %d - Content %d\n", i, mgr.clients[i].billboards[j].billboard_content);
                Sleep(500);
            }
        }
    }
    printf("Bye!");
    return 0;
}
