#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H
#include "Event.h"
#include "config.h"

typedef struct queueNode {
    Event* events;
    Event head;
    Event tail;
} queueNode;

typedef struct queueNode* EventQueue;

queueNode* createEventQueue(int capacity);
// void queue_destroy(queueNode* q);
// int queue_isEmpty(const queueNode* q); 
// int queue_isFull(const queueNode* q);
// int queue_enqueue(queueNode* q, Event e); 
// int queue_dequeue(queueNode* q, Event* out);

#endif