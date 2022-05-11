#include <iostream>
#include <stdlib.h>
#include <time.h>

//typedef double             DATA_TYPE; // Jeden z těchto dvou řádků
typedef unsigned long long DATA_TYPE;   // odkomentujeme.

#define kibi 1024              // kilo binary (IEC)
#define mebi (1024*kibi)       // mega binary (IEC)
#define giga (1000*1000*1000)  // giga (SI)

const int SIZE = 256 * mebi;     // max. testovaná velikost pole v bytech
const int ARRAY_SIZE = SIZE / sizeof(DATA_TYPE);
const int REP = 32;              // počet opakování čtení pole, při ladení lze zmenšit

void measure(volatile DATA_TYPE *p, const int n_elements, const int rep, double &throughput) {
    DATA_TYPE sum;
    volatile DATA_TYPE save_sum;
    clock_t start, end;
    start = clock();
    for (int r = 0; r < rep; r++) {
        sum = 0.0;
        for (int i = 0; i < n_elements; i++) {
            sum += p[i];
        }
    }
    end = clock();
//    save_sum = sum;
    throughput = double(n_elements * sizeof(DATA_TYPE) * rep) / double(end - start);

}

int main() {
    DATA_TYPE *pole = new DATA_TYPE[ARRAY_SIZE];
    std::fill(pole, pole + ARRAY_SIZE, 1.00000000123456789);
    double tp;

    printf("size [KiB]  speed [GB/s]" "\n" // hlavička tabulky
           "----------  ------------" "\n"
    );
    for (int i = 1; i <= (1 << 16); i *= 2)        // i bude postupně 1, 2, 4 až nakonec 1<<16, tj. 2^16=65536
    {
        printf("%8i", SIZE / i / kibi);          // celý kus, pak 1/2, 1/4 atd., v kibibytech
        measure(pole, ARRAY_SIZE / i, REP * i, tp);
        printf("%#12.3g"  "\n", tp / giga);   // v gigabytech/s
    }

    return EXIT_SUCCESS;
}
