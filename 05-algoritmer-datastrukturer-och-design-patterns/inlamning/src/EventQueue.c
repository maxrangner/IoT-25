#include <stdlib.h>
#include <stdio.h>
#include "EventQueue.h"

extern DebugLevel debugLevel;

void queueInit(EventQueue* queue) {
    if (debugLevel >= DEBUG) printf("Queue initialized with 0s.\n");
    queue->head = 0;
    queue->tail = 0;
    queue->size = 0;
}    

void queueReset(EventQueue* queue) {
    if (debugLevel >= DEBUG) printf("Queue reset with 0s.\n");
    queue->head = 0;
    queue->tail = 0;
    queue->size = 0;
}

int queueIsEmpty(EventQueue* queue) {
    // if (debugLevel >= DEBUG) printf("Queue is empty: %d\n", queue->size == 0);
    return queue->size == 0;
}

int queueIsFull(EventQueue* queue) {
    // if (debugLevel >= DEBUG) printf("Queue is full: %d\n", queue->size >= QUEUE_CAPACITY);
    return queue->size >= QUEUE_CAPACITY;
}

int queueEnqueue(EventQueue* queue, Event event) {
    if (queueIsFull(queue)) return 0;
    queue->events[queue->head++] = event;
    queue->head = queue->head % QUEUE_CAPACITY;
    queue->size++;
    if (debugLevel >= DEBUG) printf("Event added to queue. QueueSize: %d\n", queue->size);
    return 1;
}

int queueDequeue(EventQueue* queue, Event* event) {
    if (queueIsEmpty(queue)) return 0;
    *event = queue->events[queue->tail++];
    queue->tail = queue->tail % QUEUE_CAPACITY;
    queue->size--;
    if (debugLevel >= DEBUG) printf("Event removed from queue. QueueSize: %d\n", queue->size);
    return 1;
}