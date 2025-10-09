#include <iostream>
#include <array>

constexpr int ARRAY_SIZE = 5;

void printSensor(const std::array<float, ARRAY_SIZE>& value) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        std::cout << "Value " << i + 1 << ": " << value[i] << std::endl;  
    }
}

int main() {
    std::array<float, ARRAY_SIZE> myArray = {22.4, 21.5, 30.1, 25.7, 20.2};
    printSensor(myArray);
    return 0;
}