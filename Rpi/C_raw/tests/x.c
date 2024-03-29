#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

uint32_t flipMantissa(uint8_t* buffer, uint8_t* buf) {
    uint32_t value = 0;
    uint32_t sign = (buffer[3] >> 7) & 1;
    uint32_t exponent = ((buffer[3] & 0x7F) << 1) | ((buffer[2] >> 7) & 1);
    uint32_t mantissa = ((buffer[3] & 0x7F) << 16) | (buffer[1] << 8) | buffer[0];

    uint32_t bitPos = rand() % 23;
    mantissa ^= 1U << bitPos;

    for (int i = 0; i < 4; i++) {
        //printf("%02X ", buffer[i]);
        uint8_t byte = buffer[i];

        for(int j = 7; j >= 0; j--) {
            uint8_t bit = (byte >> j) & 1;
            printf("%u", bit);
        }
        printf(" ");
    }
    
    uint32_t intValue =  mantissa | (sign << 31) | (exponent << 23) ;
    memcpy (buf, &intValue, sizeof(float));
    for (int i = 0; i < 4; i++) {
        //printf("%02X ", buffer[i]);
        uint8_t byte = buf[i];

        for(int j = 7; j >= 0; j--) {
            uint8_t bit = (byte >> j) & 1;
            printf("%u", bit);
        }
        printf(" ");
    }

    return intValue;


}

int main() {
    uint8_t buf [4];
    uint8_t buffer[4] = {0x3A, 0x4D, 0x5C, 0x3F};  // Example buffer with a single-precision floating-point number (1.0)
    float originalValue;
    memcpy(&originalValue, buffer, sizeof(float));


    uint32_t intValue = flipMantissa(buffer,buf);

    return 0;
}