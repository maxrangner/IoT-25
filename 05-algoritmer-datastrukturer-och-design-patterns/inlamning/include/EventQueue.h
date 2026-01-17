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

void queueInit(EventQueue* queue);
void queueReset(EventQueue* queue);
int queueIsEmpty(EventQueue* queue);
int queueIsFull(EventQueue* queue);
int queueEnqueue(EventQueue* queue, Event event);
int queueDequeue(EventQueue* queue, Event* event);

#endif