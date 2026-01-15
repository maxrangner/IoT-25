#include <stdlib.h>
#include <stdio.h>
#include "EventQueue.h"

extern DebugLevel debugLevel;

queueNode* createEventQueue(int capacity) {
    size_t size = sizeof(queueNode) * capacity;
    struct queueNode* newQueue =  malloc(size);
    if (newQueue == NULL) return NULL;
    if (debugLevel >= DEBUG) printf("Queue created with NULL.\n");
    return newQueue;
}