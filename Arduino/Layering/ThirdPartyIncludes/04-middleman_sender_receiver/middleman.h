// LOGIC LAYER (LOGICAL)
#pragma once
#include "environment_set.h"

#define TESTING   TRUE

#if     ENVIRONMENT == LOCAL
    #if TESTING
        #define REST_READ_SECONDS       (unsigned long)20                   // (three times a day)
    #else
        #define REST_READ_SECONDS       (unsigned long)60 * 60 * 24 / 3     // (three times a day)
    #endif
    #define TIMEOUT_RECEIVE_SECONDS     REST_READ_SECONDS*3 + 120
    #define YGM_THRESHOLD               700
    
    #define now_seconds() (millis()/1000)

    #include "src/serial_com.h"
    #include "src/reader.h"
    #include "src/sender.h"
    #include "src/receiver.h"

#elif   ENVIRONMENT == REMOTE
    #if TESTING
        #define REST_READ_SECONDS       (unsigned long)20                   // (three times a day)
    #else
        #define REST_READ_SECONDS       (unsigned long)60 * 60 * 24 / 3     // (three times a day)
    #endif
    #define TIMEOUT_RECEIVE_SECONDS     REST_READ_SECONDS*3 + 120
    #define YGM_THRESHOLD               700
    
    #define now_seconds() (millis()/1000)

    #include "src/serial_com.h"
    #include "src/reader.h"
    #include "src/sender.h"
    #include "src/receiver.h"

#else //ENVIRONMENT == DUMMY
    #define REST_READ_SECONDS           (unsigned long)3
    #define TIMEOUT_RECEIVE_SECONDS     REST_READ_SECONDS*3 + 2
    #define YGM_THRESHOLD               1250
    #include <stdlib.h>     // needed for rand() and srand()
    #include <time.h>       // needed for time() and clock()
    #include <stddef.h>     // needed for size_t
    #include <stdbool.h>    // needed for type bool
    #include <string.h>
    #include <stdio.h>      // to enable debugging messages

    #define now_seconds() (unsigned long)time(NULL)

    #include "dummy/reader.h"
    #include "dummy/sender.h"
    #include "dummy/receiver.h"
    
#endif

void middlemanSetup();
void middlemanLoop();
void serialPrintln(const char *text);   // add hoc function

static unsigned long last_read_seconds      = 0;
static unsigned long last_receipt_seconds   = 0;
static unsigned long last_print_seconds     = 0;
static int remote_reading;
static int local_reading = -1; // no valid reading at the start
static char message_received[64];

int extract_reading();
