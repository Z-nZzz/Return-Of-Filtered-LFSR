#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "lfsr.h"

#define debug 0
#define W_size 64

//Getting the position in a list of W_size words from a list of int
void wpos_from_intpos(uint16_t *p, size_t p_len, uint8_t **res){
    for (size_t i = 0; i < p_len; i++) {
        res[i][0] = p[i]/64; 
        res[i][0] = p[i]%64;    
    }
}

void lfsr_init(LFSR *lfsr, uint64_t *key, size_t key_len, uint16_t *p, size_t p_len) {
    size_t len = 1 + key_len/W_size;
    lfsr->s = (uint64_t*) calloc(len, sizeof(uint64_t));
    if (lfsr->s == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
    }
    for (size_t i = 0; i < len; i++) {
        lfsr->s[i] = key[i];
    }
    
    lfsr->p = malloc(p_len * sizeof(uint8_t*));
    if (lfsr->p == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
    }
    for (size_t i = 0; i < p_len; i++) {
        lfsr->p[i] = malloc(2 * sizeof(uint8_t));
    }
    wpos_from_intpos(p, p_len, lfsr->p);
    lfsr->len = len;
    lfsr->p_len = p_len;
}

//Getting the bit at the position W_size*nw + pw in the LFSR state
uint8_t get_bit(LFSR *lfsr, uint8_t nw, uint8_t pw){
    return (lfsr->s[nw]>>(W_size - pw))%2;
}

void print_state(LFSR *lfsr){
    printf("LFSR state: [ ");
    for (size_t i = 0; i < lfsr->len; i++) {
        printf("%ld", lfsr->s[i]);
    }
    printf(" ]\n"); 
}
//Computing the feedback bit using the feedback polynomial
uint8_t lfsr_sum(LFSR *lfsr) {
    uint8_t s = 0;
    for (size_t i = 0; i < lfsr->p_len; i++) {
        s ^= get_bit(lfsr, lfsr->p[i][0], lfsr->p[i][1]);
    }
    return s;
}
//Updating the lfsr state with the feedback bit and the shift of the registers
uint8_t lfsr_bit(LFSR *lfsr) {
    if (debug){
        print_state(lfsr);
}
    uint8_t b = get_bit(lfsr, lfsr->len - 1, W_size - 1);
    uint8_t new_bit = lfsr_sum(lfsr);

    for (size_t i = lfsr->len - 1; i > 0; i--) {
        uint8_t tmp = get_bit(lfsr, i-1, W_size - 1);
        lfsr->s[i] = (lfsr->s[i] >> 1) | tmp;
    }
    lfsr->s[0] = (lfsr->s[0] >> 1) | new_bit;
    return b;
}

void free_lfsr(LFSR *lfsr){
    free(lfsr->s);
    free(lfsr->p);
}
