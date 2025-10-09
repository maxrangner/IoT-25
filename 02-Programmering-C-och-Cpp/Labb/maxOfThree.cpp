#include <iostream>
#include <array>

int max(std::array<int, 5> inpArr) {
    int max {};
    for (int i = 0; i < 5; i++) {
        if (inpArr[i] > max) {
            max = inpArr[i];
        }
    }
    return max;
}

int main() {
    std::array<int, 5> myArr = {4, 7, 3, 9, 0};
    std::cout << max(myArr);
}