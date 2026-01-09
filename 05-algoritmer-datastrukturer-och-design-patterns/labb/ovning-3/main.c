
#define _CRT_SECURE_NO_WARNINGS

#include "list.h"
#include <stdio.h>

// KOMMENTAR OM MINNE:
// I detta program använder vi heap allocation (malloc) för att skapa noder i vår länkade lista.
// I embedded-programmering kan det vara riskabelt pga av fragmentering och begränsade resurser.
// I riktig firmware använder vi ofta object ppols eller fixed-size buffers.

void listMenu(void)
{
    int choice = -1;
    int value = 0;
    List testList = createEmptyList();
    printf("Menu:\n0: Exit\n1: Add node first\n2: Add node last\n3: Remove first node\n4: Remove last node\n5: Remove by data\n6: Contains data\n7: Print list\n");

    do {
        printf("Menu choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Choose data for node: ");
            scanf("%d", &value);
            addFirst(&testList, value);
        }
        else if (choice == 2) {
            printf("Choose data for node: ");
            scanf("%d", &value);
            addLast(&testList, value);
        }
        else if (choice == 3) {
            removeFirst(&testList);
        }
        else if (choice == 4) {
            removeLast(&testList);
        }
        else if (choice == 5) {
            printf("Choose data to remove: ");
            scanf("%d", &value);
            removeElement(&testList, value);
        }
        else if (choice == 6) {
            printf("Choose data for search: ");
            scanf("%d", &value);
            if (isInList(testList, value))
                printf("List contains %d: TRUE\n", value);
            else
                printf("List contains %d: FALSE\n", value);
        }
        else if (choice == 7) {
            printList(testList, stdout);
            printf("\n");
        }
    } while (choice != 0);
}

int main(void) {
    listMenu();
    return 0;
}