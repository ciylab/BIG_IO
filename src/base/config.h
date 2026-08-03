#ifndef CONFIG_H
#define CONFIG_H

typedef struct data {
    int val;
    int min;
    int max;
    int buffer;
} data;

typedef struct algo {
    int in;
    int out;
    int action_num;
} algo;

void init_data();
#endif
