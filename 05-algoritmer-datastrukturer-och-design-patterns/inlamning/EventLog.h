#ifndef EVENTLOG_H
#define EVENTLOG_H
#include "Event.h"

struct node {
    Event event;
    int logSize;
    struct node* nextNode;
};

typedef struct node* EventLog;

EventLog createLog(void);
int isEmpty(EventLog log);
int addFirst(EventLog* log, Event event);
int addLast(EventLog* log, Event event);

#endif