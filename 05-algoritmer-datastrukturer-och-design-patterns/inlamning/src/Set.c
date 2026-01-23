#include "Set.h"

extern DebugLevel debugLevel;

void setInitialize(Set* set) {
    if (debugLevel >= DEBUG) printf("%s\n", "setInit()\n");
    set->capacity = SET_CAPACITY;
    set->size = 0;
}

int setContains(const Set* set, int id) {
    for (int i = 0; i < set->size; i++) {
        if (set->sensorIds[i] == id) return 1;
    }
    return 0;
}

static int findIndex(const Set* set, int id) {
    for (int i = 0; i < set->size; i++) {
        if (set->sensorIds[i] == id) return i;
    }
    return -1;
}

void setAdd(Set* set, int sensorId) {
    if (debugLevel >= DEBUG) printf("%s\n", "setAdd()\n");
    if (setContains(set, sensorId) || set->size >= set->capacity) return;
    set->sensorIds[set->size] = sensorId;
    set->size++;
    return;
}

void setRemove(Set* set, int sensorId) {
    if (debugLevel >= DEBUG) printf("%s\n", "setRemove()\n");
    int indexToRemove = findIndex(set, sensorId);
    if (indexToRemove >= 0) {
        set->sensorIds[indexToRemove] = set->sensorIds[set->size - 1];
        set->size--;
    }
}
