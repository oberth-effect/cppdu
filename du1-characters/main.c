#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main() {
    printf( " hex|dec|chr|print|control|wspace|alnum" "\n" );
    printf( "---------------------------------------" "\n" );
    for(unsigned int i=0;i<128;i++){
        printf("0x%.2x|%3d|%3c|%5c|%7c|%6c|%5c\n",i,i,isprint(i)?i:' ', isprint(i) ? 'x':' ', iscntrl(i) ? 'x' :' ', isspace(i) ? 'x':' ',
               isalnum(i)? 'x':' ');
    }

    return EXIT_SUCCESS;
}
