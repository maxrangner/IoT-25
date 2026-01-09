#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "utils.h"

/********************************************************
************************ UTILS **************************
********************************************************/ 

bool isSorted(int* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) return false;
    }
    return true;
}

void printArr(int* arr, int size) {
    printf("{ ");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i != size - 1) printf(", ");
    }
    printf(" }\n\n");
}

void swap(int* a, int* b, struct Statistics* stats) {
    stats->swaps++;
    int aTemp = *a;
    *a = *b;
    *b = aTemp;
}

int assign(int* a, int x, struct Statistics* stats) {
    stats->assigns++;
    *a = x;
    return x;
}

/********************************************************
********************* NEW ARRAYS ************************
********************************************************/ 

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

int* createRand(int size, struct Statistics* stats) {
    srand(time(NULL));
    int* newArr = createSorted(size);
    for (int i = 0; i < size * 10; i++) {
        swap(&newArr[rand() % size], &newArr[rand() % size], stats);
    }
    return newArr; 
}

/********************************************************
************************ SORTING ************************
********************************************************/ 

void bubbleSort(int* arr, int size, struct Statistics* stats) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1; j++) {
            if (greaterThan(&arr[j], &arr[j] + 1, stats)) {
                swap(&arr[j], &arr[j + 1], stats);
            }
        }
    }
}

void selectionSort(int* arr, int size, struct Statistics* stats) {
    for (int i = 0; i < size - 1; i++) {
        int smallestIdx; 
        assign(&smallestIdx, i, stats);
        for (int j = i; j < size; j++) {
            if (lessThan(&arr[j], &arr[smallestIdx], stats)) {
                assign(&smallestIdx, j, stats);
            }
        }
        swap(&arr[i], &arr[smallestIdx], stats);
    }
}

void insertionSort(int* arr, int size, struct Statistics* stats) {
    for (int i = 1; i <= size; i++) {
        for (int j = i - 1; j > 0; j--) {
            if (greaterThan(&arr[j-1], &arr[j], stats)) {
                swap(&arr[j-1], &arr[j], stats);
            }
        }
        printArr(arr, size);
    }
}

int quickSub(int* arr, int size, struct Statistics* stats) {
    int pivot;
    assign(&pivot, arr[size - 1], stats);
    int limit;
    assign(&limit, 0, stats);

    for (int i = 0; i < size - 1; i++) {
        if (lessThan(&arr[i], &pivot, stats)) {
            swap(&arr[i], &arr[limit], stats);
            assign(&limit, limit + 1, stats);
        }
    }
    swap(&arr[limit], &arr[size - 1], stats);
    return limit;
}

void quickSort(int* arr, int size, struct Statistics* stats) {
    int exit = 1;
    if (lessThanOrEqualTo(&size, &exit, stats)) return;
    int returnSize;
    assign(&returnSize, quickSub(arr, size, stats), stats);
    quickSort(arr, returnSize, stats);
    quickSort(&arr[returnSize + 1], size - returnSize - 1, stats);
}
