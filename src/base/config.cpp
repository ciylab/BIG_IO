#ifndef PAGE_H
#define PAGE_H
#include "config.h"

data values[16][8];

algo algos[8];

void init_data() {
    /* main page */
    values[0][1] = {128, 0, 255, 128};
    values[0][3] = {0, 0, 7, 0};
    values[0][4] = {1, 1, 7, 0};
    /* config page */
    values[1][0] = {0, 0, 7, 0};
    values[1][1] = {0, 0, 17, 0};
    values[1][2] = {0, 0, 27, 0};
    values[1][3] = {0, 0, 8, 0};
}
#endif
