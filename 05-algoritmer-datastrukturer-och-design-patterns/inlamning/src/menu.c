#include "menu.h"
#include "utils.h"

extern DebugLevel debugLevel;

typedef struct {
    char cmd[20];
    void (*menuOption)(Context*, char*);
} command;

command commandList[] = {
    {.cmd = "help", .menuOption = help},
    {.cmd = "tick", .menuOption = tick},
    {.cmd = "sort", .menuOption = sortLog},
    {.cmd = "find", .menuOption = findSensor},
    {.cmd = "quit", .menuOption = quit}
};

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
            commandList[i].menuOption(ctx, inputArgument);
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
    int iterations = atoi(arg); // Konvertera argument char array till int
    if (debugLevel >= DEBUG) printf("%s %d", "tick()\n", iterations);

    // Producer simplifierad. Bör vara egen funktion.
    for (int i = 0; i < iterations; i++) {
        Event newEvent;
        newEvent = generateRandomEvent();
        if (queueEnqueue(ctx->queue, newEvent) == 0) break;
    }
    
    // Consumer simplifierad. Bör vara egen funktion.
    while (!queueIsEmpty(ctx->queue)) {
        Event tempEvent;
        queueDequeue(ctx->queue, &tempEvent);
        logAppend(ctx->log, tempEvent);
    }
    printf("Log size: %d", logSize(ctx->log));
}

void sortLog(Context* ctx, char* arg) {
    if (debugLevel >= DEBUG) printf("%s", "sortLog()");
    // NOT IMPLEMENTED YET
}

void findSensor(Context* ctx, char* arg) {
    if (debugLevel >= DEBUG) printf("%s", "findSensor()");
    // NOT IMPLEMENTED YET
}

void quit(Context* ctx, char* arg) {
    if (debugLevel >= DEBUG) printf("%s", "quit()");
    queueReset(ctx->queue);
    logDestroy(ctx->log);
    *ctx->running = 0;
}
