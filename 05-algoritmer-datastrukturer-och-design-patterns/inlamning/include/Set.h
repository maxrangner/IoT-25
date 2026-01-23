#ifndef SET_H
#define SET_H
#include "utils.h"
#include "config.h"

typedef struct Set {
    int sensorIds[SET_CAPACITY];
    int capacity;
    int size;
} Set;

void setInitialize(Set* set);
int setContains(const Set* set, int id);
static int findIndex(const Set* set, int id);
void setAdd(Set* set, int sensorId);
void setRemove(Set* set, int sensorId);

#endif