#include <stdio.h>
// #include <math.h> // Uses the user created lib instead (.a)
#include <stdlib.h>
#include <time.h>

#include "mathtest.h"       // static library

// Compile as: gcc -c addNumbers.c subNumbers.c to obtain the binary objects
// Generate the reaspective library with: ar cr libmath.a addNumbers.o subNumbers.o
// Final compilation: gcc doMatch.c -lmath -o doMath.out -I include -L lib

int main() {

    // Needed to create a random number
    time_t t;
    srand((unsigned) time(&t)); // Sets the random seed
    int rNum_a = rand();
    int rNum_b = rand();

    int answer;

    answer = addNumbers(rNum_a, rNum_b);
    printf("%d + %d = %d\n", rNum_a, rNum_b, answer);

    answer = subNumbers(rNum_a, rNum_b);
    printf("%d - %d = %d\n", rNum_a, rNum_b, answer);

    return 0;
}