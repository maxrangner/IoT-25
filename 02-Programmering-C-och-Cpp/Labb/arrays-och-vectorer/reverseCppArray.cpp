#include <iostream>
#include <array>

std::array<int, 5> myArray1 = {1,2,3,4,5};
std::array<int, myArray1.size()> myArray2;

int main() {
    for (int i = 0; i < myArray1.size(); i++) {
        myArray2[i] = myArray1[myArray1.size()-i-1];
    }

    std::cout << "myArray1: ";
    for (int i = 0; i < myArray1.size(); i++) {
        std::cout << myArray1[i];
    }

    std::cout << "\nmyArray2: ";
    for (int i = 0; i < myArray2.size(); i++) {
        std::cout << myArray2[i];
    }

    return 0;
}