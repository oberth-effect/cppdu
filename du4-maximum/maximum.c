#include "maximum.h"


int *get_maximum(int *start, int *past_end) {
    if (!start || !past_end) {
        return 0;
    }

    if (start == past_end) {
        return 0;
    }

    int *res = start;
    for (int *p = start; p < past_end; p++) {
        if (*p > *res) {
            res = p;
        }
    }
    return res;
}