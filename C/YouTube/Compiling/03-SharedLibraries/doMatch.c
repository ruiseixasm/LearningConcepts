#include <stdio.h>
// #include <math.h> // Uses the user created lib instead (.a)
#include <stdlib.h>
#include <time.h>

#include "mathtest.h"       // shared library

// DYNAMIC LIBRARIES:
// gcc -fpic -c addNumbers.c subNumbers.c
// gcc -fpic -o libmath.so.1.2.3 addNumbers.o subNumbers.o -shared -Wl,-soname,libmath.so.1
// readelf -a libmath.so.1.2.3 | grep soname
// mv libmath.so.1.2.3 lib
// cd lib/
// ln -s libmath.so.1.2.3 libmath.so.1
// ln -s libmath.so.1 libmath.so
// cd ..
// gcc doMatch.c -o doMatch.out -lmath -I include -L lib
// file doMatch.out
// readelf -a doMatch.out | grep Shared
// # Specify an environmental variable
// echo $LD_LIBRARY_PATH
// LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/rui/GitHub/LearningConcepts/C/YouTube/Compiling/03-SharedLibraries/lib
// export LD_LIBRARY_PATH
// ./doMatch.out


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
