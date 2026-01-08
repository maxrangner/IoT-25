#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "time.h"

bool isSorted(int* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) return false;
    }
    return true;
}

void printArr(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d: %d\n", i, arr[i]);
    }
}

void swap(int* a, int* b) {
    int aTemp = *a;
    *a = *b;
    *b = aTemp;
}

int* createSorted(int size) {
    size_t newArrSize = size * sizeof(int);
    int* newArr = (int*)malloc(newArrSize);
    for (int i = 0; i < size; i++) {
        newArr[i] = i;
    }
    return newArr;
}

int* createBackSorted(int size) {
    size_t newArrSize = size * sizeof(int);
    int* newArr = (int*)malloc(newArrSize);
    for (int i = 0; i < size; i++) {
        newArr[i] = size - i - 1;
    }
    return newArr;
}

int* createRand(int size) {
    srand(time(NULL));
    int* newArr = createSorted(size);
    for (int i = 0; i < size * 10; i++) {
        swap(&newArr[rand() % size], &newArr[rand() % size]);
    }

    return newArr; 
}

void bubbleSort(int* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1; j++) {
            if (arr[j] > arr[j + 1]) swap(&arr[j], &arr[j + 1]);
        }
    }
}