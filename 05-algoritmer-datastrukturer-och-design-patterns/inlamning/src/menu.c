#include "menu.h"
#include "utils.h"
#include "sortingAlgorithms.h"

extern DebugLevel debugLevel;

typedef struct {
    char cmd[20];
    void (*function)(Context*, char*);
} command;

command commandList[] = {
    {.cmd = "help", .function = help},
    {.cmd = "tick", .function = tick},
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

    while (input[index] != ' ' && input[index] != '\0' && input[index] != '\n') { // Kollar input fram tills ' ' eller '\0'
        command[commandIndex++] = tolower(input[index++]);
    }
    command[commandIndex] = '\0';
    index++;
    while (input[index] != ' ' && input[index] != '\0' && input[index] != '\n') {
        argument[argumentIndex++] = tolower(input[index++]);
    }
    argument[argumentIndex] = '\0';
}

void handleMenuInput(Context* ctx) {
    char userInput[50] = {""};
    char inputCommand[50] = {""};
    char inputArgument[50] = {""};

    fgets(userInput, sizeof(userInput), stdin);
    parseInput(userInput, inputCommand, inputArgument);

    if (debugLevel >= DEBUG) printf("inputCommand: %s\n", inputCommand);
    if (debugLevel >= DEBUG) printf("inputArgument: %s\n", inputArgument);

    int numCommands = sizeof(commandList) / sizeof(command);

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
    // logPrint(ctx->log, stdout);
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
    int iterations = atoi(arg); // Konvertera argument char array till int
    if (debugLevel >= DEBUG) printf("%s %d\n", "tick()", iterations);

    // Producer simplifierad. Bör vara egen funktion.
    for (int i = 0; i < iterations; i++) {
        for (int j = 0; j < 3; j++) {
            Event newEvent;
            generateRandomEvent(&newEvent, j);
            if (queueEnqueue(ctx->queue, newEvent) == 0) break;
        }

        while (!queueIsEmpty(ctx->queue)) {
            Event tempEvent;
            queueDequeue(ctx->queue, &tempEvent);
            logAppend(ctx->log, tempEvent);
        }
    }

    logPrint(ctx->log, stdout);
    printf("Log size: %d\n", logSize(ctx->log));
}

void sortLog(Context* ctx, char* arg) {
    if (debugLevel >= DEBUG) printf("%s\n", "sortLog()");

    logPrint(ctx->log, stdout);
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
