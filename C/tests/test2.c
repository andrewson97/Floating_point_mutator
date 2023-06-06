#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
// union FloatRep {
//     float f;
//     uint32_t i;
// };

void flipSignBit(uint8_t* buffer) {

        

    // Assuming single-precision floating-point value (float)
    uint32_t intValue;
    //union FloatRep rep;
    //uint32_t mantissa = ((buffer[1] & 0x7F) << 16) | (buffer[2] << 8) | buffer[3];
    uint32_t mantissa = ((buffer[1] & 0x7F) << 16) | (buffer[2] << 8) | buffer[3];
    printf("%u" ,mantissa);
    int bitPos = rand() % 23;
    mantissa ^= 1U << bitPos;

    // buffer[0] = mantissa & 0xFF;
    // buffer[1] = (mantissa >> 8) & 0xFF;
    // buffer[2] = (mantissa >> 16) & 0xFF;

    // //memcpy(, buffer, sizeof(uint32_t));

    // // Flipping the sign bit
    // //intValue ^= (1U << 31);

    // memcpy(buffer, &mantissa, sizeof(uint32_t));
}

int main() {
    // Example buffer containing a float value
    uint8_t buffer[4] = {0x4F, 0x4F, 0x4F, 0x3F};  // -0.5 as little-endian

    float originalValue;
    memcpy(&originalValue, buffer, sizeof(float));

    printf("1Before flipping sign bit: %.32f\n", originalValue);

    printf("2Before flipping sign bit: ");
    for (int i = 0; i < 4; i++) {
        printf("%02X", buffer[i]);
    }


    flipSignBit(buffer);

    float flippedValue;
    memcpy(&flippedValue, buffer, sizeof(float));

    printf("\n1After flipping sign bit:  %.32f\n", flippedValue);

    printf("2After flipping sign bit: ");
    for (int i = 0; i < 4; i++) {
        printf("%02X ", buffer[i]);
    }

    return 0;
}