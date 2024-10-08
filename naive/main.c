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
    filter_init(&filter, key, N, P, sizeof(P) / sizeof(P[0]), g, g_len, n);

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

