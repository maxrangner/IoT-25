#include <stdlib.h>
#include "menu.h"
#include "Set.h"
#include "utils.h"

int main() {
    int isRunning = 1;
    srand(time(NULL)); // Sets random seed for generating random Events

    EventLog eventLog = createLog();
    EventQueue eventQueue;
    queueInit(&eventQueue);
    Set set;
    setInitialize(&set);
    
    Context ctx = {
        .log = &eventLog,
        .queue = &eventQueue,
        .set = &set,
        .running = &isRunning,
    };

    while (isRunning) {
        menu(&ctx);
    }

    return 0;
}
