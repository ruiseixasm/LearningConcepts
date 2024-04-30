// LOGIC LAYER (LOGICAL)
#pragma once
#include "03-third_layer.c"

#if     ENVIRONMENT == LOCAL
    #define REST_READ_SECONDS   0
    #include <SPI.h>
    #include <LoRa.h>
    #define now_seconds() (millis()/1000)

    // These constants won't change. They're used to give names to the pins used:
    const int redPin = 7;       // RED LED pint
    const int greenPin = 6;     // GREEN LED pint
    const int bluePin = 5;      // BLUE LED pint    (You've Got Mail)

    void setup() {
        Serial.begin(9600);
        while (!Serial);
        pinMode(lightPin, OUTPUT);           // set pin to input
        digitalWrite(lightPin, LOW);

        Serial.println("LoRa Receiver");
        if (!LoRa.begin(433E6)) {
            Serial.println("Starting LoRa failed!");
            while (1);
        }
        // print the results to the Serial Monitor:
        Serial.println("STARTED");
    }

    #include "01-hooks_local/local_reader.c"
    #include "01-hooks_local/local_sender.c"
    #include "01-hooks_local/local_actor.c"

#elif   ENVIRONMENT == REMOTE
    #define REST_READ_SECONDS   60 * 60 * 24 / 3    // (three times a day)
    #include <SPI.h>
    #include <LoRa.h>
    #define now_seconds() (millis()/1000)

    // These constants won't change. They're used to give names to the pins used:
    int sensorValue = 0;        // value read from the pot
    const int lightPin = 8;     // LED pint
    const int analogInPin = A0;  // (14) Analog input pin that the potentiometer is attached to

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

    #include "01-hooks_remote/remote_reader.c"
    #include "01-hooks_remote/remote_sender.c"
    #include "01-hooks_remote/remote_actor.c"

#else //ENVIRONMENT == DUMMY
    #define REST_READ_SECONDS   3
    #include <stdlib.h>     // needed for rand() and srand()
    #include <time.h>       // needed for time() and clock()
    #include <stddef.h>     // needed for size_t
    #include <stdbool.h>    // needed for type bool
    #include <string.h>
    #include <stdio.h>      // to enable debugging messages

    #define now_seconds() (unsigned long)time(NULL)

    typedef struct {
        char content[64];
        int position;
    } Message;

    Message message;

    char message[64];
    static int message_received = 0;    // false

    static bool seed_set = false;

    void setSeed()
    {
        if (!seed_set)
        {
            srand(time(NULL));  // Needed to make it trully random!
            seed_set = true;
        }
    }

    int iRandom(int module)
    {
        setSeed();
        return rand() % module;
    }

    int iRandomrng(int start, int end)
    {
        int module = abs(end - start);
        int rvalue = iRandom(module);
        return (double)rvalue * (end - start) / module + start;
    }

    int getMessage()
    {
        if (!message_received) return 0;
        message_received = 0;
        return 1;
    }

    void LoRa_print(const char *message_string)
    {
        strcpy(message.content, message_string);
        message.position = 0;
    }

    int LoRa_available()
    {
        return message.position != -1;
    }
    
    char LoRa_read()
    {
        char message_char = message.content[message.position++];
        if (message_char == '\0')
            message.position = -1;
        return message_char;
    }

    void send_message(int reading) {
        char message_to_send[64];
        sprintf(message_to_send, "%d \t- %ld", reading, now_seconds());
        LoRa_print(message_to_send);
    }

    void process_reading() {
        char message_to_send[64];
        sprintf(message_to_send, "%d \t- %ld", reading, now_seconds());
        LoRa_print(message_to_send);
    }

    void setup() {
        message.position = -1;
        printf("STARTED\n");
    }

    #include "01-hooks_dummy/dummy_reader.c"
    #include "01-hooks_dummy/dummy_sender.c"
    #include "01-hooks_dummy/dummy_actor.c"
    
#endif

static unsigned long last_seconds = 0;
int reading;

void second_loop()
{
    if (now_seconds() - last_seconds > REST_READ_SECONDS)
    {
        reading = getReading();
        send_message(reading);
    }

    receive_reading();

    if (reading < 30 || reading > 680)
    {
        setRed();
    }
    else
    {
        setGreen();
    }
    last_seconds = now_seconds();
}

void triggerValue(int value)
{
    doAction(value);
}

int timeToStop()
{

}