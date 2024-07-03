#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "filter.h"

//#define N 512
#define N 1024
//#define N 2048
#define n 128
//100Ko
#define stream_len 800000

int main() {
    //Our feedback polynomial 
    //uint16_t P[] = {1, 4, 7, 511};
    uint16_t P[] = {5, 18, 1023};
    //uint16_t P[] = {0, 12, 13, 18, 2047};
    //List of all the primes lower than 1024
    uint16_t taps[172] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997, 1009, 1013, 1019, 1021};
    //Initialising the key and initial state of our LFSR
    uint8_t* key = calloc(N, sizeof(uint8_t));
    if (key == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
    return 1;
}
    //Picking a random key for testing purpose
    for (size_t i = 0; i < N; i++) {
        key[i] = rand() % 2;
        //printf("%d\n", key[i]);
    }
    //printing the key
    double nkey = 0;
    for (size_t i = 0; i < N; i++) {
        nkey += pow(2,(N - 1 - i)) * key[i];
        //printf("%f\n", key[i]);
    }

    printf("key: %f\n", nkey);
    
   /* 
    //Our Cyclic weightwise quadratic function base g = u
    int **g = malloc(n / 2 * sizeof(int *));
    if (g == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
    return 1;
    }

    g[0] = malloc(2 * sizeof(int));
    if (g[0] == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(g[0]);
        return 1;
    }
    g[0][0] = 0;
    g[0][1] = -1;

    for (int i = 1; i < 1 + (n - 1) / 2; i++) {
        g[i] = malloc(3 * sizeof(int));
        if (g[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            for (int j = 0; j < i; j++) {
                free(g[j]);
            }
            free(g);
            return 1;
        }
        g[i][0] = 2 * i - 1;
        g[i][1] = 2 * i;
        g[i][2] = -1;
    }
    size_t g_len = n/2;
*/
 //Our Cyclic weightwise quadratic function base g = t = x_0 + x_1x_2
    int **g = malloc(2 * sizeof(int *));
    if (g == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
    return 1;
    }

    g[0] = malloc(2 * sizeof(int));
    if (g[0] == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(g[0]);
        free(g);
        return 1;
    }
    g[0][0] = 0;
    g[0][1] = -1;
    
    g[1] = malloc(3 * sizeof(int));
    if (g[1] == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(g[1]);
        free(g);
        return 1;
        }
    g[1][0] = 1;
    g[1][1] = 2;
    g[1][2] = -1;
    size_t g_len = 2;

    //Init and then use of the filter
    Filter filter;
    filter_init(&filter, key, N, P, sizeof(P) / sizeof(P[0]), g, g_len, n, taps);

    clock_t start_time = clock();
    uint8_t keystream[stream_len];
    for (size_t i = 0; i < stream_len; i++) {
        keystream[i] = filter_bit(&filter);
        //printf("%d", keystream[i]);
    }
    clock_t end_time = clock();


    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Execution time to generate 100Ko of keystream: %.6f seconds\n", execution_time);
   
    for (int i = 0; i < g_len; i++) {
        free(g[i]);
    }
    free(g);
    free(key);
    free_filter(&filter);
    return 0;
}

