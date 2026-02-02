#ifndef EVENTLOG_H
#define EVENTLOG_H

#include <stdio.h>
#include <stdbool.h>
#include "Event.h"
#include "config.h"

struct logNode {
    Event event;
    struct logNode* nextNode;
};

typedef struct logNode* EventLog;

// Log interface
EventLog createLog();
void logAppend(EventLog* log, Event event);
void logDestroy(EventLog* log);
Event logGet(const EventLog* log, int index);
bool isLogEmpty(EventLog* log);
int logSize(const EventLog* log);

#endif