#include <stdio.h>
#include <stdbool.h>
#include "calc.h"
#define TWO 2
// According to all known laws of aviation, there is no way a bee should be able to fly.
// Its wings are too small to get its fat little body off the ground.
// The bee, of course, flies anyway because bees don't care what humans think is impossible.
void println(char* msg) {
    printf(msg);
    printf("\n");
}


int main(void) {
    bool isRich = false;
    printf("Hello Forsaken World!\n");

    if (add(1, 1) == 2) {
        isRich = true;
    }

    if (isRich) {
        printf("Squeeze every drop of value from your workers!\n");
    }
    else {
        printf("Let's escape to the one place that hasn't been corrupted by capitalism... SPACE!\n");
    }

    return 0;
}
