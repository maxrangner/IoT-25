#include <iostream>

int divide(int a, int b) {
    int result {};

    result = a / b;

    return result;
}

int main() {
    int a = 5;
    int b = 0;
    std::cout << "Result: " << divide(a,b);
}