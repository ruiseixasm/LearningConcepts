#include <iostream>
#include "mediator.h"

// Instantiate a global Serial object similar to Arduino
SerialClass Serial;


int main() {
    int number = 10;
    Serial.println(number);


    return 0;
}