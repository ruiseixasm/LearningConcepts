#pragma once

#ifdef  ARDUINO

#include <Arduino.h>

#else

#include "PseudoArduino.h"

#endif

void mediatorSetup();
void mediatorLoop();