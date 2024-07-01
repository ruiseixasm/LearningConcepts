#define ARDUINO_IDE true
#include <Arduino.h>
#include "Mediator.h"

void setup()
{
    mediatorSetup();
}

void loop()
{
    mediatorLoop();
}
