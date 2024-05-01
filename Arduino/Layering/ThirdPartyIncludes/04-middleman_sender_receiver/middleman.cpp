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

    void serialPrintln(const char *text)
    {
        Serial.println(text);
    }

#elif   ENVIRONMENT == REMOTE
    void middlemanSetup()
    {
        serialSetup(9600);
        readerSetup();
        senderSetup(433E6);
        receiverSetup(433E6);
    }

    void serialPrintln(const char *text)
    {
        // Does nothing!
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
    
    void serialPrintln(const char *text)
    {
        printf("%s\n", text);
    }

#endif

void middlemanLoop()
{
    // FOR SERIAL
    
    if (readSerial(serial_read))
    {
        int read_size = strlen(serial_read);
        
        if (read_size == 7)
        {
            // Tries to extract a reading in the LOCAL device (Reader)
            local_reading = extract_reading(serial_read);
        }
        else if (read_size < 5)
        {
            char message_to_send[16] = {0};
            if (read_size == 3)
                addPrefix(message_to_send, "0");
            
            addPrefix(message_to_send, "YGM");
        
            sendMessage(message_to_send);
        }
    }
    
    // FOR SENDER
    
    if (now_seconds() - last_read_seconds > REST_READ_SECONDS)
    {
        remote_reading = getReading();
    
        char message_to_send[16] = {0};
        numberToText(message_to_send, remote_reading);
        if (remote_reading < 1000)
            addPrefix(message_to_send, "0");
        
        addPrefix(message_to_send, "YGM");
    
        sendMessage(message_to_send);
            
        last_read_seconds = now_seconds();
    }

    // FOR RECEIVER
    
    if (receiveReading(message_received))
    {
        // Tries to extract a reading in the LOCAL device (Reader)
        local_reading = extract_reading(message_received);
    }
    
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
        last_print_seconds = now_seconds();
    }
    else if (now_seconds() - last_receipt_seconds > TIMEOUT_RECEIVE_SECONDS)
    {
        greenLightOff();
        redLightOn();
    }

    if (now_seconds() - last_print_seconds > 10)
    {
        serialPrintln("Nothing received!");
        last_print_seconds = now_seconds();
    }
}


int extract_reading(const char *message) {
    int message_size = strlen(message);
    if (message_size == 7 && strcspn(message, "YGM") == 0)
        return atoi(message + 3);  // jumps to the beginning of the numeric value
    return -1;  // invalid reading
}

void addPrefix(char *text, const char *prefix)
{
    int prefix_size = strlen(prefix);
    int text_size = strlen(text);
    
    for (int i = text_size + prefix_size; i >= prefix_size; i--)
    {
        text[i] = text[i - prefix_size];
    }
    for (int i = 0; i < prefix_size; i++)
    {
        text[i] = prefix[i];
    }
}

void removePrefix(char *text, const char *prefix)
{
    int prefix_size = strlen(prefix);
    int text_size = strlen(text);
    int i;
    for (i = prefix_size; i <= text_size; i++)
    {
        text[i - prefix_size] = text[i];
    }
}

