#include <stdlib.h>
#include <stdio.h>
#include "EventLog.h"

extern DebugLevel debugLevel;

EventLog createLog() {
	// Log created. Set to NULL, meaning the log currently has no data
	if (debugLevel >= DEBUG) printf("Log created.\n");
	return NULL;
}

static struct logNode* createLogNode(Event event) {
	size_t size = sizeof(struct logNode);
	struct logNode* newNode = malloc(size); // Allocate memopry on heap for a new node
	if (newNode == NULL) return NULL; // Return NULL pointer if malloc() fails
	newNode->event = event;
	newNode->nextNode = NULL;
	if (debugLevel >= DEBUG) printf("New log node created.\n");
	return newNode;
}

int logAppend(EventLog* log, Event event) {
	if (isLogEmpty(log)) { // If log is empty, create first node.
		*log = createLogNode(event);
		return 1;
	}
	struct logNode* currentNode = *log;
	while(1) {
		if (currentNode->nextNode == NULL) { // Check if we are at the last node
			currentNode->nextNode = createLogNode(event); // Append new event to end of log
			if (currentNode->nextNode == NULL) return 0; // Pass along error from createLogNode()
			break;
		} else {
			currentNode = currentNode->nextNode;
		}
	}
	if (debugLevel >= DEBUG) printf("log appended.\n");
	return 1;
}

void logDestroy(EventLog* log) {
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

Event logGet(const EventLog* log, int index) {
	// NOT IMPLEMENTED YET
}

int isLogEmpty(EventLog* log) {
	if (debugLevel >= DEBUG) printf("isLogEmpty: %d\n", *log == NULL);
	if (*log == NULL) return 1;
	return 0;
}

int logSize(EventLog* log) {
	// NOT IMPLEMENTED YET
}