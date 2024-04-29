#pragma once
#include <stdlib.h>     // needed for rand() and srand()
#include <time.h>       // needed for time() and clock()
#include <stddef.h>     // needed for size_t
#include <stdbool.h>    // needed for type bool
#include <string.h>
#include <stdio.h>      // to enable debugging messages

static bool seed_set = false;

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


int getReading()
{
    return -1;
}
