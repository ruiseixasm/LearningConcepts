#include "middleman.h"

void middlemanSetup()
{
    serialSetup(9600);
    loraSetup(433E6);
    readerSetup();
}

void middlemanLoop()
{
    // To be implemented later
}
