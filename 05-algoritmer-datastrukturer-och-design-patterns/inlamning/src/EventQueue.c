#include <stdio.h>
#include "EventQueue.h"

extern DebugLevel debugLevel;

eventQueue createEventQueue() {
    if (debugLevel >= DEBUG) printf("Log created with NULL.\n");
    return NULL;
}