#include <stdio.h>
#include "Event.h"
#include "EventLog.h"

int main() {
    EventLog myLog = createLog();
    Event myEvent;
    
    addLast(&myLog, myEvent);
    printf("myLog is empty: %d\n", isEmpty(myLog));

    return 0;
}