#include "middleman.h"

int main()
{
    middlemanSetup();
    while (true)
    {
        middlemanLoop();
    }
    
    return 0;
}
