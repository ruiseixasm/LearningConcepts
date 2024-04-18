#include "random.h"


void setSeed()
{
    if (!seed_set)
    {
        srand(time(NULL));  // Needed to make it trully random!
        //srand(clock());     // Alternative to the first that also works
        //printf("time(NULL): %ld | clock(): %ld\n", time(NULL), clock());
        //// time(NULL): 1713457747 | clock(): 3200
        seed_set = true;
    }
}

size_t getRandom(size_t module)
{
    setSeed();
    return rand() % module;
}

size_t getRandomrng(size_t start, size_t end)
{
    return getRandom(end - start) + start;
}
