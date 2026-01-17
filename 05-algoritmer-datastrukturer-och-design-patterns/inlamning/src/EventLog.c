#include <stdlib.h>
#include <stdio.h>
#include "EventLog.h"

extern DebugLevel debugLevel;

// Log functions
EventLog createLog() {
	if (debugLevel >= DEBUG) printf("Log created with NULL.\n");
	return NULL;
}

static struct logNode* createLogNode(Event event) {
	size_t size = sizeof(struct logNode);
	struct logNode* newNode = malloc(size);
	if (newNode == NULL) return NULL;
	newNode->event = event;
	newNode->nextNode = NULL;
	return newNode;
}

int logAppend(EventLog* log, Event event) {
	if (debugLevel >= DEBUG) printf("logAppend()\n");
	struct logNode* currentNode = *log;
	if (isLogEmpty(*log)) {
        *log = createLogNode(event);
        if (debugLevel >= DEBUG) printf("Node created in empty log.\n");
		return 1;
	}
	while(1) {
		if (currentNode->nextNode == NULL) {
			currentNode->nextNode = createLogNode(event);
            if (debugLevel >= DEBUG) printf("Node created.\n");
			if (currentNode->nextNode == NULL) return 0;
			break;
		} else {
			if (debugLevel >= DEBUG) printf("Node moved.\n");
			currentNode = currentNode->nextNode;
		}
	}
	return 1;
}

void logDestroy(EventLog* log) {
	// NOT IMPLEMENTED YET
}

Event logGet(const EventLog* log, int index) {
	// NOT IMPLEMENTED YET
}

// Log helper functions
int isLogEmpty(EventLog log) {
	if (log == NULL) return 1;
	return 0;
}

int logSize(EventLog* log) {
	// NOT IMPLEMENTED YET
}