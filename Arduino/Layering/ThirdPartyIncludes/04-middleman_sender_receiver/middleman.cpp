// LOGIC LAYER (LOGICAL)
#include "middleman.h"

#if     ENVIRONMENT == LOCAL
    void middlemanSetup()
    {
        serialSetup(9600);
        readerSetup();
        senderSetup(433E6);
        receiverSetup(433E6);
    }

#elif   ENVIRONMENT == REMOTE
    void middlemanSetup()
    {
        serialSetup(9600);
        readerSetup();
        senderSetup(433E6);
        receiverSetup(433E6);
    }

#else //ENVIRONMENT == DUMMY
    void middlemanSetup()
    {
        senderSetup();
        redLightOn();
        greenLightOn();
        blueLightOn();
        greenLightOff();
        blueLightOff();
        printf("STARTED\n");
    }
    
#endif

void middlemanLoop()
{
    receiveReading(message_received);
    
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


int extract_reading() {
    int message_size = strlen(message_received);
    if (message_size == 7 && strcspn(message_received, "YGM") == 0)
    {
        *message_received = '\0';           // marks message as empty for other str methods.
        return atoi(message_received + 3);  // jumps to the beginning of the numeric value
    }
    return -1;  // invalid reading
}
