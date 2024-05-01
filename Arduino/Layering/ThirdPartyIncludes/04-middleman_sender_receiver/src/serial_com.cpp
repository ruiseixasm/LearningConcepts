#include "serial_com.h"

void serialSetup(unsigned long baud_rate)
{
    Serial.begin(baud_rate);
    while (!Serial);

    Serial.print("Serial com connected at: ");
    Serial.println(baud_rate);
}
