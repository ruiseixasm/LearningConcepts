#include "local_receiver.h"


// Bellow are all common functions that need to be implemented in all "receiver" hooks!

void receiveReading(char *message)
{
    // try to parse packet
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
        // received a packet
        Serial.print("Received packet '");

        // read packet
        int i;
        for (i = 0; LoRa.available(); i++)
        {
            message[i] = (char)LoRa.read();
            Serial.print(message[i]);
        }
        message[i] = '\0';

        // print RSSI of packet
        Serial.print("' with RSSI ");
        Serial.println(LoRa.packetRssi());
    }
}

void redLightOn()
{
    if (!red_state && !red_state++)
        digitalWrite(redPin, HIGH);
}

void redLightOff()
{
    if (red_state && red_state--)
        digitalWrite(redPin, LOW);
}

void greenLightOn()
{
    if (!green_state && !green_state++)
        digitalWrite(greenPin, HIGH);
}

void greenLightOff()
{
    if (green_state && green_state--)
        digitalWrite(greenPin, LOW);
}

void blueLightOn()
{
    if (!blue_state && !blue_state++)
        digitalWrite(bluePin, HIGH);
}

void blueLightOff()
{
    if (blue_state && blue_state--)
        digitalWrite(bluePin, LOW);
}
