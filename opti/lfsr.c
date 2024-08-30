#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lfsr.h"

#define debug 0
#define GET_BIT(lfsr, nw, pw) \
    ((lfsr->s[nw])>>(W_SIZE - pw))%2



void lfsr_init(LFSR_t *lfsr, int_t *key) {
    for (size_t i = 0; i < N_LFSR; i++) {
        lfsr->s[i] = key[i];
    }
}

/*Getting the bit at the position W_SIZE*nw + pw in the LFSR_t state
uint8_t get_bit(LFSR_t *lfsr, uint16_t nw, uint8_t pw){
    return ((lfsr->s[nw])>>(W_SIZE - pw))%2;
}*/

void print_state(LFSR_t *lfsr){
    printf("LFSR_t state: [ ");
    for (size_t i = 0; i < N_LFSR; i++) {
        printf("%lx", lfsr->s[i]);
    }
    printf(" ]\n"); 
}
//Computing the feedback bit using the feedback polynomial
uint8_t lfsr_sum(LFSR_t *lfsr) {
    const uint8_t POLY[P_LEN][2] =  {{0, 0}, {5/W_SIZE,  5% W_SIZE}, {18/W_SIZE,  18% W_SIZE}, {1023/W_SIZE,  1023% W_SIZE}};
    uint8_t s = 0;

    for (size_t i = 0; i < P_LEN; i++) {
        //printf("%d\n", GET_BIT(lfsr, POLY[i][0], POLY[i][1]));
        s ^= GET_BIT(lfsr, POLY[i][0], POLY[i][1]);
    }
    return s;
}
//Updating the lfsr state with the feedback bit and the shift of the registers
void lfsr_bit(LFSR_t *lfsr) {
    const int_t endianness = pow(2, W_SIZE - 1);
    uint8_t new_bit;
    uint8_t tmp;

    if (debug){
        print_state(lfsr);
}
    //uint8_t b = GET_BIT(lfsr, NB_WORD - 1, LAST_BIT_POS);
    new_bit = lfsr_sum(lfsr);

    for (size_t i = N_LFSR - 1; i > 0; i--) {
        tmp = GET_BIT(lfsr, i-1, W_SIZE - 1);
        lfsr->s[i] = (lfsr->s[i] >> 1) | tmp;
    }
    lfsr->s[0] = (lfsr->s[0] >> 1) | new_bit * endianness;
    //return b;
}

