
// needs -I /path/to/AFLplusplus/include
#include "afl-fuzz.h"
#include "alloc-inl.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define DATA_SIZE (32)

typedef struct my_mutator
{

    afl_state_t *afl;

    // Reused buffers:
    u8 *fuzz_buf;

} my_mutator_t;

my_mutator_t *afl_custom_init(afl_state_t *afl, unsigned int seed)
{
    
    //printf("1");
    srand(seed);
    my_mutator_t *data = calloc(1, sizeof(my_mutator_t)); //pointer to the allocated space
    if (!data)
    {

        perror("afl_custom_init alloc");
        return NULL;
    }

    data->fuzz_buf = (u8 *)malloc(MAX_FILE);
    if (!data->fuzz_buf)
    {

        perror("afl_custom_init malloc");
        return NULL;
    }

    data->afl = afl;

    return data;
}

void flipMantissaBit(uint8_t *buf1,my_mutator_t *data, u8 **out_buf) {
    // single-precision floating-point value (float)

    uint32_t sign = (buf1[0] >> 7) & 1;
    uint32_t exponent = ((buf1[3] & 0x7F) << 1) | ((buf1[1] >> 7) & 1);
    uint32_t mantissa = ((buf1[2] & 0x7F) << 16) | (buf1[1] << 8) | buf1[0];

    //flipping random bit of mantissa
    uint32_t bitPos = rand() % 23;
    mantissa ^= 1U << bitPos;

    //combining the segments of the float
    uint32_t intValue = (sign << 31) | (exponent << 23) | mantissa;

    memcpy(data->fuzz_buf, &intValue, sizeof(float));

    *out_buf = data->fuzz_buf;
    

}

size_t afl_custom_fuzz(my_mutator_t *data, uint8_t *buf, size_t buf_size,
                       u8 **out_buf, uint8_t *add_buf,
                       size_t add_buf_size, // add_buf can be NULL
                       size_t max_size)
{

    // my_mutator_t *data   --pointer to my_mutator structure
    // uint8_t *buf         --input buffer
    // size_t buf_size      --size of the input buffer
    // u8 **out_buf         --pointer to the output buffer
    // uint8_t *add_buf     --aditional buffer
    // size_t add_buf_size  --add_buf size
    // size_t max_size      --max size of out buff

    size_t mutated_size = DATA_SIZE <= max_size ? DATA_SIZE : max_size;

    //afl_realloc(out_buf, sizeof(float));


    flipMantissaBit(buf,data,out_buf);

    return mutated_size;

}



void afl_custom_deinit(my_mutator_t *data)
{

    free(data->fuzz_buf);
    free(data);
}