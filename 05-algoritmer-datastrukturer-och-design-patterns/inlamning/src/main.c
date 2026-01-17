#include <stdio.h>
#include "config.h"
#include "Event.h"
#include "EventLog.h"
#include "EventQueue.h"

DebugLevel debugLevel = DEBUG;

int main() {
    Event myEvent;
    EventQueue myQueue = queueCreate;
    EventLog myLog = createLog();
    if (debugLevel >= DEBUG) printf("myLog is empty: %d\n", isLogEmpty(myLog));
    logAppend(&myLog, myEvent);
    logAppend(&myLog, myEvent);
    if (debugLevel >= DEBUG) printf("myLog is empty: %d\n", isLogEmpty(myLog));


    return 0;
}