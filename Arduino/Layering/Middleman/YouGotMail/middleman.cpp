#include "middleman.h"


// BASELINE FUNCTIONS
void middlemanSetup()
{
    setupSetup();
}

void middlemanLoop()
{
    // FOR SERIAL
    
    if (serialRead(serial_read))
    {
        int read_size = strlen(serial_read);
        
        if (read_size == 7)
        {
            printf("\tREAD from SERIAL:\t%s\n\n", serial_read);
            // Tries to extract a reading in the LOCAL device (Reader)
            local_light_reading = extractLedLightIntensity(serial_read);
        }
        else if (read_size < 5)
        {
            printf("\tSERIAL to SENDER:\t%s\n", serial_read);
            if (read_size == 3)
                addPrefix(serial_read, "0");
            addPrefix(serial_read, "YGM");
        
            remoteLoraPrint(serial_read);
            printf("SENDER to RECEIVER:\t%s\n", serial_read);
        }
    }
    else
    {
        // FOR SENDER
        
        if (now_seconds() - last_read_seconds > REST_READ_SECONDS)
        {
            int light_intensity = ledLightIntensity();
        
            char message_to_send[16] = {0};
            numberToText(message_to_send, light_intensity);
            if (light_intensity < 1000)
                addPrefix(message_to_send, "0");
            
            addPrefix(message_to_send, "YGM");
        
            remoteLoraPrint(message_to_send);
            printf("SENDER to RECEIVER:\t%s\n", message_to_send);
                
            last_read_seconds = now_seconds();
        }

        // FOR RECEIVER
        
        if (localLoraRead(message_received))
        {
            printf("READ from SENDER:\t%s\n\n", message_received);
            // Tries to extract a reading in the LOCAL device (Reader)
            local_light_reading = extractLedLightIntensity(message_received);
        }
    }
    
    if (local_light_reading != -1)  // valid reading
    {
        
        printf("EXTRACTED VALUE:\t%d\n\n", local_light_reading);
        redLightOff();
        greenLightOn();
        if (local_light_reading > YGM_THRESHOLD)
            blueLightOn();
        else
            blueLightOff();
        local_light_reading = -1;
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


int extractLedLightIntensity(const char *message) {
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
