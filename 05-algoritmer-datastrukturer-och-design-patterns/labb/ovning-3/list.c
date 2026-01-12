#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "list.h"

static struct node* createListNode(Data d) {
	int size = sizeof(struct node);
	struct node* newNode = malloc(size);
	if (newNode == NULL) return NULL;
	newNode->d = d;
	newNode->rest = NULL;
	return newNode;
}

List createEmptyList(void) {
	return NULL;
}

int isEmpty(List l) {
	if (l == NULL) return 1;
	return 0;
}

int addFirst(List* l, Data d) {
	struct node* newNode = createListNode(d);
	if (newNode == NULL) return 0;
	if (*l == NULL) {
		*l = newNode;
	} else {
		struct node* tempNode = *l;
		*l = newNode;
		(*l)->rest = tempNode;
	}
	return 1;
}

int addLast(List* l, Data d) {
	struct node* currentNode = *l;
	if (isEmpty(*l)) {
		*l = createListNode(d);
		return 1;
	}
	while(1) {
		if (currentNode->rest == NULL) {
			currentNode->rest = createListNode(d);
			if (currentNode->rest == NULL) return 0;
			break;
		} else {
			currentNode = currentNode->rest;
		}
	}
	return 1;
}

void removeFirst(List* l) {
	assert(!isEmpty(*l));
	struct node* toDestroy = *l;
	*l = (*l)->rest;
	free(toDestroy);
}

void removeLast(List* l) {
	assert(!isEmpty(*l));
	if (isEmpty(*l)) return;
	
	struct node* temp = *l;
	if (temp->rest == NULL) {
		*l = NULL;
		return;
	}
	while(temp->rest->rest != NULL) {
			temp = temp->rest;
	}
	struct node* toDestroy = temp->rest;
	temp->rest = NULL;
	free(toDestroy);
}

int removeElement(List* l, Data d) {
	assert(!isEmpty(*l));
	if (isEmpty(*l)) return 0;

	struct node* temp = *l;
	struct node* toDestroy = temp;
	if (temp->d == d) {
		*l = (*l)->rest;
		free(toDestroy);
		return 1;
	}
	while(temp->rest != NULL && temp->rest->d != d) {
		temp = temp->rest;
	}
	if (temp->rest == NULL) return 0;
	toDestroy = temp->rest;
	temp->rest = temp->rest->rest;
	free(toDestroy);
	return 1;
}

int isInList(List l, Data d) {
	struct node* currentElement = l;
	while(currentElement != NULL) {
		if (currentElement->d == d) return 1;
		currentElement = currentElement->rest;
	}
	return 0;
}

int lengthOfList(List l) {
	struct node* currentElement = l;
	int idx = 0;
	if (currentElement == NULL) return idx;
	idx++;
	while(currentElement->rest != NULL) {
		currentElement = currentElement->rest;
		idx++;
	}
	return idx;
}

void clearList(List* l) {
	while((*l) != NULL) {
		removeFirst(l);
	}
	assert(isEmpty(*l));
}

void printList(List l, FILE* stream) {
	if (l == NULL) {

		return;
	}
	List currentNode = l;
	printf("[");
	while(1) {
		printf("%d", (currentNode)->d);
		if ((currentNode)->rest == NULL) break;
		printf(", ");
		(currentNode) = (currentNode)->rest;
	}
	printf("]");
}

Data getFirstElement(List l) {
	assert(!isEmpty(l));
	return l->d;
}

Data getLastElement(List l) {
	assert(!isEmpty(l));
		
	struct node* temp = l;
	while(temp->rest != NULL) {
			temp = temp->rest;
	}
	return temp->d;
}
