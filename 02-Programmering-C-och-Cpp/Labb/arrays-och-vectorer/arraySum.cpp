#include <iostream>
#include <array>
#include <random>

// Initiasion
constexpr int arraySize {5};
std::array<int, arraySize> myArray {};
int sum {};
float mean {};
int min {};
int max {};
int numEven {};

// Randomizer
std::mt19937 gen(std::random_device{}());
std::uniform_int_distribution<int> dist(1,20);

int main () {
    // Fill array with random numbers
    for (int i = 0; i < arraySize; i++) {
        myArray[i] = dist(gen);
    }

    // Add all the elements to "sum"
    for (int i = 0; i < arraySize; i++) {
        sum += myArray[i];
    }

    // Calculate mean
    mean = (float)sum / myArray.size();

    // Check min/max
    min = myArray[0];
    max = myArray[0];
    for (int i = 0; i < arraySize; i++) {
        if (myArray[i] < min) {
            min = myArray[i];
        } else if (myArray[i] > max) {
            max = min = myArray[i];
        }
    }

    for (int i = 0; i < arraySize; i++) {
        if (myArray[i] % 2 == 0) {
            numEven += 1;
        }
    }

    // Print results
    std::cout << "myArray: ";
    for (int i = 0; i < arraySize; i++) {
        std::cout << myArray[i] << " ";
    }
    std::cout << "\nSumman av myArray: " << sum;
    std::cout << "\nMedelvärdet av myArray: " << mean;
    std::cout << "\nMin: " << min;
    std::cout << "\nMax: " << max;
    std::cout << "\nAmout of even digits: " << numEven;

    return 0;
}