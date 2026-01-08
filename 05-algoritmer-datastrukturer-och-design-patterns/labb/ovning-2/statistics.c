#include <stdio.h>
#include "statistics.h"

void reset(struct Statistics* stats) {
    stats->assigns = 0;
    stats->comparisons = 0;
    stats->swaps = 0;
}

void printStats(struct Statistics* stats) {
    printf("Assigns: %d\nSwaps: %d\nComparisons: %d\n", stats->assigns, stats->swaps, stats->comparisons);
}

int greaterThan(int* a, int* b, struct Statistics* stats) {
    stats->comparisons++;
    if (*a > *b) return 1;
    else return 0;
}

int greaterThgreaterThanOrEqualToan(int* a, int* b, struct Statistics* stats) {
    stats->comparisons++;
    if (*a >= *b) return 1;
    else return 0;
}

int lessThan(int* a, int* b, struct Statistics* stats) {
    stats->comparisons++;
    if (*a < *b) return 1;
    else return 0;
}

int lessThanOrEqualTo(int* a, int* b, struct Statistics* stats) {
    stats->comparisons++;
    if (*a <= *b) return 1;
    else return 0;
}

int equalTo(int* a, int* b, struct Statistics* stats) {
    stats->comparisons++;
    if (*a = *b) return 1;
    else return 0;
}

int notEqualTo(int* a, int* b, struct Statistics* stats) {
    stats->comparisons++;
    if (*a != *b) return 1;
    else return 0;
}

int and(int* a, int* b, struct Statistics* stats) {
    stats->comparisons++;
    if (*a != *b) return 1;
    else return 0;
}

int or(int* a, int* b, struct Statistics* stats) {
    stats->comparisons++;
    if (*a != *b) return 1;
    else return 0;
}

int not(int* a, int* b, struct Statistics* stats) {
    stats->comparisons++;
    if (*a != *b) return 1;
    else return 0;
}