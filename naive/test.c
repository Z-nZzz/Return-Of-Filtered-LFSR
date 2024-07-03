#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "filter.h"

#define N 512

int main() {
    //List of all the primes lower than 1024
    uint16_t taps[172] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997, 1009, 1013, 1019, 1021};
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
    filter_init(&filter, key, key_len, P, P_len, g, g_len, n, taps);
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

