#include "serial_com.h"

void serialSetup(int baud_rate)
{
    Serial.begin(9600);
    while (!Serial);

    Serial.print("Serial com connected at: ");
    Serial.println(baud_rate);
}
