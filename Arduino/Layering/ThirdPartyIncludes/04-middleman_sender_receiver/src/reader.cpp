#include "reader.h"

void readerSetup()
{
#if     ENVIRONMENT == LOCAL
    // sets nothing
    
#else //ENVIRONMENT == REMOTE
    pinMode(lightPin, OUTPUT);           // set pin to input
    // Turn off the light
    digitalWrite(lightPin, LOW);
    
#endif
}


// Common function to be implemented in all reader hooks!
int getReading()
{
#if     ENVIRONMENT == LOCAL
    return -1;
    
#else //ENVIRONMENT == REMOTE
    digitalWrite(lightPin, HIGH);
    delay(20);  // allows liht warm up
    // read the analog in value:
    sensorValue = analogRead(analogInPin);
    // map it to be correlated to light intensity, from 0 to 1023:
    sensorValue = map(sensorValue, 0, 1023, 1023, 0);
    // Turn off the light
    digitalWrite(lightPin, LOW);
    // print the results to the Serial Monitor:
    Serial.print("sensor = ");
    Serial.print(sensorValue);
    return sensorValue; // Returns final reading
    
#endif
}
