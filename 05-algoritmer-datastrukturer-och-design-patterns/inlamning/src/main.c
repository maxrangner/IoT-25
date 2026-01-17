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
    Event myEvent2;
    Event myEvent3;

    queueEnqueue(&eventQueue, myEvent);
    queueEnqueue(&eventQueue, myEvent2);
    queueEnqueue(&eventQueue, myEvent3);

    Event moveEvent;
    queueDequeue(&eventQueue, &moveEvent);

    // while (1) {
    //     menu();
    // }

    return 0;
}