#include "random.h"


void setSeed()
{
    if (!seed_set)
    {
        srand(time(NULL));  // Needed to make it trully random!
        seed_set = true;
    }
}

size_t getRandom(size_t module)
{
    setSeed();
    return rand() % module;
}
