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

int iRandom(int module)
{
    setSeed();
    return rand() % module;
}

int iRandomrng(int start, int end)
{
    int module = abs(end - start);
    int rvalue = iRandom(module);
    return (double)rvalue * (end - start) / module + start;
}

long lNormRandom(long module)
{
    int loops = sizeof(long) * 8 / RAND_MAX + 1;
    long rvalue = 0;
    for (int i = 0; i < loops; i++)
        rvalue += iRandom(RAND_MAX);
    return rvalue % module;
}

long lNormRandomrng(long start, long end)
{
    long module = abs(end - start);
    long rvalue = lNormRandom(module);
    return (double)rvalue * (end - start) / module + start;
}
