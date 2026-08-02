#ifndef PAGE_H
#define PAGE_H
#include "config.h"


data values[16][8];

void init_data() {
/* main page */
    values[0][1] = {0, -10, 10, 0};
    values[0][3] = {1, 1, 8, 1};
    values[0][4] = {1, 1, 8, 1};
    values[1][0] = {1, 1, 8, 1};
}

#endif
