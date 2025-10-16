#include <iostream>

int inpInt;
std::string result;
std::string fizzBuzz(int num);

int main() {
    std::cout << "To what whole number do you want to check? ";
    std::cin >> inpInt;

    for (int i = 1; i <= inpInt; i++) {
        std::cout << fizzBuzz(i) << "\n";
    }

}

std::string fizzBuzz(int num) {
    std::string output;
    if (num % 3 == 0) {
        output += "Fizz";
    } if (num % 5 == 0) {
        output += "Buzz";
    } if (output.empty()) {
        output = std::to_string(num);
    }
    return output;
}