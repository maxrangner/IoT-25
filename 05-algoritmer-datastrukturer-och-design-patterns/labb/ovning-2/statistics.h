#ifndef STATISTICS_H
#define STATISTICS_H

struct Statistics {
    int assigns;
    int swaps;
    int comparisons;
};

void reset(struct Statistics* stats);
void printStats(struct Statistics* stats);
int greaterThan(int* a, int* b, struct Statistics* stats);
int greaterThanOrEqualTo(int* a, int* b, struct Statistics* stats);
int lessThan(int* a, int* b, struct Statistics* stats);
int lessThanOrEqualTo(int* a, int* b, struct Statistics* stats);
int equalTo(int* a, int* b, struct Statistics* stats);
int notEqualTo(int* a, int* b, struct Statistics* stats);
int notEqualTo(int* a, int* b, struct Statistics* stats);
int and(int* a, int* b, struct Statistics* stats);
int or(int* a, int* b, struct Statistics* stats);
int not(int* a, int* b, struct Statistics* stats);

#endif