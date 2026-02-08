#include <stdint.h>
#include <stdio.h>

int main() {
  int8_t x_overflow = 127;
  int8_t one = x_overflow >> 1;
  int8_t two = x_overflow >> 2;
  int8_t three = x_overflow >> 3;
  int8_t four = x_overflow >> 4;
  int8_t five = x_overflow >> 5;
  int8_t six = x_overflow >> 6;
  int8_t seven = x_overflow >> 7;
  int8_t eight = x_overflow >> 8;

  printf("x_overflow:\t%i\none:\t%i\ntwo:\t%i\nthree:\t%i\nfour:\t%i\nfive:\t%"
         "i\nsix:\t%i\nseven:\t%i\neight:\t%i\n",
         x_overflow, one, two, three, four, five, six, seven, eight);
}