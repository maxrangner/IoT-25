#ifndef LIST_H
#define LIST_H

#include <stdio.h>

typedef int Data;

struct node {
	Data d;
	struct node* rest;
};

typedef struct node* List;

List createEmptyList(void);
int isEmpty(List l);
int addFirst(List* l, Data d);
int addLast(List* l, Data d);
void removeFirst(List* l);
void removeLast(List* l);
int removeElement(List* l, Data d);
int isInList(List l, Data d);
int lengthOfList(List l);
void clearList(List* l);
void printList(List l, FILE* stream);
Data getFirstElement(List l);
Data getLastElement(List l);

#endif
