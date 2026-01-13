#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H
#include "Event.h"
#include "config.h"

typedef struct queueNode {
    Event event;
    struct queueNode* nextQueueNode;
} queueNode;

typedef queueNode* eventQueue;

eventQueue createEventQueue();

#endif