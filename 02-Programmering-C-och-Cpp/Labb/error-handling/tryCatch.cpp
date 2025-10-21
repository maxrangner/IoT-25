#include <iostream>
#include <stdexcept>
#include <fstream>

void readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    std::cout << "File opened correctly." << std::endl;
}

int main() {
    try {
        readFile("data.txt");
    } catch (const std::exception& e) {
        std::cerr << "Error:" << e.what() << std::endl;
    }
}