#ifndef LIST_H
#define LIST_H

#include <assert.h>
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

/*
    // ---- Traversering (iteration) ----

    // Anropar f(x) för varje element x i listan.
    void forEach(void (*f)(Data)) const;

      forEachCtx: "Ctx" = Context (kontext).

      Callbacks i C/C++ (utan lambdas med capture) kan inte automatiskt "komma åt"
      lokala variabler utanför funktionen. Därför skickar vi med en extra så kallad
      "kontext"-pekare (void* ctx) som callbacken kan använda för att nå extra data.

      Vad är en callback? En funktion som skickas som argument till en annan funktion.

      Exempel:
        struct MyCtx { int sum; };
        
        void add_to_sum(Data x, void* ctx) {
            MyCtx* c = (MyCtx*)ctx;
            c->sum += x;
        }

        MyCtx c{0};
        list.forEachCtx(add_to_sum, &c);
        // c.sum innehåller nu summan av elementen.
        void forEachCtx(void (*f)(Data, void*), void* ctx) const;
*/

#endif
