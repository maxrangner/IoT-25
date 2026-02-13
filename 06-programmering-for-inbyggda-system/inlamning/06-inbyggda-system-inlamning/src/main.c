#include <stdio.h>
#include "ClientManager.h"
#include <windows.h> // for prototyping


int main(void) {
    printf("Hello Billboards!\n");
    ClientManager mgr;
    client_manager_init(&mgr);

    while(1) {
        get_next_billboard(&mgr);
        Sleep(5000);
    }
    printf("Bye!");
    return 0;
}
