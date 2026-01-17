#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H
#include "Event.h"
#include "config.h"



typedef struct queueNode {
    Event event;
    struct queueNode* nextQueueNode;
} queueNode;

typedef queueNode* EventQueue;

EventQueue queueCreate();
void queueDestroy(EventQueue* queue); // NOT IMPLEMENTED YET
int queueIsEmpty(EventQueue* queue); // NOT IMPLEMENTED YET
int queueIsFull(EventQueue* queue); // NOT IMPLEMENTED YET
int queueEnqueue(EventQueue* queue, Event event); // NOT IMPLEMENTED YET
int queueDequeue(EventQueue* queue, Event event); // NOT IMPLEMENTED YET

#endif