#ifndef LFSR_H
#define LFSR_H

#include <stddef.h>
#include <stdint.h>

#define N_LFSR 521
#define W_SIZE 64
#define NB_WORD (1 + N_LFSR / W_SIZE)
#define N_FILTER 128
#define P_LEN 2

//const uint16_t POLY[P_LEN][2] =  {{31/W_SIZE, 31 % W_SIZE}, {520/W_SIZE, 520 % W_SIZE}};

typedef struct {
    uint64_t s[NB_WORD];
} LFSR_t;

void lfsr_init(LFSR_t *lfsr, uint64_t *key);

uint8_t get_bit(LFSR_t *lfsr, uint16_t nw, uint16_t pw);

void print_state(LFSR_t *lfsr);

uint8_t lfsr_sum(LFSR_t *lfsr);

uint8_t lfsr_bit(LFSR_t *lfsr);

void free_lfsr(LFSR_t *lfsr);

#endif /* LFSR_H */
