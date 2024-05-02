#include "middleman.h"

#if     SETUP == DUMMY

int main()
{
    middlemanSetup();
    while(1)
        middlemanLoop();
    
    return 0;
}

#endif
