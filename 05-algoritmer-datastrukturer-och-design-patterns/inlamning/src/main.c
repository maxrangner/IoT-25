#include <stdio.h>
#include "config.h"
#include "Event.h"
#include "EventLog.h"
#include "EventQueue.h"

DebugLevel debugLevel = DEBUG;

int main() {
    Event myEvent;
    EventQueue myQueue = createEventQueue;
    EventLog myLog = createLog();
    if (debugLevel >= DEBUG) printf("myLog is empty: %d\n", isLogEmpty(myLog));
    addLogNodeBack(&myLog, myEvent);
    addLogNodeBack(&myLog, myEvent);
    if (debugLevel >= DEBUG) printf("myLog is empty: %d\n", isLogEmpty(myLog));


    return 0;
}