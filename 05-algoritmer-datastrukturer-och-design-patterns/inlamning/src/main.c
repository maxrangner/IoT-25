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

DebugLevel debugLevel = DEBUG; // Set to NONE, INFO, ERROR or DEBUG

int main() {
    int isRunning = 1;
    srand(time(NULL)); // Set random seed for generating random Events

    EventLog eventLog = createLog();
    EventQueue eventQueue;
    Set set;
    queueInit(&eventQueue);
    setInitialize(&set);

    Context ctx = {
        .log = &eventLog,
        .queue = &eventQueue,
        .set = &set,
        .running = &isRunning,
        .timeTicks = 0 // Simulates time that increments every tick
    };

    while (isRunning) {
        menu(&ctx);
    }

    return 0;
}
