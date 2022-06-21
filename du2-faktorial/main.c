#include <stdio.h>

//typedef unsigned CARDINAL;
//#define CPT "u" // CARDINAL Printf Type (without %)
typedef unsigned long long CARDINAL;
#define CPT "llu" // CARDINAL Printf Type (without %)

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
    for (int n = 1; n < 200; n += 10) {
        for (int k = 1; k < n; k += 10) {
            printf("n=%d, k=%d: ", n, k);
            printf("%"CPT" == %"CPT" %s\n", combination(n + 1, k + 1), combination(n, k + 1) + combination(n, k),
                   combination(n + 1, k + 1) == combination(n, k + 1) + combination(n, k) ? "true" : "false");
        }
    }
    return 0;
}
