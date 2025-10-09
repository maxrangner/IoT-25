#include <iostream>

void ptrFunc(int* ptr, int& ref) {
    std::cout << "ptr: " << ptr << std::endl;
    std::cout << "*ptr: " << *ptr << std::endl;
    std::cout << "&ptr: " << &ptr << std::endl;
    std::cout << "ref: " << ref << std::endl;
    std::cout << "&ref: " << &ref << std::endl;
    std::cout << "\n";
}

int main() {
    int myInt = 1;

    ptrFunc(&myInt, myInt);

    return 0;
}