#ifndef  ARDUINO

#include "Mediator.h"


int main()
{
    mediatorSetup();
    while(1)
        mediatorLoop();
    
    return 0;
}

#endif
