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

EventLog createLog();
static struct logNode* createLogNode(Event event);
int logAppend(EventLog* log, Event event);
void logDestroy(EventLog* log); // NOT IMPLEMENTED YET
Event logGet(const EventLog* log, int index);  // NOT IMPLEMENTED YET
int isLogEmpty(EventLog log);
int logSize(EventLog* log); // NOT IMPLEMENTED YET

#endif