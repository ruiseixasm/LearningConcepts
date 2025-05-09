#include <Arduino.h>


uint32_t value = 10000;
uint32_t bellow = 9000;


void setup()
{
    Serial.begin(9600);
    while (!Serial);
    
    uint32_t delta = value - bellow;
    Serial.println(delta);  // 1000

    // Overflow (negative value)
    delta = bellow - value;
    Serial.println(delta);  // 4294966296
}

void loop()
{
    
}
