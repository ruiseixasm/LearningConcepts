// LOGIC LAYER (LOGICAL)
#pragma once
#include "03-third_layer.h"

#if     ENVIRONMENT == LOCAL
    #define REST_READ_SECONDS           60 * 60 * 24 / 3    // (three times a day)
    #define TIMEOUT_RECEIVE_SECONDS     REST_READ_SECONDS*3 + 120
    #define YGM_THRESHOLD               700
    
    #define now_seconds() (millis()/1000)

    #include "01-hooks_local/local_reader.h"
    #include "01-hooks_local/local_sender.h"
    #include "01-hooks_local/local_receiver.h"

#elif   ENVIRONMENT == REMOTE
    #define REST_READ_SECONDS           60 * 60 * 24 / 3    // (three times a day)
    #define TIMEOUT_RECEIVE_SECONDS     REST_READ_SECONDS*3 + 120
    #define YGM_THRESHOLD               700
    
    #define now_seconds() (millis()/1000)

    #include "01-hooks_remote/remote_reader.h"
    #include "01-hooks_remote/remote_sender.h"
    #include "01-hooks_remote/remote_receiver.h"

#else //ENVIRONMENT == DUMMY
    #define REST_READ_SECONDS           3
    #define TIMEOUT_RECEIVE_SECONDS     REST_READ_SECONDS*3 + 2
    #define YGM_THRESHOLD               1250
    #include <stdlib.h>     // needed for rand() and srand()
    #include <time.h>       // needed for time() and clock()
    #include <stddef.h>     // needed for size_t
    #include <stdbool.h>    // needed for type bool
    #include <string.h>
    #include <stdio.h>      // to enable debugging messages

    #define now_seconds() (unsigned long)time(NULL)

    #include "01-hooks_dummy/dummy_reader.h"
    #include "01-hooks_dummy/dummy_sender.h"
    #include "01-hooks_dummy/dummy_receiver.h"
    
#endif

static unsigned long last_read_seconds      = 0;
static unsigned long last_receipt_seconds   = 0;

static int remote_reading;
static int local_reading = -1; // no valid reading at the start

static char message_received[64];

int extract_reading();

void second_loop();
