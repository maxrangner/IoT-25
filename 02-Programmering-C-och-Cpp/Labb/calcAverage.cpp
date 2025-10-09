#include <iostream>

float avarage(float a, float b) {
    return (a + b) / 2;
}

int main() {
    float userInpA, userInpB {};
    std::cin >> userInpA >> userInpB;
    std::cout << avarage(userInpA, userInpB);
    return 0;
}