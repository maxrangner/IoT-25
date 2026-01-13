#ifndef EVENTLOG_H
#define EVENTLOG_H
#include "Event.h"
#include "config.h"

struct logNode {
    Event event;
    int logSize;
    struct logNode* nextNode;
};

typedef struct logNode* EventLog;

// Log functions
EventLog createLog();
int addLogNodeFront(EventLog* log, Event event);
int addLogNodeBack(EventLog* log, Event event);

// Log helper functions
int isLogEmpty(EventLog log);

#endif