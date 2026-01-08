#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "statistics.h"

int main() {
    struct Statistics stats;
    reset(&stats);
    int arrSize = 9;
    int* myArr = createBackSorted(arrSize);
    printf("\nUtgångsläge:\n");
    printArr(myArr, arrSize);

    // quickSort(myArr, arrSize);
    
    quickSort(myArr, arrSize, &stats);
    printf("\nResultat:\n");
    printArr(myArr, arrSize);
    printStats(&stats);

    free(myArr);
    return 0;
}