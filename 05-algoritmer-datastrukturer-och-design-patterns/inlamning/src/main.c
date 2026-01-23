#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "config.h"
#include "Event.h"
#include "EventLog.h"
#include "EventQueue.h"
#include "Set.h"
#include "utils.h"
#include "menu.h"
#include "Context.h"

DebugLevel debugLevel = DEBUG;

int main() {
    int isRunning = 1;
    srand(time(NULL));

    EventLog eventLog = createLog();
    EventQueue eventQueue;
    Set set;
    queueInit(&eventQueue);
    setInitialize(&set);

    Context ctx = {
        .log = &eventLog,
        .queue = &eventQueue,
        .set = &set,
        .running = &isRunning
    };

    while (isRunning) {
        menu(&ctx);
    }

    return 0;
}
