#ifndef LFSR_H
#define LFSR_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint8_t *s;
    uint16_t *p;
    size_t len;
    size_t p_len;
} LFSR;

void lfsr_init(LFSR *lfsr, uint8_t *key, size_t key_len, uint16_t *p, size_t p_len);
void print_state(LFSR *lfsr);
uint8_t lfsr_sum(LFSR *lfsr);
//uint8_t lfsr_clock(LFSR *lfsr);
uint8_t lfsr_bit(LFSR *lfsr);
void free_lfsr(LFSR *lfsr);

#endif /* LFSR_H */
