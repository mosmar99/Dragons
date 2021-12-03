#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <stdlib.h>
#define SIZE 10

int main(void) {
    clock_t begin = clock();
    // --------- S T A R T  T O  C O D E  H E R E ---------
    printf("hello");


    // --------- E N D  O F  C O D E ---------
    clock_t end = clock();
    double res = (double) (end - begin) / CLOCKS_PER_SEC;
    printf("\nExecution time: %f", res);
    return 0;
}