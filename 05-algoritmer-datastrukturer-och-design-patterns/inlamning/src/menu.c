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

void menu(Context* ctx) {
    printf("\nEnter command: \n> ");
    handleMenuInput(ctx);
}

void parseInput(char* input, char* command, char* argument) {
    int inputIndex = 0;
    int commandIndex = 0;
    int argumentIndex = 0;

    // Add chars to command from input up until char is == ' ', '\0' or '\n'
    while (input[inputIndex] != ' ' && input[inputIndex] != '\0' && input[inputIndex] != '\n') {
        command[commandIndex++] = tolower(input[inputIndex++]);
    }
    command[commandIndex] = '\0'; // Add null terminator to make complete string
    inputIndex++;

    // Add chars to argument from input up until char is == ' ', '\0' or '\n'
    while (input[inputIndex] != ' ' && input[inputIndex] != '\0' && input[inputIndex] != '\n') {
        argument[argumentIndex++] = tolower(input[inputIndex++]);
    }
    argument[argumentIndex] = '\0';
    // Ignore rest of input
}

void handleMenuInput(Context* ctx) {
    char userInput[INPUT_CHAR_LIMIT] = {""};
    char inputCommand[INPUT_CHAR_LIMIT] = {""};
    char inputArgument[INPUT_CHAR_LIMIT] = {""};

    fgets(userInput, sizeof(userInput), stdin);
    parseInput(userInput, inputCommand, inputArgument);
    
    // Compare parsed command input with valid commands from commandList
    int numCommands = sizeof(commandList) / sizeof(command);
    for (int i = 0; i < numCommands; i++) {
        if (strcmp(commandList[i].cmd, inputCommand) == 0) {
            commandList[i].function(ctx, inputArgument);
            return;
        }
    }
    printf("%s", "Invalid command.\n");
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
    if (iterations == 0) {
        printf("Please enter valid number of ticks requested.\n");
    } else {
        printf("Sensors polled %d number of times.\n", iterations);
    }

    for (int i = 0; i < iterations; i++) { // Produce <interations> number of readings from all sensors
        producer(ctx, i);
    }

    while (!queueIsEmpty(ctx->queue)) { // Move events from queue to log until queue is empty
        consumer(ctx);
    }
}

void printElement(Event* event) {
    printf("%.24s   ---   Id: %-5d %-15s %.2f%s\n", 
        ctime(&event->timeLogged),
        event->sensorId,
        sensorEnumToChar(event->sensorType),
        event->value,
        getSensorSuffix(event->sensorType));
}

void printLog(Context* ctx, char* arg) {
    int limit = atoi(arg);
    int max = logSize(ctx->log);
    if (limit <= 0 || limit > logSize(ctx->log)) {
        limit = max;
    }
    for (int i = 0; i < limit; i++) {
        Event temp = logGet(ctx->log, i);
        printElement(&temp);
    } 
}

void sortLog(Context* ctx, char* arg) {
    int size = logSize(ctx->log);
    Event sortedArr[size];

    for (int i = 0; i < size; i++) {
        sortedArr[i] = logGet(ctx->log, i);
    }

    sortFunction chosenSort = selectSort(arg);
    chosenSort(sortedArr, size);

    for (int i = 0; i < size; i++) {
        printElement(&sortedArr[i]);
    }
}

void findSensor(Context* ctx, char* arg) {
    int id = atoi(arg);
    printf("Fetching data from %s sensor\n", sensorEnumToChar(id));

    for (int i = 0; i < logSize(ctx->log); i++) {
        if (logGet(ctx->log, i).sensorId == id) {
            Event temp = logGet(ctx->log, i);
            printElement(&temp);
        }
    }
}

void quit(Context* ctx, char* arg) {
    queueReset(ctx->queue);
    logDestroy(ctx->log);
    *ctx->running = 0;
}
