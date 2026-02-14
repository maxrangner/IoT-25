#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ClientManager.h"
#include "display.h"
#include <windows.h> // Using Sleep() for prototyping. 


int main(void) {
    SetConsoleOutputCP(CP_UTF8);
    printf("Hello Billboards!\n");
    srand(time(NULL));
    ClientManager mgr;
    client_manager_init(&mgr);
    Client* next_client;

    while(1) {
        next_client = get_next_client(&mgr);
        get_next_billboard(next_client);
        Sleep(2000);
    }
    printf("Bye!");
    return 0;
}
