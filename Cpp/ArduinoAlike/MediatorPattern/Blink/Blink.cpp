#include "Mediator.h"

#ifndef  ARDUINO_IDE

int main()
{
    mediatorSetup();
    while(1)
        mediatorLoop();
    
    return 0;
}

#endif
