#include <iostream>
#include <vector>
#include <fstream>

bool writeToFile(std::vector<float> inpVec) {
    std::ofstream outFile("data.txt");
    if (!outFile) return false;
    for (float f : inpVec){
        outFile << f << std::endl;
    }
    outFile.close();
    return true;
}

bool readFromFile(float temp) {
    std::ofstream inFile("data.txt");
    if (!inFile) return false;
    inFile << temp << std::endl;
    inFile.close();
    return true;
}

int main() {
    std::vector<float> myVec;

    for (int i = 0; i < 5; i++) {
        std::string usrInp;
        std::cout << "> ";
        std::cin >> usrInp;
        myVec.push_back(stof(usrInp));
    }

    if (writeToFile(myVec)) std::cout << "Success!\n";
    else std::cout << "Error writing to file.\n";

    std::ifstream inFile("data.txt");

    std::string readLine;
    int sum = 0;
    while(std::getline(inFile, readLine)) {
        std::cout << readLine << std::endl;
        sum += std::stof(readLine);
    }

    std::cout << "Sum: " << sum;
}