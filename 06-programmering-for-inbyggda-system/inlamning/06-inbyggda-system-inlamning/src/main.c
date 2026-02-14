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
    Billboard* next_billboard;

    while(1) {
        next_billboard = get_next_billboard(&mgr);
        printf("Returned billboard: %s\n\n", next_billboard->billboard_text);
        Sleep(2000);
    }
    printf("Bye!");
    return 0;
}
