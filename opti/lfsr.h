#ifndef LFSR_H
#define LFSR_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint64_t *s;
    uint8_t **p;
    size_t len;
    size_t p_len;
} LFSR_t;

void lfsr_init(LFSR_t *lfsr, uint64_t *key, size_t key_len, uint16_t *p, size_t p_len);

uint8_t get_bit(LFSR_t *lfsr, uint8_t nw, uint8_t pw);

void print_state(LFSR_t *lfsr);

uint8_t lfsr_sum(LFSR_t *lfsr);

uint8_t lfsr_bit(LFSR_t *lfsr);

uint8_t get_bit(LFSR_t *lfsr, uint8_t nw, uint8_t pw);

void free_lfsr(LFSR_t *lfsr);

#endif /* LFSR_H */
