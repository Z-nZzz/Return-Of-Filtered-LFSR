#ifndef LFSR_H
#define LFSR_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint64_t *s;
    uint8_t **p;
    size_t len;
    size_t p_len;
} LFSR;

void lfsr_init(LFSR *lfsr, uint64_t *key, size_t key_len, uint16_t *p, size_t p_len);

void print_state(LFSR *lfsr);

uint8_t lfsr_sum(LFSR *lfsr);

uint8_t lfsr_bit(LFSR *lfsr);

uint8_t get_bit(LFSR *lfsr, uint8_t nw, uint8_t pw);

void free_lfsr(LFSR *lfsr);

#endif /* LFSR_H */
