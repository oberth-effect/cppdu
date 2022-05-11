#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    FILE *f;

    f = fopen("data 415.bin", "rb");
    fseek(f, 0, SEEK_END);
    int size = ftell(f);
    rewind(f);

    unsigned char data[size];
    fread(data, sizeof(unsigned char), size, f);

    unsigned char CheckSum = 0;
    for (int i = 0; i < size; i++) CheckSum ^= data[i];
    printf("Size:%i, CheckSum: 0x%02x" "\n", size, CheckSum);
    fclose(f);

    double a = 0.0;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            a += (double) (data[i] - data[j]) / (double) (i - j);
        }
    }
    a = a * 2 / (size - 1) / size;
    printf("a: %f\n", a);

    double b = 0.0;
    for (int i = 0; i < size; i++) {
        b += (double) data[i] - i * a;
    }
    b = b / size;
    printf("b: %f\n", b);

    double diff = 0.0;
    for (int i = 0; i < size; i++) {
        diff += fabs(i * a + b - (double) data[i]);
    }
    diff = diff / size;
    printf("Avg. dev.: %f", diff);

    return EXIT_SUCCESS;
}
