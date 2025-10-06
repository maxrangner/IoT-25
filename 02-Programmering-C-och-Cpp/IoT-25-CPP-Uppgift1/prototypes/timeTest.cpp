#include <iostream>
#include <ctime>

int main() {
    //Alternativ 1
    std::time_t timestamp1;
    std::time(&timestamp1);

    //Alternativ 2
    std::time_t timestamp2 = std::time(nullptr);

    //Alternativ 3
    struct tm datetime = *localtime(&timestamp1);


    //Output
    std::cout << "Alternativ 1: " << std::ctime(&timestamp1);
    std::cout << "Alternativ 2: " << std::ctime(&timestamp2);
    std::cout << "Alternativ 3: " << std::asctime(&datetime);
    std::cout << "Alternativ 4: " << datetime.tm_hour;
    return 0;
}