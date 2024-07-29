#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "filter.h"
#include "lfsr.h"


//const uint16_t Taps_tmp[N_FILTER][2] ={{0, 0}, {0, 2}, {0, 5}, {0, 10}, {0, 17}, {0, 28}, {0, 41}, {0, 58}, {1, 13}, {1, 36}, {2, 1}, {2, 32}, {3, 5}, {3, 46}, {4, 25}, {5, 8}, {5, 61}, {6, 56}, {7, 53}, {0, 47}, {1, 54}, {2, 63}, {4, 14}, {5, 33}, {6, 58}, {0, 18}, {1, 55}, {3, 30}, {5, 9}, {6, 54}, {0, 30}, {2, 29}, {4, 32}, {6, 41}, {0, 43}, {3, 0}, {5, 23}, {7, 52}, {2, 14}, {4, 53}, {7, 34}, {2, 12}, {5, 1}, {8, 0}, {2, 56}, {0, 59}, {7, 45}, {3, 7}, {6, 44}, {5, 59}, {1, 35}, {5, 30}, {1, 22}, {5, 29}, {1, 33}, {5, 48}, {1, 60}, {6, 21}, {2, 39}, {7, 12}, {3, 54}, {0, 36}, {2, 17}, {7, 28}, {4, 36}, {7, 19}, {4, 43}, {2, 9}, {7, 56}, {5, 36}, {3, 22}, {1, 12}, {7, 17}, {5, 21}, {3, 29}, {1, 45}, {0, 7}, {5, 18}, {3, 58}, {2, 40}, {1, 26}, {7, 27}, {6, 31}, {5, 37}, {4, 47}, {4, 5}, {3, 35}, {2, 47}, {2, 19}, {3, 1}, {3, 37}, {4, 15}, {4, 63}, {5, 49}, {7, 43}, {0, 42}, {1, 56}, {3, 8}, {4, 30}, {5, 58}, {7, 26}, {0, 51}, {2, 33}, {6, 19}, {0, 8}, {4, 22}, {6, 34}, {0, 49}, {3, 13}, {5, 47}, {0, 16}, {3, 4}, {6, 0}, {0, 61}, {4, 11}, {7, 31}, {2, 48}, {6, 14}, {1, 43}, {0, 62}, {4, 54}, {4, 51}, {6, 35}, {7, 58}, {4, 37}, {6, 38}, {3, 45}, {0, 54}};

const int_t Taps[NB_WORD] = {7803205505086064037,1279066386378797056,9295853506047660546,306350501190967731,9252795179579000864,3171519516457042690, 378322488476057601, 373842769334636544,1};


/*
Cyclic Weightwise degree d Boolean function for Filter_t generators using LFSR

:param filter: instance of the Filter_t structure from filter.h
:param key: the initial state of the LFSR, 
:param g: the base function of our filter with a structure of a list of monomial ending with a -1, for instance g(x) = x1 + x2x3 would give g = [[0, -1], [1, 2, -1]], the -1 is used to know that the list is over as we do not necessarilly have monomials of the same degree,
*/
void filter_init(Filter_t *filter, int_t *key, int **g, size_t g_len) {
    lfsr_init(filter->lfsr, key);
    filter->g = g;
    filter->g_len = g_len;
}
//Generating one bit of keystream with the filter function and the state of the LFSR that is also updated
uint8_t filter_bit(Filter_t *filter) {
    int_t state[N_FILTER] = {0};
    //Getting the variables for our filter from the LFSR state
    for (size_t i = 0; i < NB_WORD; i++) {
        state[i] = Taps[i] & (filter->lfsr->s[i]);
        //printf("%d", state[i]);
    }
    //printf("\n");
    uint8_t hw = 0;
    //Computing the hamming weight:
    for (size_t i = 0; i < N_FILTER; i++) {
        hw += state[i];
    }
    uint8_t b = 0;
    for (size_t i = 0; i < filter->g_len; i++) {
        uint8_t tmp = 1;
        int j = 0;
        int current = filter->g[i][j];
        while (current != -1){   
            size_t k = (current + hw) % N_FILTER;
            tmp *= state[k];
            j ++;
            current = filter->g[i][j];
            //printf("%d", current);
        }
        b ^= tmp;
    }
    lfsr_bit(filter->lfsr);
    return b;
}

//Generating a byte by calling 8 times filter_bit
uint8_t filter_byte(Filter_t *filter) {
    uint8_t byte = 0;
    for (size_t i = 0; i < 8; i++) {
        uint8_t bit = filter_bit(filter);
        byte += bit << (7 - i);
    }
    return byte;
}
/*void gen_taps(size_t N, size_t n, uint8_t **res){
    uint16_t taps[] = {0, 2, 5, 10, 17, 28, 41, 58, 77, 100, 129, 160, 197, 238, 281, 328, 381, 440, 501, 568, 639, 712, 791, 874, 963, 1060, 1161, 1264, 1371, 1480, 1593, 1720, 1851, 1988, 2127, 2276, 2427, 2584, 2747, 2914, 3087, 3266, 3447, 3638, 3831, 4028, 4227, 4438, 4661, 4888, 5117, 5350, 5589, 5830, 6081, 6338, 6601, 6870, 7141, 7418, 7699, 7982, 8275, 8582, 8893, 9206, 9523, 9854, 10191, 10538, 10887, 11240, 11599, 11966, 12339, 12718, 13101, 13490, 13887, 14288, 14697, 15116, 15537, 15968, 16401, 16840, 17283, 17732, 18189, 18650, 19113, 19580, 20059, 20546, 21037, 21536, 22039, 22548, 23069, 23592, 24133, 24680, 25237, 25800, 26369, 26940, 27517, 28104, 28697, 29296, 29897, 30504, 31117, 31734, 32353, 32984, 33625, 34268, 34915, 35568, 36227, 36888, 37561, 38238, 38921, 39612, 40313, 41022, 41741, 42468, 43201, 43940, 44683, 45434, 46191, 46952, 47721, 48494, 49281, 50078, 50887, 51698, 52519, 53342, 54169, 54998, 55837, 56690, 57547, 58406};
    //uint16_t taps[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997, 1009, 1013, 1019, 1021};

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
