#include "02-second_layer.h"
#include "01-hooks_local/local_receiver.h"

void setup() {
    Serial.begin(9600);
    while (!Serial);
    
    // set the status LEDs
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);

    Serial.println("LoRa Receiver");
    if (!LoRa.begin(433E6)) {
        Serial.println("Starting LoRa failed!");
        while (1);
    }
    
//    // test the status LEDs and keep the red one on until data is received
//    redLightOn();
//    greenLightOn();
//    blueLightOn();
//    delay(1000);
//    redLightOff();
//    greenLightOff();
    
    // print the results to the Serial Monitor:
    Serial.println("STARTED");
}

void loop()
{
    second_loop();
}
