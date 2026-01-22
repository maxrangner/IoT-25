#include "sortingAlgorithms.h"
#include "Context.h"

void bubbleSort(Event* returnArr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1; j++) {
            if (returnArr[j].value > returnArr[j + 1].value) {
                Event temp = returnArr[j];
                returnArr[j] = returnArr[j + 1];
                returnArr[j + 1] = temp;
            }
        }
    }
}

sortFunction sortBubble = bubbleSort;
