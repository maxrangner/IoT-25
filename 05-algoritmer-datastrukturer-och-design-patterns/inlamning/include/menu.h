#ifndef MENU_H
#define MENU_H

#include "menu.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "stdio.h"
#include "Event.h"
#include "EventQueue.h"
#include "EventLog.h"

void printMenu();
void parseInput(char* input, char* command, char* argument);
void handleMenuInput();
void menu();
void printHelp();
void quit(EventLog* log, EventQueue* queue);

#endif