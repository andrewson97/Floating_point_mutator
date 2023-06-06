#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

uint32_t flipMantissa(uint8_t* buffer) {
    uint32_t value = 0;
    uint32_t sign = (buffer[0] >> 7) & 1;
    uint32_t exponent = ((buffer[0] & 0x7F) << 1) | ((buffer[1] >> 7) & 1);
    uint32_t mantissa = ((buffer[1] & 0x7F) << 16) | (buffer[2] << 8) | buffer[3];

    printf("\nsign\n");
    for (int i = 31; i >= 0; i--) {
        int bit = (sign >> i) & 1;
        printf("%d", bit);
    }
    printf("\nexp\n");
    for (int i = 31; i >= 0; i--) {
        int bit = (exponent >> i) & 1;
        printf("%d", bit);
    }

    uint32_t bitPos = rand() % 23;
    mantissa ^= 1U << bitPos;
    uint32_t intValue = (sign << 31) | (exponent << 23) | mantissa;


    return intValue;


}

int main() {
    uint8_t buffer[4] = {0x3F, 0x3F, 0x4D, 0x3F};  // Example buffer with a single-precision floating-point number (1.0)
    float originalValue;
    memcpy(&originalValue, buffer, sizeof(float));
    printf("\nBefore: %.32f\n", originalValue);
    printf(" \n");
    for (int i = 0; i < 4; i++) {
        //printf("%02X ", buffer[i]);
        uint8_t byte = buffer[i];

        for(int j = 7; j >= 0; j--) {
            uint8_t bit = (byte >> j) & 1;
            printf("%u", bit);
        }
        printf(" ");
    }


    uint32_t intValue = flipMantissa(buffer);

    memcpy(buffer, &intValue, sizeof(float));

    // printf("\nAefore: %.32f\n", intValue);
    printf(" \n");
    for (int i = 0; i < 4; i++) {
        //printf("%02X ", buffer[i]);
        uint8_t byte = buffer[i];

        for(int j = 7; j >= 0; j--) {
            uint8_t bit = (byte >> j) & 1;
            printf("%u", bit);
        }
        printf(" ");
    }
    // printf("\nbmant");
    // for (int i = 31; i >= 0; i--) {
    //     int bit = (mantissa >> i) & 1;
    //     printf("%d", bit);
    // }
    // printf("\n");

    
    // printf("\namant");
    // for (int i = 31; i >= 0; i--) {
    //     int bit = (mantissa >> i) & 1;
    //     printf("%d", bit);
    // }

    
    // printf("\nnewfloat\n");
    // for (int i = 31; i >= 0; i--) {
    //     int bit = (intValue >> i) & 1;
    //     printf("%d", bit);
    // }
    // printf("\ns\n");
    // for (int i = 31; i >= 0; i--) {
    //     int bit = (sign >> i) & 1;
    //     printf("%d", bit);
    // }
    // printf("\nexp\n");
    // for (int i = 31; i >= 0; i--) {
    //     int bit = (exponent >> i) & 1;
    //     printf("%d", bit);
    // }



    //printf("Mantissa: 0x%06X\n", mantissa);

    return 0;
}