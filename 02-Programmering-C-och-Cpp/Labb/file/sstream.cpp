#include <sstream>
#include <iostream>
#include <vector>
#include <sstream>

int main() {
    std::string str = "12 3 456";   
    std::vector<int> vec;     
    std::stringstream ss(str);                     
    int temp;

    while (ss >> temp) {
        vec.push_back(temp);
    }
   
    for (int& i : vec) {
            std::cout << "Integer: " << i << std::endl;
    }

    return 0;             
}