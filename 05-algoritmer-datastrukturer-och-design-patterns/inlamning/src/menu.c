#include "menu.h"

typedef struct {
    char cmd[20];
    void (*menuOption)(Context*, char*);
} command;

command commandList[] = {{.cmd = "help", .menuOption = printHelp}};

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

    printf("inputCommand: %s\n", inputCommand);
    printf("inputArgument: %s\n", inputArgument);

    if (strcmp(inputCommand, "tick") == 0) {
        int n = 1;
        if (strcmp(inputArgument, "") != 0) {
            n = atoi(inputArgument);
        }
        printf("%s %d", inputCommand, n);
    } else if (strcmp(inputCommand, "print") == 0) {
        printf("%s", "Command print\n");
    } else if (strcmp(inputCommand, "sort") == 0) {
        printf("%s", "Command sort\n");
    } else if (strcmp(inputCommand, "find") == 0) {
        printf("%s", "Command find\n");
    } else if (strcmp(inputCommand, "help") == 0) {
        printf("%s", "Command help\n");
    } else if (strcmp(inputCommand, "quit") == 0) {
        printf("%s", "Command quit\n");
    } else {
        printf("%s", "Invalid command\n");
    }
}

void menu(Context* ctx) {
    printMenu();
    handleMenuInput(ctx);
}

void printHelp(Context* ctx, char* arg) {
    printf("Available commands:\n");
    printf("tick <n> - Run simulation n number of times\n");
    printf("print - Print log. Add <n> to limit results\n");
    printf("sort - View sorted log\n");
    printf("find <n> - Find all entires for specific sensor\n");
    printf("help - Display available commands\n");
    printf("quit - Exit program\n\n");
}

void quit(Context* ctx, char* arg) {
    // queueReset(queue);
    // logDestroy(log);
}
