#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "maximum.h"

#define M 5

void print_pole(int *p, int m)  // p je ukazatel na zacatek pole, m počet prvku
{
    for (int i = 0; i < m; i++) {
        printf("%i%s", p[i], i < (m - 1) ? "\t" : "");
    }
}

int main(void) {
    int pole[M];
    // Nasada do generatoru pseudonahodnych cisel vyuzitim
    srand(time(0)); // aktualniho casu, aby kazdy beh programu byl jiny.
    // Pri ladeni lze zakomentovat, pak bude kazdy beh stejny.

    for (int i = 0; i < M; i++) pole[i] = rand() % 10;  // vyplnime "nahodne" z intervalu <0,10)

    print_pole(pole, sizeof(pole) / sizeof(pole[0]));
    printf("\n");                                 // vypsani pole neodradkuje, musime zde

    int *max;

    max = get_maximum(0, pole);            // neplatny pocatek pole, funkce vrati nulovy ukazatel
    if (max) printf("max=%i" "\n", *max);  // max by melo byt 0, nelze *max, proto printf se preskoci

    max = get_maximum(pole, 0);            // neplatny konec pole, funkce vrati nulovy ukazatel
    if (max) printf("max=%i" "\n", *max);  // max by melo byt 0, nelze *max, proto printf se preskoci

    max = get_maximum(pole, pole);         // prazdne pole, funkce vrati nulovy ukazatel
    if (max) printf("max=%i" "\n", *max);  // max by melo byt 0, nelze *max, proto printf se preskoci

    max = get_maximum(pole, pole + 1);       // test s jednoprvkovym polem
    if (max) printf("max=%i" "\n", *max);  // *max by mel byt pole[0]

    max = get_maximum(pole, pole + M);       // cele pole
    if (max) printf("max=%i" "\n", *max);  // mel by najit maximum

    return 0;
}

