#include <stdio.h>

typedef unsigned CARDINAL;
#define CPT "u" // CARDINAL Printf Type (without %)
//typedef unsigned long long CARDINAL;
//#define CPT "llu" // CARDINAL Printf Type (without %)

CARDINAL combination(CARDINAL n, CARDINAL k) {
    if (k > n / 2) {
        k = n - k;
    }
    CARDINAL result = 1;
    for (CARDINAL i = 1; i <= k; i++) {
        result = result * (n - k + i) / i;
    }
    return result;
}

int main() {
    printf("%"CPT"\n", combination(129, 60));
    return 0;
}
