#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "filter.h"
#include "lfsr.h"


int G[2][3] = { {0, -1, -1}, {1, 2, -1} };

/*
Cyclic Weightwise degree d Boolean function for Filter_t generators using LFSR

:param filter: instance of the Filter_t structure from filter.h
:param key: the initial state of the LFSR, 
:param g: the base function of our filter with a structure of a list of monomial ending with a -1, for instance g(x) = x0 + x1x2 would give g = [[0, -1], [1, 2, -1]], the -1 is used to know that the list is over as we do not necessarilly have monomials of the same degree,
*/

void filter_init(Filter_t *filter, LFSR_t *lfsr, int_t *key) {
    size_t i;
    lfsr_init(lfsr, key);
    filter->lfsr = lfsr; 
    if (W_SIZE == 64){
        uint8_t Taps_cpl[N_FILTER][2] ={{0, 0}, {0, 2}, {0, 4}, {0, 5}, {0, 8}, {0, 10}, {0, 14}, {0, 16}, {0, 17}, {0, 18}, {0, 28}, {0, 30}, {0, 36}, {0, 41}, {0, 42}, {0, 43}, {0, 46}, {0, 47}, {0, 51}, {0, 54}, {0, 58}, {0, 62}, {1, 9}, {1, 13}, {1, 18}, {1, 24}, {1, 25}, {1, 31}, {1, 33}, {1, 36}, {1, 40}, {1, 43}, {1, 54}, {1, 55}, {2, 1}, {2, 11}, {2, 12}, {2, 14}, {2, 18}, {2, 25}, {2, 29}, {2, 32}, {2, 36}, {2, 38}, {2, 55}, {2, 56}, {2, 58}, {2, 63}, {3, 0}, {3, 2}, {3, 4}, {3, 5}, {3, 7}, {3, 14}, {3, 15}, {3, 29}, {3, 30}, {3, 36}, {3, 45}, {3, 46}, {3, 50}, {3, 52}, {3, 54}, {3, 59}, {4, 1}, {4, 7}, {4, 8}, {4, 10}, {4, 14}, {4, 17}, {4, 25}, {4, 32}, {4, 38}, {4, 40}, {4, 44}, {4, 53}, {4, 57}, {5, 1}, {5, 4}, {5, 7}, {5, 8}, {5, 9}, {5, 12}, {5, 23}, {5, 27}, {5, 33}, {5, 35}, {5, 37}, {5, 47}, {5, 57}, {5, 61}, {5, 62}, {5, 63}, {6, 1}, {6, 13}, {6, 19}, {6, 23}, {6, 29}, {6, 40}, {6, 41}, {6, 45}, {6, 46}, {6, 53}, {6, 54}, {6, 55}, {6, 56}, {6, 58}, {6, 62}, {6, 63}, {7, 0}, {7, 1}, {7, 3}, {7, 8}, {7, 16}, {7, 17}, {7, 23}, {7, 24}, {7, 28}, {7, 32}, {7, 33}, {7, 34}, {7, 46}, {7, 52}, {7, 53}, {7, 54}, {8, 0}, {8, 1}, {8, 8}};

        int_t Taps[NB_WORD] = {7803205505086064037,1279066386378797056,9295853506047660546,306350501190967731,9252795179579000864,3171519516457042690, 378322488476057601, 373842769334636544,1};
        memcpy(filter->taps, Taps, NB_WORD*sizeof(int_t));
        for (i = 0; i < N_FILTER; i++){
            memcpy(filter->taps_cpl[i], Taps_cpl[i], 2*sizeof(uint8_t));
        }
    }
    if (W_SIZE == 32){
        uint8_t Taps_cpl[N_FILTER][2] = {{0, 0}, {0, 2}, {0, 4}, {0, 5}, {0, 8}, {0, 10}, {0, 14}, {0, 16}, {0, 17}, {0, 18}, {0, 28}, {0, 30}, {1, 4}, {1, 9}, {1, 10}, {1, 11}, {1, 14}, {1, 15}, {1, 19}, {1, 22}, {1, 26}, {1, 30}, {2, 9}, {2, 13}, {2, 18}, {2, 24}, {2, 25}, {2, 31}, {3, 1}, {3, 4}, {3, 8}, {3, 11}, {3, 22}, {3, 23}, {4, 1}, {4, 11}, {4, 12}, {4, 14}, {4, 18}, {4, 25}, {4, 29}, {5, 0}, {5, 4}, {5, 6}, {5, 23}, {5, 24}, {5, 26}, {5, 31}, {6, 0}, {6, 2}, {6, 4}, {6, 5}, {6, 7}, {6, 14}, {6, 15}, {6, 29}, {6, 30}, {7, 4}, {7, 13}, {7, 14}, {7, 18}, {7, 20}, {7, 22}, {7, 27}, {8, 1}, {8, 7}, {8, 8}, {8, 10}, {8, 14}, {8, 17}, {8, 25}, {9, 0}, {9, 6}, {9, 8}, {9, 12}, {9, 21}, {9, 25}, {10, 1}, {10, 4}, {10, 7}, {10, 8}, {10, 9}, {10, 12}, {10, 23}, {10, 27}, {11, 1}, {11, 3}, {11, 5}, {11, 15}, {11, 25}, {11, 29}, {11, 30}, {11, 31}, {12, 1}, {12, 13}, {12, 19}, {12, 23}, {12, 29}, {13, 8}, {13, 9}, {13, 13}, {13, 14}, {13, 21}, {13, 22}, {13, 23}, {13, 24}, {13, 26}, {13, 30}, {13, 31}, {14, 0}, {14, 1}, {14, 3}, {14, 8}, {14, 16}, {14, 17}, {14, 23}, {14, 24}, {14, 28}, {15, 0}, {15, 1}, {15, 2}, {15, 14}, {15, 20}, {15, 21}, {15, 22}, {16, 0}, {16, 1}, {16, 8}};
        int_t Taps[NB_WORD] = {1342653749, 1145622032, 2198086144, 12585234, 570710018, 2239758417, 1610662069, 139747344, 33703298, 35656001, 142611346, 3791683626, 545792002, 3319816960, 293798155, 7356423, 259};
        
        memcpy(filter->taps, Taps, NB_WORD*sizeof(int_t));
        for (i = 0; i < N_FILTER; i++){
            memcpy(filter->taps_cpl[i], Taps_cpl[i], 2*sizeof(uint8_t));
        }
    }

}
//Generating one bit of keystream with the filter function and the state of the LFSR that is also updated
uint8_t filter_bit(Filter_t *filter) {
    uint8_t *k;
    uint8_t hw;
    size_t i;
    size_t j;
    uint8_t b;
    uint8_t tmp;
    uint8_t current = 0;
    unsigned int v;
    unsigned int c;
    //int g[2][3] = G;

    int_t state[N_FILTER];
    //Getting the variables for our filter from the LFSR state
    for (i = 0; i < NB_WORD; i++) {
        state[i] = filter->taps[i] & (filter->lfsr->s[i]);
        printf("%d\n", state[i]);
    }
    //printf("\n");
    hw = 0;
    //Computing the hamming weight:
    for (i = 0; i < NB_WORD; i++) {
        v = state[i];
        v = v - ((v >> 1) & 0x55555555);                    // reuse input as temporary
        v = (v & 0x33333333) + ((v >> 2) & 0x33333333);     // temp
        c = ((v + ((v >> 4) & 0xF0F0F0F)) * 0x1010101) >> 24; // count
        hw += c;
    }
    b = 0;
    for (i = 0; i < G_LEN; i++) {
        tmp = 1;
        j = 0;
        current = G[i][j];
        while (current != 255){   
            k = filter->taps_cpl[(current + hw) % N_FILTER];
            tmp = tmp * GET_BIT(filter, k[0], k[1]);
            j ++;
            current = G[i][j];
        }
        b ^= tmp;
    }
    lfsr_bit(filter->lfsr);
    printf("%d\n", b);
    return b;
}

