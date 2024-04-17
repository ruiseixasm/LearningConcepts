#include <stdlib.h>     // needed for rand() and srand()
#include <time.h>       // needed for time()
#include <stddef.h>     // needed for size_t
#include <stdbool.h>    // needed for type bool

static bool seed_set = false;

void setSeed();
size_t getRandom(size_t module);
