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
int isLogEmpty(EventLog* log);
Event logGet(const EventLog* log, int index);
int logSize(const EventLog* log);
void logPrint(EventLog* log, FILE* stream);

#endif