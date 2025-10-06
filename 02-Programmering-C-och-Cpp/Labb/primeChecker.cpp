#include <iostream>

bool isPrime(int num) {
    if (num < 2) return false;
    for (int i = 2; i < num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

int main() {
    int inpVal {};
    std::cout << "Check if number is a prime: ";
    while (true) {
        std::cin >> inpVal;
        if (isPrime(inpVal)) {
            std::cout << "It's a prime!\n";
        } else {
            std::cout << "It's not a prime.\n";
        }
    }
    return 0;
}