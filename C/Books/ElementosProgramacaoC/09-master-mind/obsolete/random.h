#ifndef LIB_RAND
#define LIB_RAND

#include <stdlib.h>     // needed for rand() and srand()
#include <time.h>       // needed for time() and clock()
#include <stddef.h>     // needed for size_t
#include <stdbool.h>    // needed for type bool
#include <stdio.h>      // to enable debugging messages

static bool seed_set = false;

void setSeed();
int iRandom(int module);
int iRandomrng(int start, int end);
long lNormRandom(long module);
long lNormRandomrng(long start, long end);


#endif /* LIB_RAND */
