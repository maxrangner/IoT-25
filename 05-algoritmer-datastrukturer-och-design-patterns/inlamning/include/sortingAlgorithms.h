#ifndef SORTINGALORITHMS_H
#define SORTINGALORITHMS_H
#include "Event.h"

void bubbleSort(Event* returnArr, int size);
typedef void (*sortFunction)(Event* returnArr, int size);
extern sortFunction sortBubble;

#endif