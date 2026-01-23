#include "menu.h"
#include "stdio.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "menu.h"
#include "Event.h"
#include "EventQueue.h"
#include "EventLog.h"
#include "Set.h"
#include "utils.h"
#include "sortingAlgorithms.h"

extern DebugLevel debugLevel;

// Map input string to MENU commands
typedef struct {
    char cmd[20];
    void (*function)(Context*, char*);
} command;

command commandList[] = {
    {.cmd = "help", .function = help},
    {.cmd = "tick", .function = tick},
    {.cmd = "print", .function = printLog},
    {.cmd = "sort", .function = sortLog},
    {.cmd = "find", .function = findSensor},
    {.cmd = "quit", .function = quit}
};

/********************************************************
******************* HELPER FUNCTIONS ********************
********************************************************/ 

void printMenu() {
    printf("\nEnter command: \n> ");
}

void parseInput(char* input, char* command, char* argument) {
    int index = 0;
    int commandIndex = 0;
    int argumentIndex = 0;

    // Add chars to command from input up until char is == ' ', '\0' or '\n'
    while (input[index] != ' ' && input[index] != '\0' && input[index] != '\n') {
        command[commandIndex++] = tolower(input[index++]);
    }
    command[commandIndex] = '\0'; // Add null terminator to make complete string
    index++;

    // Add chars to argument from input up until char is == ' ', '\0' or '\n'
    while (input[index] != ' ' && input[index] != '\0' && input[index] != '\n') {
        argument[argumentIndex++] = tolower(input[index++]);
    }
    argument[argumentIndex] = '\0';
    // Ignore rest of input
}

void handleMenuInput(Context* ctx) {
    char userInput[50] = {""}; // Arbitrary limit input to 50 chars
    char inputCommand[50] = {""};
    char inputArgument[50] = {""};

    fgets(userInput, sizeof(userInput), stdin);
    parseInput(userInput, inputCommand, inputArgument);

    if (debugLevel >= DEBUG) printf("inputCommand: %s\n", inputCommand);
    if (debugLevel >= DEBUG) printf("inputArgument: %s\n", inputArgument);

    int numCommands = sizeof(commandList) / sizeof(command);

    // Compare parsed command input with valid commands from commandList
    for (int i = 0; i < numCommands; i++) {
        if (strcmp(commandList[i].cmd, inputCommand) == 0) {
            commandList[i].function(ctx, inputArgument);
            return;
        }
    }
    printf("%s", "Invalid command.\n");
}

void menu(Context* ctx) {
    printMenu();
    handleMenuInput(ctx);
}

/********************************************************
******************** MENU FUNCTIONS *********************
********************************************************/ 

void help(Context* ctx, char* arg) {
    printf("\n**** Available commands ****\n\n");
    printf("tick <n> - Run simulation n number of times\n");
    printf("print - Print log. Add <n> to limit results\n");
    printf("sort - View sorted log\n");
    printf("find <n> - Find all entires for specific sensor\n");
    printf("help - Display available commands\n");
    printf("quit - Exit program\n\n");
}

void tick(Context* ctx, char* arg) {
    int iterations = atoi(arg); // Convert argument char array to int
    if (debugLevel >= DEBUG) printf("%s %d\n", "tick()", iterations);

    for (int i = 0; i < iterations; i++) { // Iterate iterations number of times
        // FOr every iteration create Event for each of the sensors
        for (int j = 0; j < 3; j++) { 
            Event newEvent;
            generateRandomEvent(&newEvent, &ctx->timeTicks, j);
            if (queueEnqueue(ctx->queue, newEvent) == 0) break;
        }
        // Empty queue into log
        while (!queueIsEmpty(ctx->queue)) {
            Event tempEvent;
            queueDequeue(ctx->queue, &tempEvent);
            
            if (tempEvent.sensorType == 0 && tempEvent.value > 25) {
                setAdd(ctx->set, tempEvent.sensorId); // If triggered this tick - put into set
            } else if (tempEvent.sensorType == 0 && tempEvent.value <= 25) {
                setRemove(ctx->set, tempEvent.sensorId); // If not triggered this tick, remove from set
            }
            logAppend(ctx->log, tempEvent);
        }
        ctx->timeTicks++;
    }

    if (debugLevel >= DEBUG) logPrint(ctx->log, stdout);
    for (int i = 0; i < ctx->set->size; i++) {
        printf("Triggered sensors: %d\n", ctx->set->sensorIds[i]);
    }
    if (debugLevel >= DEBUG) printf("Log size: %d\n", logSize(ctx->log));
}

void printLog(Context* ctx, char* arg) {
    if (debugLevel >= DEBUG) printf("%s\n", "printLog()");

    for (int i = 0; i < logSize(ctx->log); i++) {
        Event currentEvent = logGet(ctx->log, i);
        printf("Id: %d Time: %d\n", currentEvent.sensorId, currentEvent.timeLogged);
    } 
}

void sortLog(Context* ctx, char* arg) {
    if (debugLevel >= DEBUG) printf("%s\n", "sortLog()");
    if (debugLevel >= DEBUG) logPrint(ctx->log, stdout);

    int size = logSize(ctx->log);
    Event sortedArr[size];

    for (int i = 0; i < size; i++) {
        sortedArr[i] = logGet(ctx->log, i);
    }

    sortFunction chosenSort;
    if (strcmp(arg, "bubble") == 0) {
        chosenSort = bubbleSort;
    } else if (strcmp(arg, "selection") == 0) {
        chosenSort = selectionSort;
    } else {
        printf("%s\n", "Sorting algorithms available: bubble or selection");
        return;
    }
    chosenSort(sortedArr, size);

    for (int i = 0; i < size; i++) {
        printf("%d: SensorId: %d    SensorType: %d    Value: %f\n", i, sortedArr[i].sensorId, sortedArr[i].sensorType, sortedArr[i].value);
    }
}

void findSensor(Context* ctx, char* arg) {
    if (debugLevel >= DEBUG) printf("%s\n", "findSensor()");

    int id = atoi(arg);
    printf("%s: %d\n", "Id", id);
    for (int i = 0; i < logSize(ctx->log); i++) {
        if (logGet(ctx->log, i).sensorId == id) {
            printf("%d: %.2f\n", i, logGet(ctx->log, i).value);
        }
    }
}

void quit(Context* ctx, char* arg) {
    if (debugLevel >= DEBUG) printf("%s\n", "quit()");

    queueReset(ctx->queue);
    logDestroy(ctx->log);
    *ctx->running = 0;
}
