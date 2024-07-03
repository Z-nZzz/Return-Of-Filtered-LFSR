#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "filter.h"
#include "lfsr.h"

/*
Cyclic Weightwise degree d Boolean function for Filter generators using LFSR

:param filter: instance of the Filter structure from filter.h
:param key: the initial state of the LFSR, 
:param P: the feedback polynomial of the LFSR, 
:param g: the base function of our filter with a structure of a list of monomial ending with a -1, for instance g(x) = x1 + x2x3 would give g = [[0, -1], [1, 2, -1]], the -1 is used to know that the list is over as we do not necessarilly have monomials of the same degree,
:param n: amount of variables taken by the filter function, 
:param taps: list of positions of the taps where the function will take it's variables, 
*/

void filter_init(Filter *filter, uint8_t *key, size_t key_len, uint16_t *P, size_t P_len, int **g, size_t g_len, size_t n, uint16_t *taps) {
    lfsr_init(&filter->lfsr, key, key_len, P, P_len);
    filter->N = key_len;
    filter->g = g;
    filter->g_len = g_len;
    filter->n = n;
    filter->taps = taps;
}
//Generating one bit of keystream with the filter function and the state of the LFSR that is also updated
uint8_t filter_bit(Filter *filter) {
    uint8_t state[filter->n];
    //Getting the variables for our filter from the LFSR state
    for (size_t i = 0; i < filter->n; i++) {
        state[i] = filter->lfsr.s[filter->taps[i]%filter->N];
        //printf("%d", state[i]);
    }
    //printf("\n");
    uint8_t hw = 0;
    //Computing the hamming weight:
    for (size_t i = 0; i < filter->n; i++) {
        hw += state[i];
    }
    uint8_t b = 0;
    for (size_t i = 0; i < filter->g_len; i++) {
        uint8_t tmp = 1;
        int j = 0;
        int current = filter->g[i][j];
        while (current != -1){   
            size_t k = (current + hw) % filter->n;
            tmp *= state[k];
            j ++;
            current = filter->g[i][j];
            //printf("%d", current);
        }
        b ^= tmp;
    }
    lfsr_bit(&filter->lfsr);
    return b;
}

//Generating a byte by calling 8 times filter_bit
uint8_t filter_byte(Filter *filter) {
    uint8_t byte = 0;
    for (size_t i = 0; i < 8; i++) {
        uint8_t bit = filter_bit(filter);
        byte += bit << (7 - i);
    }
    return byte;
}
void free_filter(Filter *filter){
    free_lfsr(&filter->lfsr);
}

