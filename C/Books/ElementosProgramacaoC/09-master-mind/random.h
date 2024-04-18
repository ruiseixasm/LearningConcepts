#include <stdlib.h>     // needed for rand() and srand()
#include <time.h>       // needed for time() and clock()
#include <stddef.h>     // needed for size_t
#include <stdbool.h>    // needed for type bool
#include <stdio.h>      // to enable debugging messages

static bool seed_set = false;

void setSeed();
size_t getRandom(size_t module);
size_t getRandomrng(size_t start, size_t end);
