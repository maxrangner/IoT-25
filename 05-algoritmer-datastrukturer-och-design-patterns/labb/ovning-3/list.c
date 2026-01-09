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
	if ((*l) == NULL) {
		*l = newNode;
	} else {
		struct node* tempNode = *l;
		(*l) = newNode;
		(*l)->rest = tempNode;
	}
	return 1;
}

int addLast(List* l, Data d) {
	int idx = 0;
	struct node* lastNode = *l;
	if (lastNode == NULL) return 0;
	while(1) {
		if (lastNode->rest == NULL) {
			lastNode->rest = createListNode(d);
			if (lastNode->rest == NULL) return 0;
			break;
		} else {
			lastNode = lastNode->rest;
		}
	}
	return 1;
}

void removeFirst(List* l) {
	assert(!isEmpty(*l));
	*l = (*l)->rest;

}

void removeLast(List* l) {
	// Tänk på att du måste hantera fallet där listan bara har ett element.
	//precondition: listan är inte tom (testa med assert)
}

int removeElement(List* l, Data d) {
	// Se till att ta bort första noden korrekt. Behöver ha koll på föregående nod när du itererar.
	return 0; //endast här för kompilering
}

int isInList(List l, Data d) {
	return 0; //endast här för kompilering
}

int lengthOfList(List l) {
	return 0; //endast här för kompilering
}

void clearList(List* l) {
	// Enklast och säkrast att köra removeFirst i en loop tills listan är tom.
	//postcondition: listan är tom (testa med assert)
}

void printList(List l, FILE* stream) {
	// Tom lista ska skriva ut: []
	// Icke-tom lista ska skriva ut: [data1, data2, data3]
}

Data getFirstElement(List l) {
	//precondition: listan är inte tom (testa med assert)
	return 0; //endast här för kompilering
}

Data getLastElement(List l) {
	//precondition: listan är inte tom (testa med assert)
	return 0; //endast här för kompilering
}
