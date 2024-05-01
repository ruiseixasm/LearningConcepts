#include "reader.h"

void setSeed()
{
    if (!seed_set)
    {
        // Seed the random number generator with the current time
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        //srand(time(NULL));  // Needed to make it trully random!
        seed_set = true;
    }
}

int iRandom(int module)
{
    setSeed();
    return std::rand() % module;
}

int iRandomrng(int start, int end)
{
    int module = abs(end - start);
    int rvalue = iRandom(module);
    return (double)rvalue * (end - start) / module + start;
}

// Common function to be implemented in all reader hooks!
int getReading()
{
    int average_measures = 0;
    const int measures = 20;
    for (int i = 0; i < measures; i++)
    {
        average_measures += iRandomrng(0, 2048);    // 1024 is excluded
    }
    return average_measures / measures; // Normal distribution
}
