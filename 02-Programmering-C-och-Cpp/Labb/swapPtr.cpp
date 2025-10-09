#include <iostream>

void swap(int* a, int* b) {
    int swapVal = *a;
    *a = *b;
    *b = swapVal;
}

int main() {
    int a = 1;
    int b = 2;

    std::cout << "a: " << a << " b: " << b << std::endl;
    swap(&a, &b);
    std::cout << "a: " << a << " b: " << b << std::endl;

    return 0;
}