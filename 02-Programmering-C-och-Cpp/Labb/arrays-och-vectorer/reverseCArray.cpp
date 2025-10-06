#include <iostream>

int arr1[] = {1,2,3,4,5};
int arr2[5];

int arrSize = sizeof(arr1) / sizeof(arr1[0]);

int main() {
    for (int i = 0; i < arrSize; i++) {
        arr2[i] = arr1[arrSize-i-1];
    }
    std::cout << "Arr1: ";
    for (int i = 0; i < arrSize; i++) {
        std::cout << arr1[i];
    }
    std::cout << "\nArr2: ";
    for (int i = 0; i < arrSize; i++) {
        std::cout << arr2[i];
    }

    return 0;
}