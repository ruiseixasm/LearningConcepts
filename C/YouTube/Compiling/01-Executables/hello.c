#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


int main(void) {

    printf("Hello World!\n");   // libc

    // Needed to create a random number
    time_t t;
    srand((unsigned) time(&t)); // Sets the random seed
    int rNum = rand();

    double sr = sqrt(rNum);     // libm

    printf("Square root of %d is %f\n", rNum, sr);

    return 0;
}