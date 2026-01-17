#include <stdlib.h>
#include <stdio.h>
#include "EventQueue.h"

extern DebugLevel debugLevel;

EventQueue queueCreate() {
    if (debugLevel >= DEBUG) printf("Log created with NULL.\n");
    return NULL;
}

queueNode* createEventQueue(int capacity) {
    size_t size = sizeof(queueNode) * capacity;
    struct queueNode* newQueue =  malloc(size);
    if (newQueue == NULL) return NULL;
    if (debugLevel >= DEBUG) printf("Queue created with NULL.\n");
    return newQueue;
}    

void queueDestroy(EventQueue* queue) {
    // NOT IMPLEMENTED YET
}

int queueIsEmpty(EventQueue* queue) {
    // NOT IMPLEMENTED YET
}

int queueIsFull(EventQueue* queue) {
    // NOT IMPLEMENTED YET
}

int queueEnqueue(EventQueue* queue) {
    // NOT IMPLEMENTED YET
}

int queueDequeue(EventQueue* queue) {
    // NOT IMPLEMENTED YET
}