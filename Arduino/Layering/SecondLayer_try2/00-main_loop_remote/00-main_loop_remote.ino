#include "02-second_layer.c"


void setup() {
    Serial.begin(9600);
    while (!Serial);
    pinMode(lightPin, OUTPUT);           // set pin to input
    digitalWrite(lightPin, LOW);

    Serial.println("LoRa Sender");
    if (!LoRa.begin(433E6)) {
        Serial.println("Starting LoRa failed!");
        while (1);
    }
    // print the results to the Serial Monitor:
    Serial.println("STARTED");
}

int loop()
{
    my_last_time_seconds = time(NULL);
    do
    {
        if ((time(NULL) - my_last_time_seconds) > 3)
        {
            my_value = iRandomrng(200, 400);
            if (my_value < 205)
            {
                triggerValue(my_value);
                total_triggers++;
            }
            my_last_time_seconds = time(NULL);
        }
        second_loop();
    } while (total_triggers < 20);
}
