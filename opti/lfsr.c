#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "lfsr.h"

#define debug 0

const uint16_t POLY[P_LEN][2] =  {{31/W_SIZE, 31 % W_SIZE}, {520/W_SIZE, 520 % W_SIZE}};

void lfsr_init(LFSR_t *lfsr, uint64_t *key) {
    for (size_t i = 0; i < N_LFSR; i++) {
        lfsr->s[i] = key[i];
    }
}

//Getting the bit at the position W_SIZE*nw + pw in the LFSR_t state
uint8_t get_bit(LFSR_t *lfsr, uint16_t nw, uint16_t pw){
    return ((lfsr->s[nw])>>(W_SIZE - pw))%2;
}

void print_state(LFSR_t *lfsr){
    printf("LFSR_t state: [ ");
    for (size_t i = 0; i < N_LFSR; i++) {
        printf("%ld", lfsr->s[i]);
    }
    printf(" ]\n"); 
}
//Computing the feedback bit using the feedback polynomial
uint8_t lfsr_sum(LFSR_t *lfsr) {
    uint8_t s = 0;
    for (size_t i = 0; i < P_LEN; i++) {
        s ^= get_bit(lfsr, POLY[i][0], POLY[i][1]);
    }
    return s;
}
//Updating the lfsr state with the feedback bit and the shift of the registers
uint8_t lfsr_bit(LFSR_t *lfsr) {
    if (debug){
        print_state(lfsr);
}
    uint8_t b = get_bit(lfsr, N_LFSR - 1, W_SIZE - 1);
    uint8_t new_bit = lfsr_sum(lfsr);

    for (size_t i = N_LFSR - 1; i > 0; i--) {
        uint8_t tmp = get_bit(lfsr, i-1, W_SIZE - 1);
        lfsr->s[i] = (lfsr->s[i] >> 1) | tmp;
    }
    lfsr->s[0] = (lfsr->s[0] >> 1) | new_bit;
    return b;
}

