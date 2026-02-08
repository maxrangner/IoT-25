#include <avr/io.h>
#include <util/delay.h>

#define numPins 8
#define intA 0b0001
#define intB 0b0001
// uint8_t ledPins[numPins] = {PD0, PD1, PD2, PD3, PD4, PD5, PD6, PD7};
uint8_t buffer = (intA << 4) | intB;

int main(void) {
    uint8_t valA = buffer >> 4;
    uint8_t valB = buffer & 0b00001111;
    uint8_t sum = valA + valB;

    return 0;
}