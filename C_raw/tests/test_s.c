#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>


int main() {
    uint8_t buf [4];
    uint8_t buffer[4] = {0x3A, 0x4D, 0x5C, 0x3F};  // Example buffer with a single-precision floating-point number (1.0)
    float originalValue;
    memcpy(&originalValue, buffer, sizeof(float));
    printf("\nBefore: %.32f\n", originalValue);
    printf(" \n");
    for (int i = 3; i >= 0; i--) {
        //printf("%02X ", buffer[i]);
        uint8_t byte = buffer[i];

        for(int j = 7; j >= 0; j--) {
            uint8_t bit = (byte >> j) & 1;
            printf("%u", bit);
        }
        printf(" ");
    }


    uint32_t intValue ;
    memcpy(&intValue, buffer, sizeof(uint32_t));
    intValue ^= (1U << 31);

    memcpy(buf, &intValue, sizeof(float));

    float mutatedValue;
    memcpy(&mutatedValue, buf, sizeof(float));
    printf("\nAfter: %.32f\n", mutatedValue);

    // printf("\nAefore: %.32f\n", intValue);
    printf(" \n");
    for (int i = 3; i >= 0; i--) {
        //printf("%02X ", buffer[i]);
        uint8_t byte = buf[i];

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