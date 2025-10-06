#include <vector>
#include <iostream>

std::vector<int> vec1;
std::vector<int> vec2;
int numElements = 5;

int main() {
    for (int i = 0; i < numElements; i++) {
        vec1.push_back(i+1);
    }

    int vec1Size = vec1.size();

    for (int i = 0; i < vec1.size(); i++) {
        vec2.push_back(vec1[vec1Size-i-1]);
    }

    std::cout << "Vec1: ";
    for (int i = 0; i < vec1.size(); i++) {
        std::cout << vec1[i];
    }

    std::cout << "\nVec2: ";
    for (int i = 0; i < vec2.size(); i++) {
        std::cout << vec2[i];
    }
    
    return 0;
}