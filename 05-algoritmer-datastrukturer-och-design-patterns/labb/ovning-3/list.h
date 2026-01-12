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

//tar bort första förekomsten av 'd' från listan
//returnerar 1 ifall elementet fanns, annars 0
int removeElement(List* l, Data d);

//undersök om datat 'd' finns i listan
//returnerar 1 ifall det finns, annars 0
// O(n)
int isInList(List l, Data d);

//returnerar antal element i listan
int lengthOfList(List l);

//tömmer listan och frigör allt minne
void clearList(List* l);

//skriver ut alla element i listan till den angivna strömmen
void printList(List l, FILE* stream);

//returnerar värdet på första datat i listan
Data getFirstElement(List l);

//returnerar värdet på sista datat i listan
Data getLastElement(List l);

#endif
