#include <stdio.h>

int main() {
    FILE *f = fopen("data.txt", "r");
    if (f == NULL) {
        perror("Error opening file");
        return 1;
    } else {
        printf("File opened.");
    }
    return 0;
}