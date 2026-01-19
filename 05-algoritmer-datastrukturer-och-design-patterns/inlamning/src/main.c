#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "config.h"
#include "Event.h"
#include "EventLog.h"
#include "EventQueue.h"
#include "systemFunctions.h"
#include "menu.h"

DebugLevel debugLevel = NONE;
int running = 1;

int main() {
    srand(time(NULL));
    EventQueue eventQueue;
    queueInit(&eventQueue);
    EventLog eventLog = createLog();

    while (running) {
        menu();
        // tick(&eventQueue, &eventLog, 2);
        // logPrint(&eventLog, stdout);
    }

    return 0;
}