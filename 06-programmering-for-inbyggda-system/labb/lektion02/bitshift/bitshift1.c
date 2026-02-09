#include <stdio.h>
#include <stdint.h>

int main(void) {
    int8_t signed_min = INT8_MIN;
    int8_t signed_max = INT8_MAX;
    uint8_t unsigned_min = 0;
    uint8_t unsigned_max = UINT8_MAX;

    int8_t signedVar = 204; // 0b01001100
    uint8_t unsignedVar = 204; // 0b11001100

    printf("signedVar: %i\nunsignedVar: %i", signedVar, unsignedVar);


    printf("\nsigned_min: %i\nsigned_max: %i\nusigned_min: %i\nusigned_max: %i\n\n", 
        signed_min, signed_max, unsigned_min, unsigned_max);

    int8_t r_overflow = 204;
    int8_t r_signed = r_overflow >> 2;
    uint8_t r_unsigned = 204 >> 2;

    printf("r_overflow: %i      >> 2      -> r_signed: %i  r_unsigned: %i\n", r_overflow, r_signed, r_unsigned);

    int8_t l_overflow = 204;
    int8_t l_signed = l_overflow << 2;
    uint8_t l_unsigned = 204 << 2;
    printf("l_overflow: %i      << 2      -> l_signed: %i l_signed: %i\n\n", l_overflow, l_signed, l_unsigned);
    
    return 0;
}