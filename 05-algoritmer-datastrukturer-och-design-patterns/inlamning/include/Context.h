#ifndef CONTEXT_H
#define CONTEXT_H
#include "EventLog.h"
#include "EventQueue.h"
#include "Set.h"

typedef struct {
    EventLog* log;
    EventQueue* queue;
    Set* set;
    int* running;
} Context;

#endif