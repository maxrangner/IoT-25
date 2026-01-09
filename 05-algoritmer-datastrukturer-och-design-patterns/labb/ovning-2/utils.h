#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include "statistics.h"
#include "utils.h"

bool isSorted(int* arr, int size);
void printArr(int* arr, int size);
void swap(int* a, int* b, struct Statistics* stats);
int assign(int* a, int x, struct Statistics* stats);
int* createSorted(int size);
int* createBackSorted(int size);
int* createRand(int size, struct Statistics* stats); 
void bubbleSort(int* arr, int size, struct Statistics* stats);
void selectionSort(int* arr, int size, struct Statistics* stats);
void insertionSort(int* arr, int size, struct Statistics* stats);
int quickSub(int* arr, int size, struct Statistics* stats);
void quickSort(int* arr, int size, struct Statistics* stats);

#endif