#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "config.h"
#include "Event.h"
#include "EventLog.h"
#include "EventQueue.h"
#include "systemFunctions.h"
// debug
#include <windows.h> // delete with Sleep() in main()

DebugLevel debugLevel = DEBUG;
int running = 1;

int main() {
    srand(time(NULL));
    EventQueue eventQueue;
    queueInit(&eventQueue);
    EventLog eventLog = createLog();

    while (running) {
        // menu();
        tick(&eventQueue, &eventLog, 2);
        logPrint(&eventLog, stdout);
        Sleep(5000);
    }

    return 0;
}