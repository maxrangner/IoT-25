#include <stdio.h>
#include "utils.c"

const int arrSize = 5;
int myArr[arrSize] = {1, 2, 3, 4, 5};

int main() {
    // bool result;
    // result = isSorted(myArr, arrSize);
    // printf("Result is sorted: %d\n", result);
    // printArr(myArr, arrSize);

    // int a = 1;
    // int b = 2;
    // swap(&a, &b);
    // printf("a: %d\n", a);
    // printf("b: %d\n", b);

    // int newArraySize = 7;
    // int* newArrSorted = createSorted(newArraySize);
    // int* newArrBackwards = createBackSorted(newArraySize);
    // printArr(newArrSorted, newArraySize);
    // printArr(newArrBackwards, newArraySize);
    int newArraySize = 7;
    int* newArrRandom = createRand(newArraySize);
    printArr(newArrRandom, newArraySize);
    bubbleSort(newArrRandom, newArraySize);
    printArr(newArrRandom, newArraySize);
    return 0;
}