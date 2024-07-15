#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "lfsr.h"

#define debug 0

void lfsr_init(LFSR *lfsr, uint8_t *key, size_t key_len, uint16_t *p, size_t p_len) {
    lfsr->s = (uint8_t*) calloc(key_len, sizeof(uint8_t));
    if (lfsr->s == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
    }
    for (size_t i = 0; i < key_len; i++) {
        lfsr->s[i] = key[i];
    }
    lfsr->p = p;
    lfsr->len = key_len;
    lfsr->p_len = p_len;
}

void print_state(LFSR *lfsr){
    printf("LFSR state: [ ");
    for (size_t i = 0; i < lfsr->len; i++) {
        printf("%d", lfsr->s[i]);
    }
    printf(" ]\n"); 
}
//Computing the feedback bit using the feedback polynomial
uint8_t lfsr_sum(LFSR *lfsr) {
    uint8_t s = 0;
    for (size_t i = 0; i < lfsr->p_len; i++) {
        s ^= lfsr->s[lfsr->p[i]];
    }
    return s;
}
//Updating the lfsr state with the feedback bit and the shift of the registers
uint8_t lfsr_bit(LFSR *lfsr) {
    if (debug){
        print_state(lfsr);
}
    uint8_t b = lfsr->s[lfsr->len - 1];
    uint8_t new_bit = lfsr_sum(lfsr);
    for (size_t i = lfsr->len - 1; i > 0; i--) {
        lfsr->s[i] = lfsr->s[i-1];
    }
    //lfsr->s = lfsr->s - sizeof(uint8_t);
    lfsr->s[0] = new_bit;
    return b;
}

void free_lfsr(LFSR *lfsr){
    free(lfsr->s);
}
