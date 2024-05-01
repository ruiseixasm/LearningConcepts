#include "middleman.h"

// Can't be preset for Arduino compilation!! main() conflict
#if ENVIRONMENT == DUMMY
int main()
{
    middlemanSetup();
    while (true)
    {
        middlemanLoop();
    }
    
    return 0;
}
#endif
