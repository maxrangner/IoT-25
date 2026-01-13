#include <stdlib.h>
#include "EventLog.h"

static struct node* createListNode(Event event) {
	size_t size = sizeof(struct node);
	struct node* newNode = malloc(size);
	if (newNode == NULL) return NULL;
	newNode->event = event;
	newNode->nextNode = NULL;
	return newNode;
}

EventLog createLog(void) {
	return NULL;
}

int isEmpty(EventLog log) {
	if (log == NULL) return 1;
	return 0;
}

int addFirst(EventLog* log, Event event) {
	struct node* newNode = createListNode(event);
	if (newNode == NULL) return 0;
	if (*log == NULL) {
		*log = newNode;
	} else {
		struct node* tempNode = *log;
		*log = newNode;
		(*log)->nextNode = tempNode;
	}
	return 1;
}

int addLast(EventLog* log, Event event) {
	struct node* currentNode = *log;
	if (isEmpty(*log)) {
		*log = createListNode(event);
		return 1;
	}
	while(1) {
		if (currentNode->nextNode == NULL) {
			currentNode->nextNode = createListNode(event);
			if (currentNode->nextNode == NULL) return 0;
			break;
		} else {
			currentNode = currentNode->nextNode;
		}
	}
	return 1;
}