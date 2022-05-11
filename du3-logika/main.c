#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void ops(bool *res, int a, int b) {
    res[0] = a;
    res[1] = b;
    res[2] = 0;
    res[3] = !(a || b);
    res[4] = !a && b;
    res[5] = !a;
    res[6] = a && !b;
    res[7] = !b;
    res[8] = (a || b) && !(a && b);
    res[9] = !(a && b);
    res[10] = a && b;
    res[11] = (a && b) || !(a || b);
    res[12] = b;
    res[13] = !a || b;
    res[14] = a;
    res[15] = a || !b;
    res[16] = a || b;
    res[17] = 1;
}

int main() {
    printf("      ___ _   _   _ _     ___     ___   _       _       " "\n"
           "a|b|0|a+b|a&b|a|a&b|b|a^b|a&b|a&b|a^b|b|a+b|a|a+b|a+b|1|" "\n"
           "--------------------------------------------------------" "\n"
    );
    bool results[18];
    for(int a = 0; a <=1; a++ ){
        for(int b = 0; b<=1; b++){
            ops(results,a,b);
            for(int i = 0;i<18;i++){
                if(i>2 && i!=5 && i!=7 && i!=12 && i!=14 && i!=17){
                    printf(" %i " "|",results[i]);
                }
                else{
                    printf("%i" "|",results[i]);
                }
            }
            printf("\n");
        }
    }

    return EXIT_SUCCESS;
}
