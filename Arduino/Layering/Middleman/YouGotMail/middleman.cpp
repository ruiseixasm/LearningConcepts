#include "middleman.h"


// BASELINE FUNCTIONS
void middlemanSetup()
{
    setupSetup();
    last_read_seconds = now_seconds();
    last_receipt_seconds = now_seconds();
    last_print_seconds = now_seconds();
}

void middlemanLoop()
{
    // FOR SERIAL
    
    if (serialRead(serial_read))
    {
        int read_size = strlen(serial_read);
        serialPrint("\n\tREAD from SERIAL:\t");
        serialPrintln(serial_read);
        serialPrintln("");

        if (read_size == 7)
        {
            // Tries to extract a reading in the LOCAL device (Reader)
            local_light_reading = extractLedLightIntensity(serial_read);
        }
        else if (read_size < 5)
        {
            if (!strcmp(serial_read, "ON"))
            {
                localLoraTurnOn();
                remoteLoraTurnOn();
            }
            else if (!strcmp(serial_read, "OFF"))
            {
                localLoraTurnOff();
                remoteLoraTurnOff();
            }
            else
            {
                while (strlen(serial_read) < 4)
                    addPrefix(serial_read, "0");
                addPrefix(serial_read, "YGM");
            
                remoteLoraPrint(serial_read);
                serialPrint("SENDER to RECEIVER:\t");
                serialPrintln(serial_read);
            }
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
        
            remoteLoraTurnOn();
            remoteLoraPrint(message_to_send);
            serialPrint("SENDER to RECEIVER:\t");
            serialPrintln(message_to_send);
            remoteLoraTurnOff();
            last_read_seconds = now_seconds();
        }

        // FOR RECEIVER
        
        if (localLoraRead(message_received))
        {
            serialPrint("READ from SENDER:\t");
            serialPrintln(message_received);
            serialPrintln("");
            // Tries to extract a reading in the LOCAL device (Reader)
            local_light_reading = extractLedLightIntensity(message_received);
        }
    }
    
    if (local_light_reading != -1)  // valid reading
    {
        localLoraTurnOff();
        serialPrint("\tEXTRACTED VALUE:\t");
        char text[16] = {0};
        serialPrintln(numberToText(text, local_light_reading));
        serialPrintln("");
        redLightOff();
        greenLightOn();
        if (local_light_reading > YGM_THRESHOLD)
            blueLightOn();
        else
            blueLightOff();
        local_light_reading = -1;
        last_receipt_seconds = now_seconds();
        last_print_seconds = now_seconds();
        expecting_to_receive = 0;
    }
    else if (now_seconds() - last_receipt_seconds > TIMEOUT_RECEIVE_SECONDS)
    {
        greenLightOff();
        redLightOn();
    }

    if (now_seconds() - last_print_seconds > REST_READ_SECONDS - 2*REST_SLACK_SECONDS)
    {
        
        if (!expecting_to_receive)
        {
            localLoraTurnOn();
            serialPrintln("\nExpecting to receive...\n");
            expecting_to_receive = 1;
        }
        
        if (now_seconds() - last_print_seconds > REST_READ_SECONDS + REST_SLACK_SECONDS)
        {
            serialPrintln("\nNothing received!\n");
            last_print_seconds = now_seconds() - REST_SLACK_SECONDS;
        }
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
