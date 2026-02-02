#ifndef CONTEXT_H
#define CONTEXT_H
#include "EventLog.h"
#include "EventQueue.h"

typedef struct Set Set;

struct Context {
    EventLog* log;
    EventQueue* queue;
    Set* set;
    int* running;
};
typedef struct Context Context;

#endif