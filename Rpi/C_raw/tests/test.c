#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Helper functions
uint32_t flip_s(uint32_t bits);
uint32_t flip_e(uint32_t exponent, uint32_t bits);
uint32_t flip_m(uint32_t mantissa, uint32_t bits);
uint32_t add_e(uint32_t exponent, uint32_t bits);
uint32_t add_m(uint32_t mantissa, uint32_t bits);
uint32_t sub_e(uint32_t exponent, uint32_t bits);
uint32_t sub_m(uint32_t mantissa, uint32_t bits);

// Main function
uint32_t afl_float_mutator_32(uint32_t data)
{
    uint32_t mantissa = data & 0x7FFFFF;
    uint32_t exponent = (data >> 23) & 0xFF;

    uint32_t new_bits;
    char selected_case_name[5];
    uint32_t (*perform_mutation)(uint32_t, uint32_t);

    char* cases[] = { "flip_m", "flip_e", "flip_s", "add_e", "add_m", "sub_m", "sub_e" };
    int num_cases = 6;

    char selected_case_name[] = cases[rand() % num_cases];

    if (selected_case_name[0] == 'f' )
    {
        if (selected_case_name[5] == 'm')
            mantissa = flip_m(mantissa, data);
        else if (selected_case_name[5] == 'e')
            exponent = flip_e(exponent, data);
        else if (selected_case_name[5] == 's')
            data = flip_s(data);
    
    }
    else if (selected_case_name[0] == 'a')
    {

        if (selected_case_name[4] == 'm')
            mantissa = add_m(mantissa, data);
        else if (selected_case_name[4] == 'e')
            exponent = add_e(exponent, data);
        
    }
    else if (selected_case_name[0] == 's' && selected_case_name[1] == 'u' && selected_case_name[2] == 'b')
    {
        if (selected_case_name[4] == 'm')
            mantissa = sub_m(mantissa, data);
        else if (selected_case_name[4] == 'e')
            exponent = sub_e(exponent, data);    
    }

    new_bits = (data & 0x80000000) | (exponent << 23) | mantissa;

    // Check for NaN values and replace with 0
    float new_float = *(float*)&new_bits;
    if (new_float != new_float)
        new_bits = 0x0;

    return new_bits;
}

// Helper function implementations
uint32_t flip_s(uint32_t bits)
{
    return bits ^ 0x80000000;
}

uint32_t flip_e(uint32_t exponent, uint32_t bits)
{
    uint32_t exponent_bit = 1 << (rand() % 8);
    return exponent ^ exponent_bit;
}

uint32_t flip_m(uint32_t mantissa, uint32_t bits)
{
    uint32_t mantissa_bit = 1 << (rand() % 23);
    return mantissa ^ mantissa_bit;
}

uint32_t add_e(uint32_t exponent, uint32_t bits)
{
    uint32_t random_int = rand() % 32 + 1;
    return exponent + random_int;
}

uint32_t add_m(uint32_t mantissa, uint32_t bits)
{
    uint32_t random_int = rand() % 32 + 1;
    return mantissa + random_int;
}

uint32_t sub_e(uint32_t exponent, uint32_t bits)
{
    uint32_t random_int = rand() % 32 + 1;
    return abs(exponent - random_int);
}

uint32_t sub_m(uint32_t mantissa, uint32_t bits)
{
    uint32_t random_int = rand() % 32 + 1;
    return abs(mantissa - random_int);
}