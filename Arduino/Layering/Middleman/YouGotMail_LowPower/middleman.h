#pragma once
#include "setup.h"

#if     SETUP == DUMMY

    #define REST_READ_SECONDS           (unsigned long)60                   // (each 60 seconds)
    #define REST_SLACK_SECONDS          (unsigned long)3                    // (each 3 seconds)
    #define TIMEOUT_RECEIVE_SECONDS     REST_READ_SECONDS*5 + REST_SLACK_SECONDS
    #define YGM_THRESHOLD               1250

#else

    #if DEBUG
        #define REST_READ_SECONDS       (unsigned long)60 * 5               // (each 5 minutes)
        #define REST_SLACK_SECONDS      (unsigned long)20                   // (slack of 20 seconds)
    #else
        #define REST_READ_SECONDS       (unsigned long)60 * 60 * 24 / 4     // (four times a day)
        #define REST_SLACK_SECONDS      (unsigned long)600                  // (slack of 10 minutes)
    #endif
    #define TIMEOUT_RECEIVE_SECONDS     REST_READ_SECONDS*3 + REST_SLACK_SECONDS
    #define YGM_THRESHOLD               650
    
#endif


// BASELINE FUNCTIONS
void middlemanSetup();
void middlemanLoop();

// MIDDLEMAN FUNCTIONS
int extractLedLightIntensity(const char *message);
void addPrefix(char *text, const char *prefix);
void removePrefix(char *text, const char *prefix);


// MIDDLEMAN VARIABLES
static unsigned long last_read_seconds      = 0;
static unsigned long last_receipt_seconds   = 0;
static unsigned long last_print_seconds     = 0;
static int expecting_to_receive             = 0;
static int local_light_reading = -1;        // no valid reading at the start
static char message_received[16];
static char serial_read[16];
