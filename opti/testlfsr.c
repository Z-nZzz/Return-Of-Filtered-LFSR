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

// Unit tests
int test_lfsr_init(void) {
    LFSR_t lfsr;
    const uint64_t key[NB_WORD] = {0xDEADBEEFDEADBEEF, 0xCAFEBABECAFEBABE, 0xDEADBEEFDEADBEEF, 0xCAFEBABECAFEBABE,0xDEADBEEFDEADBEEF, 0xCAFEBABECAFEBABE,0xDEADBEEFDEADBEEF, 0xCAFEBABECAFEBABE,0xDEADBEEFDEADBEEF};
    lfsr_init(&lfsr, key);
    //ASSERT_EQUAL_UINT64_ARRAY(key, lfsr.s, NB_WORD);
    for (size_t i = 0; i < NB_WORD; ++i) { 
        if (key[i] != lfsr.s[i]) { 
            printf("Assertion failed at index %zu: expected %lx, got %lx\n", i, key[i],lfsr.s[i]); 
            return 0; 
        } 
    }
    return 1;
}

int test_get_bit(uint64_t *key) {
    LFSR_t lfsr;
    lfsr_init(&lfsr, key);
    ASSERT_EQUAL_UINT8(1, get_bit(&lfsr, 0, 0));
    ASSERT_EQUAL_UINT8(1, get_bit(&lfsr, 1, 0));
    return 1;
}

int test_print_state(uint64_t *key) {
    LFSR_t lfsr;
    lfsr_init(&lfsr, key);
    print_state(&lfsr);
    return 1; // This test is mostly for manual inspection
}

int test_lfsr_sum(uint64_t *key) {
    LFSR_t lfsr;
    lfsr_init(&lfsr, key);
    ASSERT_EQUAL_UINT8(0, lfsr_sum(&lfsr));
    return 1;
}

int test_lfsr_bit(uint64_t *key) {
    LFSR_t lfsr;
    lfsr_init(&lfsr, key);
    ASSERT_EQUAL_UINT8(1, lfsr_bit(&lfsr));
    return 1;
}

int main(void) {
    int result = 1;
    uint64_t key[NB_WORD] = {0xDEADBEEFDEADBEEF, 0xCAFEBABECAFEBABE, 0xDEADBEEFDEADBEEF, 0xCAFEBABECAFEBABE,0xDEADBEEFDEADBEEF, 0xCAFEBABECAFEBABE,0xDEADBEEFDEADBEEF, 0xCAFEBABECAFEBABE,0xDEADBEEFDEADBEEF};
    printf("%lx\n", key[0]); \
    
    printf("Running test_lfsr_init...\n");
    result &= test_lfsr_init();
    printf("Running test_get_bit...\n");
    result &= test_get_bit(key);
    printf("Running test_print_state...\n");
    result &= test_print_state(key);
    printf("Running test_lfsr_sum...\n");
    result &= test_lfsr_sum(key);
    printf("Running test_lfsr_bit...\n");
    result &= test_lfsr_bit(key);
    
    if (result) {
        printf("All tests passed.\n");
    } else {
        printf("Some tests failed.\n");
    }

    return result ? 0 : 1;
}
