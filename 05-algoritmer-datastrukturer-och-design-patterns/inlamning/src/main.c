#include <stdio.h>
#include "config.h"
#include "Event.h"
#include "EventLog.h"
#include "EventQueue.h"
#include "systemFunctions.h"

DebugLevel debugLevel = DEBUG;

int main() {
    EventQueue eventQueue;
    queueInit(&eventQueue);
    Event myEvent;
 
    // Fill queue
    for (int i = 0; i < 15; i++) {
        if (queueEnqueue(&eventQueue, myEvent)) {
            printf("Event enqueued.\n");
        } else printf("Queue full.\n");
    }

    Event moveEvent;
    EventLog myLog = createLog();
    logDestroy(&myLog);

    // Empty queue
    for (int i = 0; i < 15; i++) {
        if (queueDequeue(&eventQueue, &moveEvent)) {
            logAppend(&myLog, moveEvent);
        } else printf("Queue empty.\n");
    }

    logDestroy(&myLog);
    isLogEmpty(&myLog);

    // while (1) {
    //     menu();
    // }

    return 0;
}