// These constants won't change. They're used to give names to the pins used:
int sensorValue = 0;        // value read from the pot
const int lightPin = 8;     // LED pint
const int analogInPin = A0; // (14) Analog input pin that the potentiometer is attached to

// Common function to be implemented in all reader hooks!
int getReading()
{
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
}
