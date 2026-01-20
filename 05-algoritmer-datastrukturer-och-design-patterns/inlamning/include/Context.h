#ifndef CONTEXT_H
#define CONTEXT_H
#include "EventLog.h"
#include "EventQueue.h"

typedef struct {
    EventLog* log;
    EventQueue* queue;
    int* running;
} Context;

#endif