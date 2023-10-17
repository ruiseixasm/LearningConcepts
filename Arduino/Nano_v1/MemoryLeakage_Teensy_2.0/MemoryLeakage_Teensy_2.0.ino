#include <Arduino.h>
#include "UselessLibrary.h"

// Results in 9 bytes for 'true' and 9 bytes for 'false' for the Arduino Nano Board!
// Results in 22 bytes for 'true' and 54 bytes for 'false' but only in Teensy 2.0 Board!
#define LOCAL true

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  
  char initiated_string[33] = "This results in Memory Leakage!!";

  if (LOCAL)
    LibraryClass::locallyDefinedFunction(initiated_string);
  else
    LibraryClass::externallyDefinedFunction(initiated_string);

}
