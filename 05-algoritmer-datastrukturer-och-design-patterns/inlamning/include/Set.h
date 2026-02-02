#ifndef SET_H
#define SET_H
#include "utils.h"
#include "config.h"

struct Set {
    int sensorIds[SET_CAPACITY];
    int capacity;
    int size;
};
typedef struct Set Set;

void setInitialize(Set* set);
int setContains(const Set* set, int id);
void setAdd(Set* set, int sensorId);
void setRemove(Set* set, int sensorId);

#endif