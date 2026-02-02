#include "sortingAlgorithms.h"
#include "stdio.h"
#include <string.h>

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

sortFunction selectSort(char* arg) {
    if (strcmp(arg, "bubble") == 0) {
        return bubbleSort;
    } else if (strcmp(arg, "selection") == 0) {
        return selectionSort;
    } else {
        printf("Invalid sorting algorithm. Using Bubble Sort by default.\n");
        return bubbleSort;
    }
}

void swap(Event* a, Event* b) {
    Event temp = *a;
    *a = *b;
    *b = temp;
}