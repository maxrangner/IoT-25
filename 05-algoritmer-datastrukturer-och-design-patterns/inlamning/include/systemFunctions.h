#ifndef SYSTEMFUNCTIONS_H
#define SYSTEMFUNCTIONS_H
#include "EventLog.h"
#include "EventQueue.h"

void printMenu();
void printHelp();
void tick(int n);
void sortLog(EventLog* log);
int findSensor(EventLog* log, int id);
void quit(EventLog* log, EventQueue* queue);

#endif