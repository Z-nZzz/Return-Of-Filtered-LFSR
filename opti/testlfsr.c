#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "filter.h"

// Helper macros for tests
#define ASSERT_EQUAL_UINT64_ARRAY(expected, actual, size) \
    for (size_t i = 0; i < size; ++i) { \
        if (expected[i] != actual[i]) { \
            printf("Assertion failed at index %zu: expected %lx, got %lx\n", i, expected[i], actual[i]); \
            return 0; \
        } \
    }

#define ASSERT_EQUAL_UINT8(expected, actual) \
    if (expected != actual) { \
        printf("Assertion failed: expected %d, got %d\n", expected, actual); \
        return 0; \
    }

#define ASSERT_TRUE(condition) \
    if (!(condition)) { \
        printf("Assertion failed: condition is false\n"); \
        return 0; \
    }


int main() {
    int_t key[NB_WORD] = {0xDEADBEEFDEADBEEF, 0xCAFEBABECAFEBABE, 0xDEADBEEFDEADBEEF, 0xCAFEBABECAFEBABE,0xDEADBEEFDEADBEEF, 0xCAFEBABECAFEBABE,0xDEADBEEFDEADBEEF, 0xCAFEBABECAFEBABE,0xDEADBEEFDEADBEEF};
    printf("Running test_lfsr_init...\n");
    LFSR_t lfsr;
    lfsr_init(&lfsr, key);
    const int_t key2[NB_WORD] = {0xDEADBEEFDEADBEEF, 0xCAFEBABECAFEBABE, 0xDEADBEEFDEADBEEF, 0xCAFEBABECAFEBABE,0xDEADBEEFDEADBEEF, 0xCAFEBABECAFEBABE,0xDEADBEEFDEADBEEF, 0xCAFEBABECAFEBABE,0xDEADBEEFDEADBEEF};
    //ASSERT_EQUAL_UINT64_ARRAY(key, lfsr.s, NB_WORD);
    for (size_t i = 0; i < NB_WORD; ++i) { 
        if (key2[i] != lfsr.s[i]) { 
            printf("Assertion failed at index %zu: expected %lx, got %lx\n", i, key2[i],lfsr.s[i]); 
            return 0; 
        } 
    }
    
    printf("Running test_lfsr_sum...\n");
    ASSERT_EQUAL_UINT8(1, lfsr_sum(&lfsr));
    
    /*printf("Running test_lfsr_bit...\n");
    //ASSERT_EQUAL_UINT8(1, lfsr_bit(&lfsr));
    printf("first output: %d \n", lfsr_bit(&lfsr));
    */
    printf("Running test_lfsr_sum...\n");
    ASSERT_EQUAL_UINT8(0, lfsr_sum(&lfsr));
    
    printf("Running test_lfsr_sum...\n");
    ASSERT_EQUAL_UINT8(0, lfsr_sum(&lfsr));
    
    printf("Running test_print_state...\n");
    print_state(&lfsr);

    printf("All tests passed.\n");
    return 0;
}
