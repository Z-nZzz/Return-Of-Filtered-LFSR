#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "filter.h"

#define N 512

int main() {
    uint8_t key[] = {1, 0, 0, 1};
    size_t key_len = 4;
    uint16_t P[] = {1, 3};
    size_t P_len = 2;
    size_t g_len = 2;

    // Test LFSR functions
    LFSR lfsr;
    lfsr_init(&lfsr, key, key_len, P, P_len);
    for (int i = 0; i<0; i++){
        printf("LFSR sum: %d\n", lfsr_sum(&lfsr));
        printf("LFSR bit: %d\n", lfsr_bit(&lfsr));
}
    free_lfsr(&lfsr);
    
// Test Filter functions
    int **g = malloc(2 * sizeof(int *));
    g[0] = malloc (2 * sizeof(int));
    g[1] = malloc (3 * sizeof(int));
    g[0][0] = 0;
    g[0][1] = -1;
    g[1][0] = 2;
    g[1][1] = 1;
    g[1][2] = -1;
    //int **g = {{0, -1}, {1, 2, -1}};
    size_t n = 3;
    Filter filter;
    filter_init(&filter, key, key_len, P, P_len, g, g_len, n);
    for (int i = 0; i<18; i++){
        printf("%d\n", filter_bit(&filter));
        //printf("Filter byte: %d\n", filter_byte(&filter));
}
    
    free_filter(&filter);
    for (int i = 0; i < 2; i++) {
        free(g[i]);
    }
    free(g);
    return 0;
}

