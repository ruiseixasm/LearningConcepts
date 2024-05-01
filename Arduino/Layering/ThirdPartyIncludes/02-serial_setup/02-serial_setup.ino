#include "serial_com.h"

void setup()
{
    unsigned long baud = 9600;
    setupSerial(baud);
}

void loop()
{
    Serial.println("Serial port working correctly!");
    delay(10000);
}
