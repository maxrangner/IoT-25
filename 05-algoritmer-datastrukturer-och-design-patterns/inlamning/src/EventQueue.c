#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "EventQueue.h"

/********************************************************
******************* QUEUE INTERFACE *********************
********************************************************/ 

void queueInit(EventQueue* queue) {
    assert(queue != NULL);
    queue->head = 0;
    queue->tail = 0;
    queue->size = 0;
}    

void queueReset(EventQueue* queue) {
    assert(queue != NULL);
    queue->head = 0;
    queue->tail = 0;
    queue->size = 0;
}

int queueEnqueue(EventQueue* queue, Event event) {
    assert(queue != NULL);
    if (queueIsFull(queue)) return 0;
    queue->events[queue->head++] = event; // Add event to queue. Head take one step forward.
    queue->head = queue->head % QUEUE_CAPACITY; // Wrap around if reached array end.
    queue->size++;
    return 1;
}

int queueDequeue(EventQueue* queue, Event* event) {
    assert(queue != NULL);
    assert(event != NULL);
    if (queueIsEmpty(queue)) return 0;
    *event = queue->events[queue->tail++]; // Extract event from queue. Trail take one step forward.
    queue->tail = queue->tail % QUEUE_CAPACITY;
    queue->size--;
    return 1;
}

/********************************************************
**************** QUEUE HELPER INTERFACE *****************
********************************************************/ 

int queueIsEmpty(EventQueue* queue) {
    return queue->size == 0;
}

int queueIsFull(EventQueue* queue) {
    return queue->size >= QUEUE_CAPACITY;
}

int queueSize(EventQueue* queue) {
    return queue->size;
}

int queuePeek(EventQueue* queue, Event* event) {
    assert(queue != NULL);
    assert(event != NULL);
    if (queueIsEmpty(queue)) return 0;
    *event = queue->events[queue->tail];
    return 1;
}
