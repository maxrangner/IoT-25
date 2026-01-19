#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "config.h"
#include "Event.h"
#include "EventLog.h"
#include "EventQueue.h"
#include "systemFunctions.h"
#include "menu.h"
#include "Context.h"

DebugLevel debugLevel = NONE;
int running = 1;

int main() {
    srand(time(NULL));
    EventQueue eventQueue;
    queueInit(&eventQueue);
    EventLog eventLog = createLog();
    Context ctx = {
        .log = &eventLog,
        .queue = &eventQueue
    };

    while (running) {
        menu(&ctx);
        // tick(&eventQueue, &eventLog, 2);
        // logPrint(&eventLog, stdout);
    }

    return 0;
}