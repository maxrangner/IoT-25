#ifndef SORTINGALORITHMS_H
#define SORTINGALORITHMS_H
#include "Event.h"

typedef void (*sortFunction)(Event*, int);
void bubbleSort(Event*, int);
void selectionSort(Event*, int);
void swap(Event* a, Event* b);

#endif