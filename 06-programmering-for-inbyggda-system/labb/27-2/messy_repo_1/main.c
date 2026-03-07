#include <stdio.h>
#include <stdbool.h>

#define TWO 2

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
        println("Squeeze every drop of value from your workers!");
        println("Capitalism must rule!")

    }
    else {
        println("Eat the rich!");
        println("Let's go where capitalism ")
    }

    return 0;
}
