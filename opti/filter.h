#ifndef FILTER_H
#define FILTER_H

#include <stddef.h>
#include <stdint.h>
#include "lfsr.h"

#define G_LEN 2
#define GET_BIT(filter, nw, pw) \
    ((filter->lfsr->s[nw])>>(W_SIZE - pw))%2

extern uint8_t G[G_LEN][3];

//const uint16_t Taps[N_FILTER][2] ={{0, 0}, {0, 2}, {0, 5}, {0, 10}, {0, 17}, {0, 28}, {0, 41}, {0, 58}, {1, 13}, {1, 36}, {2, 1}, {2, 32}, {3, 5}, {3, 46}, {4, 25}, {5, 8}, {5, 61}, {6, 56}, {7, 53}, {0, 47}, {1, 54}, {2, 63}, {4, 14}, {5, 33}, {6, 58}, {0, 18}, {1, 55}, {3, 30}, {5, 9}, {6, 54}, {0, 30}, {2, 29}, {4, 32}, {6, 41}, {0, 43}, {3, 0}, {5, 23}, {7, 52}, {2, 14}, {4, 53}, {7, 34}, {2, 12}, {5, 1}, {8, 0}, {2, 56}, {0, 59}, {7, 45}, {3, 7}, {6, 44}, {5, 59}, {1, 35}, {5, 30}, {1, 22}, {5, 29}, {1, 33}, {5, 48}, {1, 60}, {6, 21}, {2, 39}, {7, 12}, {3, 54}, {0, 36}, {2, 17}, {7, 28}, {4, 36}, {7, 19}, {4, 43}, {2, 9}, {7, 56}, {5, 36}, {3, 22}, {1, 12}, {7, 17}, {5, 21}, {3, 29}, {1, 45}, {0, 7}, {5, 18}, {3, 58}, {2, 40}, {1, 26}, {7, 27}, {6, 31}, {5, 37}, {4, 47}, {4, 5}, {3, 35}, {2, 47}, {2, 19}, {3, 1}, {3, 37}, {4, 15}, {4, 63}, {5, 49}, {7, 43}, {0, 42}, {1, 56}, {3, 8}, {4, 30}, {5, 58}, {7, 26}, {0, 51}, {2, 33}, {6, 19}, {0, 8}, {4, 22}, {6, 34}, {0, 49}, {3, 13}, {5, 47}, {0, 16}, {3, 4}, {6, 0}, {0, 61}, {4, 11}, {7, 31}, {2, 48}, {6, 14}, {1, 43}, {0, 62}, {4, 54}, {4, 51}, {6, 35}, {7, 58}, {4, 37}, {6, 38}, {3, 45}, {0, 54}};

typedef struct {
    LFSR_t *lfsr;
    uint8_t taps_cpl[NB_WORD][2];
    uint8_t taps[NB_WORD];
} Filter_t;

//void gen_taps(size_t N, size_t n, uint8_t **res);

void filter_init(Filter_t *filter, LFSR_t *lfsr, int_t *key);

uint8_t filter_bit(Filter_t *filter);

uint8_t filter_byte(Filter_t *filter);

void free_filter(Filter_t *filter);

#endif /* FILTER_H */

