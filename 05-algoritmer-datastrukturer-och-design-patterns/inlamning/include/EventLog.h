#ifndef EVENTLOG_H
#define EVENTLOG_H

#include <stdio.h>
#include "Event.h"
#include "config.h"

struct logNode {
    Event event;
    struct logNode* nextNode;
};

typedef struct logNode* EventLog;

EventLog createLog();
static struct logNode* createLogNode(Event event);
int logAppend(EventLog* log, Event event);
void logDestroy(EventLog* log);
Event logGet(const EventLog* log, int index);  // NOT IMPLEMENTED YET
int isLogEmpty(EventLog* log);
int logSize(const EventLog* log); // NOT IMPLEMENTED YET
void logPrint(EventLog* log, FILE* stream);

#endif