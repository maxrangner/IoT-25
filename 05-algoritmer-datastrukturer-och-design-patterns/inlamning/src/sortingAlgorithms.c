#include "sortingAlgorithms.h"

void bubbleSort(Event* returnArr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1; j++) {
            if (returnArr[j].value > returnArr[j + 1].value) {
                swap(&returnArr[j], &returnArr[j + 1]);
            }
        }
    }
}

void selectionSort(Event* returnArr, int size) {
    for (int i = 0; i < size - 1; i++) {
        int smallestIdx = i;
        for (int j = i; j < size; j++) {
            if (returnArr[j].value < returnArr[smallestIdx].value) {
                smallestIdx = j;
            }
        }
        swap(&returnArr[i], &returnArr[smallestIdx]);
    }
}

/********************************************************
************************ UTILS **************************
********************************************************/ 

void swap(Event* a, Event* b) {
    Event temp = *a;
    *a = *b;
    *b = temp;
}