#ifndef SYSTEMFUNCTIONS_H
#define SYSTEMFUNCTIONS_H
#include "EventLog.h"
#include "EventQueue.h"

void menu();
void printMenu();
void handleMenuInput();
void printHelp();
Event generateRandomEvent();
void tick(EventQueue* queue, EventLog* log, int iterations);
void sortLog(EventLog* log);
int findSensor(EventLog* log, int id);
void quit(EventLog* log, EventQueue* queue);

#endif