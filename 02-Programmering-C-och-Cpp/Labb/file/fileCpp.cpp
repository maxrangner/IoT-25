#include <iostream>
#include <vector>
#include <fstream>

bool writeToFile(std::vector<float>& myInpVec) {
    std::ofstream outFile("data.txt");
    if (!outFile) return false;
    for (float f : myInpVec){
        outFile << f << std::endl;
    }
    outFile.close();
    return true;
}

bool readFromFile(std::vector<float>& myOutVec) {
    std::ifstream inFile("data.txt");
    if (!inFile) return false;

    std::string newString;
    while(std::getline(inFile, newString)) {
        myOutVec.push_back(std::stof(newString));
    }
    inFile.close();
    return true;
}

int main() {
    std::vector<float> myInpVec {};
    std::vector<float> myOutVec {};
    int sum = 0;

    // Get user input
    for (int i = 0; i < 5; i++) {
        std::string usrInp;
        std::cout << "> ";
        std::cin >> usrInp;
        myInpVec.push_back(stof(usrInp));
    }

    // Write to the file
    if (writeToFile(myInpVec)) std::cout << "Success writing file!\n";
    else std::cout << "Error writing to file.\n";

    // Read from the file
    if (readFromFile(myOutVec)) std::cout << "Success reading file!\n";
    else std::cout << "Error writing to file.\n";

    // Print vector and calculate sum
    for (float f : myOutVec) {
        std::cout << f << "\n";
        sum += f;
    }

    std::cout << "Sum: " << sum;
}