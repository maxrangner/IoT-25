#ifndef MENU_H
#define MENU_H

#include "stdio.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "menu.h"
#include "Event.h"
#include "EventQueue.h"
#include "EventLog.h"
#include "Context.h"

void printMenu();
void parseInput(char* input, char* command, char* argument);
void handleMenuInput(Context* ctx);
void menu(Context* ctx);
void help(Context* ctx, char* arg);
void tick(Context* ctx, char* arg);
void sortLog(Context* ctx, char* arg);
void findSensor(Context* ctx, char* arg);
void quit(Context* ctx, char* arg);

#endif