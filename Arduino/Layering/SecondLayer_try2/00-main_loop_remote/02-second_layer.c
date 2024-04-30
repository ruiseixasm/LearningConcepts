// LOGIC LAYER (LOGICAL)
#pragma once
#include "03-third_layer.c"

#if     ENVIRONMENT == LOCAL
    #define REST_READ_SECONDS           60 * 60 * 24 / 3    // (three times a day)
    #define TIMEOUT_RECEIVE_SECONDS     REST_READ_SECONDS*3 + 120
    #define YGM_THRESHOLD               700
    
    #define now_seconds() (millis()/1000)

    char message_received[64];

    #include "01-hooks_local/local_reader.c"
    #include "01-hooks_local/local_sender.c"
    #include "01-hooks_local/local_receiver.c"

#elif   ENVIRONMENT == REMOTE
    #define REST_READ_SECONDS           60 * 60 * 24 / 3    // (three times a day)
    #define TIMEOUT_RECEIVE_SECONDS     REST_READ_SECONDS*3 + 120
    #define YGM_THRESHOLD               700
    
    #define now_seconds() (millis()/1000)

    char message_received[64];

    #include "01-hooks_remote/remote_reader.c"
    #include "01-hooks_remote/remote_sender.c"
    #include "01-hooks_remote/remote_receiver.c"

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

    char message_received[64];

    #include "01-hooks_dummy/dummy_reader.c"
    #include "01-hooks_dummy/dummy_sender.c"
    #include "01-hooks_dummy/dummy_receiver.c"
    
#endif

static unsigned long last_read_seconds      = 0;
static unsigned long last_receipt_seconds   = 0;

int remote_reading;
int local_reading = -1; // no valid reading at the start

int extract_reading() {
    int message_size = strlen(message_received);
    if (message_size == 7 && strcspn(message_received, "YGM") == 0)
    {
        *message_received = '\0';           // marks message as empty for other str methods.
        return atoi(message_received + 3);  // jumps to the beginning of the numeric value
    }
    return -1;  // invalid reading
}

void second_loop()
{
    // For the REMOTE device (Sender)
    if (now_seconds() - last_read_seconds > REST_READ_SECONDS)
    {
        remote_reading = getReading();
        sendMessage(remote_reading);
        last_read_seconds = now_seconds();
    }

    // Tries to extract a reading in the LOCAL device (Reader)
    local_reading = extract_reading();

    if (local_reading != -1)  // valid reading
    {
        redLightOff();
        greenLightOn();
        if (local_reading > YGM_THRESHOLD)
            blueLightOn();
        else
            blueLightOff();
        local_reading = -1;
        last_receipt_seconds = now_seconds();
    }
    else if (now_seconds() - last_receipt_seconds > TIMEOUT_RECEIVE_SECONDS)
    {
        greenLightOff();
        redLightOn();
    }

}
