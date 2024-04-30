#pragma once
#include <stdio.h>      // to enable debugging messages

static bool seed_set = false;

void setSeed()
{
    if (!seed_set)
    {
        srand(time(NULL));  // Needed to make it trully random!
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
    int average_measures = 0;
    const int measures = 20;
    for (int i = 0; i < measures; i++)
    {
        average_measures += iRandomrng(0, 1024);    // 1024 is excluded
    }
    return average_measures / measures; // Normal distribution
}
