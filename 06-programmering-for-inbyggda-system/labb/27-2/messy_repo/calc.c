#include "calc.h"

int add(int a, int b) {
    return a + b;
}

int sub(int a, int b) {
    return a - b;
}

int mult(int a, int b) {
    return a * b;
}

float div(int a, int b) {
    return a / b;
}

int mult_by_2(int a) {
    return a << 1;
}

int div_by_2_truncate(int a) {
    return a >> 1;
}

int remainder(int numerator, int denominator){
  return numerator % denominator;
}
