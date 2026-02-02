#include <stdlib.h>
#include <assert.h>
#include "EventLog.h"

/********************************************************
******************** LOG INTERFACE **********************
********************************************************/

EventLog createLog() {
	// Create log. Assign NULL to head pointer, meaning the log currently has no data
	return NULL;
}

static struct logNode* createLogNode(Event event) {
	size_t size = sizeof(struct logNode);
	struct logNode* newNode = malloc(size); // Allocate memopry on heap for a new node
	if (newNode == NULL) return NULL; // Return NULL pointer if malloc() fails
	newNode->event = event;
	newNode->nextNode = NULL; // Child set to NULL, meaning current node is the last one
	return newNode;
}

void logAppend(EventLog* log, Event event) {
	assert(log != NULL);
	if (isLogEmpty(log)) { // If log is empty, create first node.
		*log = createLogNode(event);
		return;
	}
	struct logNode* currentNode = *log;
	while(1) {
		if (currentNode->nextNode == NULL) { // Check if we are at the last node
			currentNode->nextNode = createLogNode(event); // Append new event to end of log
			break;
		} else {
			currentNode = currentNode->nextNode;
		}
	}
}

void logDestroy(EventLog* log) {
	assert(log != NULL);
	if (isLogEmpty(log) == 1) return;

	struct logNode* currentNode = *log;
	struct logNode* nextNode;

	while(currentNode != NULL) {
		if (currentNode->nextNode != NULL) {
			nextNode = currentNode->nextNode;
			free(currentNode);
			currentNode = nextNode;
		} else {
			free(currentNode);
			currentNode = NULL;
		}
	}
	*log = NULL;
}

bool isLogEmpty(EventLog* log) {
	if (*log == NULL) return true;
	return false;
}

Event logGet(const EventLog* log, int index) {
	assert(log != NULL);
	assert(index >= 0);
	assert(index < logSize(log));
	struct logNode* currentNode = *log;
	for (int i = 0; i < index; i++) {
		currentNode = currentNode->nextNode;
	}
	return currentNode->event;
}

int logSize(const EventLog* log) {
	int size = 0;
	EventLog currentNode = *log;
	while (currentNode != NULL) {
		size++;
		currentNode = currentNode->nextNode;
	}
	return size;
}

