#include <iostream>
#include <string>
#include <vector>

/* VERSION 1:
int getCount(const std::string& inputStr) {
    std::string vowels = "aeiou";
    int numVowels = 0;
    int strLength = inputStr.length();

    for (int i = 0; i < strLength; i++) {
        std::cout << inputStr[i] << "\n";
        for (int j = 0; j < vowels.length(); j++) {
            if (inputStr[i] == vowels[j]) {
                numVowels++;
            }
        }
    }

    return numVowels;
}

int main() {
    std::string myStr;
    std::cin >> myStr;
    std::cout << getCount(myStr);
}
    */

// Version 2:

int getCount(const std::string& inputStr) {
    std::string vowels = "aeiouAEIOU";
    int numVowels = 0;
    for (char c : inputStr) {
        if (vowels.find(c) != std::string::npos) {
            numVowels++;
        }
    }
    return numVowels;
}

int main() {
    std::string myStr;
    std::cout << "Count vowels in string: ";
    std::getline(std::cin, myStr);
    std::cout << getCount(myStr);

    return 0;
}