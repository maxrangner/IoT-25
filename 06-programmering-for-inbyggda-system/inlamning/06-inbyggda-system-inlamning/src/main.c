#pragma message("Compiling as UTF-8 test")

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ClientManager.h"
#include <windows.h> // for prototyping


int main(void) {
    SetConsoleOutputCP(CP_UTF8);
    printf("Hello Billboards!\n");
    srand(time(NULL));
    ClientManager mgr;
    client_manager_init(&mgr);
    Client* next_client;

    while(1) {
        next_client = get_next_billboard(&mgr);
        printf("%s\n", next_client->name);
        Sleep(2000);
    }
    printf("Bye!");
    return 0;
}
