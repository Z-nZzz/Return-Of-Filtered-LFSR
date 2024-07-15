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
    uint16_t *taps;
} Filter;

void filter_init(Filter *filter, uint8_t *key, size_t key_len, uint16_t *P, size_t P_len, int **g, size_t g_len,size_t n);
uint8_t filter_bit(Filter *filter);
uint8_t filter_byte(Filter *filter);
void free_filter(Filter *filter);
#endif /* FILTER_H */

