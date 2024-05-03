#pragma once

#define DUMMY       0
#define LOCAL       1
#define REMOTE      2

#define SETUP       LOCAL
#define DEBUG       false

#define COM_BAUD    (unsigned long)9600
#define LORA_HZ     (unsigned long)433E6
#define LORA_DELAY  (unsigned long)3000

// LIBRARY INCLUDES

#if     SETUP == DUMMY

    #include <stdlib.h>     // needed for rand() and srand()
    #include <time.h>       // needed for time() and clock()
    #include <stddef.h>     // needed for size_t
    #include <stdbool.h>    // needed for type bool
    #include <string.h>
    #include <stdio.h>      // to enable debugging messages
    #include <ctime>        // for std::time
    #include <chrono>
    #include <cstdint>
    
    #define now_seconds() (unsigned long)time(NULL)

    // Specific for DUMMY config (Random operations)
    static bool seed_set = false;
    void setSeed();
    int iRandom(int module);
    int iRandomrng(int start, int end);
    
    // TransmittedMessage used as a channel of communication!! (intended for the receiver though)
    typedef struct {
        char content[16];
        int position;
    } TransmitedMessage;

    extern TransmitedMessage transmited_message;

    unsigned long timeSinceEpochMilliseconds();
    void delay(unsigned long milliseconds);

#else   // Arduino specifics

    #include <Arduino.h>
    #include <SPI.h>
    #include <LoRa.h>

    #define now_seconds() (millis()/1000)
    
    // These constants won't change. They're used to give names to the pins used:
    const int redPin    = 3;    // RED LED pin
    const int greenPin  = 4;    // GREEN LED pin
    const int powerPin  = 5;    // Pin that turns on LoRa power
    const int bluePin   = 6;    // BLUE LED pin     (You've Got Mail)
    const int buzzerPin = 7;    // Buzzer pin       (You've Got Mail)

    static int sensorValue  = 0;    // value read from the pot
    const int lightPin      = 8;    // LED pint
    const int analogInPin   = A0;   // (14) Analog input pin that the potentiometer is attached to

    void triggerBuzzer();

#endif


// BASELINE FUNCTIONS
void setupSetup();

// SETUP FUNCTIONS
char *numberToText(char *text, int number);
int textToNumber(const char *text);

int serialRead(char *text);
void serialPrint(const char *text);
void serialPrintln(const char *text);

int ledLightIntensity();
int loraRead(char *message);
int localLoraRead(char *message);
int remoteLoraRead(char *message);
void loraPrint(const char *message);
void localLoraPrint(const char *message);
void remoteLoraPrint(const char *message);
void loraTurnOn();
void localLoraTurnOn();
void remoteLoraTurnOn();
void loraTurnOff();
void localLoraTurnOff();
void remoteLoraTurnOff();

void redLightOn();
void redLightOff();
void greenLightOn();
void greenLightOff();
void blueLightOn();
void blueLightOff();



// SETUP VARIABLES
static unsigned long last_serial_seconds      = 0;

static int total_reds           = 0;
static int total_greens         = 0;
static int total_blues          = 0;

static char red_state           = 0;
static char green_state         = 0;
static char blue_state          = 0;
static char local_lora_power    = 0;
static char remote_lora_power   = 0;
