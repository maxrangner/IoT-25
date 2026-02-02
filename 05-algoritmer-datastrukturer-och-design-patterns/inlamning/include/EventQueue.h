#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H
#include "Event.h"
#include "config.h"

typedef struct EventQueue {
    Event events[QUEUE_CAPACITY];
    int head;
    int tail;
    int size;
} EventQueue;

// Queue interface
void queueInit(EventQueue* queue);
void queueReset(EventQueue* queue);
int queueEnqueue(EventQueue* queue, Event event);
int queueDequeue(EventQueue* queue, Event* event);
// Queue helper interface
int queueIsEmpty(EventQueue* queue);
int queueIsFull(EventQueue* queue);
int queueSize(EventQueue* queue);
int queuePeek(EventQueue* queue, Event* event);

#endif