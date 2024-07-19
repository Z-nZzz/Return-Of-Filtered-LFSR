#ifndef FILTER_H
#define FILTER_H

#include <stddef.h>
#include <stdint.h>
#include "lfsr.h"

typedef struct {
    LFSR lfsr;
    size_t N;
    int **g;
    size_t g_len;
    size_t n;
    uint8_t**taps;
} Filter_t;

void gen_taps(size_t N, size_t n, uint8_t **res);

void filter_init(Filter_t *filter, uint64_t *key, size_t key_len, uint16_t *P, size_t P_len, int **g, size_t g_len,size_t n);

uint8_t filter_bit(Filter_t *filter);

uint8_t filter_byte(Filter_t *filter);

void free_filter(Filter_t *filter);

#endif /* FILTER_H */

