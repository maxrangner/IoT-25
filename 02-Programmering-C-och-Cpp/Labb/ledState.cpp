#include <iostream>

void setLedState(bool* led, bool state) {
    *led = state;
}

int main() {
    bool ledState = false;
    int userInp = 0;

    std::cout << "Toggle LED [1] = on, [0] = off" << std::endl;
    while(true) {
        std::cout << ">";
        std::cin >> userInp;
        setLedState(&ledState, userInp);
        std::cout << "LED is: " << (ledState ? "ON" : "OFF") << std::endl;
    }
}