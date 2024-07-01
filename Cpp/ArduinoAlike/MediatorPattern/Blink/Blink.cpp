#include "Mediator.h"

#ifndef  ARDUINO

int main()
{
    mediatorSetup();
    while(1)
        mediatorLoop();
    
    return 0;
}

#endif