//Generating a byte by calling 8 times filter_bit
uint8_t filter_byte(Filter_t *filter) {
    uint8_t byte = 0;
    uint8_t bit;
    size_t i;
    for (i = 0; i < 8; i++) {
        bit = filter_bit(filter);
        byte += bit << (7 - i);
    }
    return byte;
}







/*void gen_taps(size_t N, size_t n, uint8_t **res){
    uint16_t taps[] = {0, 2, 5, 10, 17, 28, 41, 58, 77, 100, 129, 160, 197, 238, 281, 328, 381, 440, 501, 568, 639, 712, 791, 874, 963, 1060, 1161, 1264, 1371, 1480, 1593, 1720, 1851, 1988, 2127, 2276, 2427, 2584, 2747, 2914, 3087, 3266, 3447, 3638, 3831, 4028, 4227, 4438, 4661, 4888, 5117, 5350, 5589, 5830, 6081, 6338, 6601, 6870, 7141, 7418, 7699, 7982, 8275, 8582, 8893, 9206, 9523, 9854, 10191, 10538, 10887, 11240, 11599, 11966, 12339, 12718, 13101, 13490, 13887, 14288, 14697, 15116, 15537, 15968, 16401, 16840, 17283, 17732, 18189, 18650, 19113, 19580, 20059, 20546, 21037, 21536, 22039, 22548, 23069, 23592, 24133, 24680, 25237, 25800, 26369, 26940, 27517, 28104, 28697, 29296, 29897, 30504, 31117, 31734, 32353, 32984, 33625, 34268, 34915, 35568, 36227, 36888, 37561, 38238, 38921, 39612, 40313, 41022, 41741, 42468, 43201, 43940, 44683, 45434, 46191, 46952, 47721, 48494, 49281, 50078, 50887, 51698, 52519, 53342, 54169, 54998, 55837, 56690, 57547, 58406};

    uint8_t tmp[2];
    int c = 0;
    int i = 0;
    //Collecting n distinct tap position modulo N from taps
    while (i < n){
        tmp[0] = (taps[i+c] % N) / 64;
        tmp[1] = (taps[i+c] % N) % 64;
        uint8_t is_uniq = 1;
        //Figuring out if the tap position is already in res
        for (int k = 0; k < i; k++){
            if (tmp[0] == res[k][0]){
                c ++;
                is_uniq = 0;
                break;
            }
        }
        if(is_uniq){
            res[i] = tmp;
            i ++;
            }
    }
}
*/
