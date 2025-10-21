#include <sstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

bool readFromFile(std::vector<int>& vec) {
    std::string newLine;       
    std::ifstream inFile("myData.txt");

    if (!inFile) {
        std::cerr << "Error opening file\n";
        return false;
    } else std::cout << "File open.\n";

    while (std::getline(inFile, newLine)) {
        int temp;
        std::stringstream ss(newLine);
        while (ss >> temp) {
            vec.push_back(temp);
        }
    }
    inFile.close();
    return true;
}

int main() {
    std::vector<int> vec;
    readFromFile(vec);

    for (int i : vec) {
        std::cout << i << std::endl;
    }

    return 0;             
}