#include "middleman.h"


// BASELINE FUNCTIONS
void middlemanSetup()
{
    last_read_seconds = now_seconds();
    last_receipt_seconds = last_read_seconds;
    last_print_seconds = last_read_seconds;
    setupSetup();
}

void middlemanLoop()
{
    static int buttons_read;
    
    // FOR BUTTONS
    if ((buttons_read = buttonsRead()) > 0)
    {
        serialPrint("\n\tBUTTON PRESSED:\t");
        if (buttons_read == 0b01)       // Blue button
        {
                serialPrintln("BLUE\n");
                remoteLoraTurnOn();
                
                char message_to_send[16] = {0};
                numberToText(message_to_send, YGM_THRESHOLD + 1);
                while (strlen(message_to_send) < 4)
                    addPrefix(message_to_send, "0");
                addPrefix(message_to_send, "YGM");
            
                serialPrint("SENDER to RECEIVER:\t");
                serialPrintln(message_to_send);
                remoteLoraPrint(message_to_send);
        }
        else if (buttons_read == 0b10)  // Green button
        {
                serialPrintln("GREEN\n");
                
                char message_to_send[16] = {0};
                numberToText(message_to_send, YGM_THRESHOLD - 1);
                while (strlen(message_to_send) < 4)
                    addPrefix(message_to_send, "0");
                addPrefix(message_to_send, "YGM");
            
                serialPrint("SENDER to RECEIVER:\t");
                serialPrintln(message_to_send);
                remoteLoraPrint(message_to_send);
                remoteLoraTurnOff();
        }
        else if (buttons_read == 0b11)  // Both buttons
        {
                serialPrintln("BOTH\n");
                int light_intensity = ledLightIntensity();
        }
        else
            serialPrintln("?\n");
    }
    
    // FOR SERIAL
    else if (readSerialUntil("\n\t\r \0", serial_read, 16))
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
            else if (!strcmp(serial_read, "READ"))
            {
                int light_intensity = ledLightIntensity();
            }
            else
            {
                while (strlen(serial_read) < 4)
                    addPrefix(serial_read, "0");
                addPrefix(serial_read, "YGM");
            
                serialPrint("SENDER to RECEIVER:\t");
                serialPrintln(serial_read);
                remoteLoraPrint(serial_read);
            }
        }
    }
    else
    {
        // FOR SENDER                                                // PROCESS POWER-DOWN MODE
        if (now_seconds() - last_read_seconds > REST_READ_SECONDS || sleepForSeconds_8s(REST_READ_SECONDS))
        {
            last_read_seconds = now_seconds();
            
            int light_intensity = ledLightIntensity();          // delay: 10                            = 10
        
            char message_to_send[16] = {0};
            numberToText(message_to_send, light_intensity);
            while (strlen(message_to_send) < 4)
                addPrefix(message_to_send, "0");
            
            addPrefix(message_to_send, "YGM");
        
            serialPrint("SENDER to RECEIVER:\t");               // delay: 1*20                          = 20
            serialPrintln(message_to_send);                     // delay: 1*8                           = 8
            remoteLoraTurnOn();                                 // delay: 1*26 + 2000 + 1*16 + 2000     = 4042
            remoteLoraPrint(message_to_send);                   // delay: 1*(13 + 7 + 1)                = 21
            remoteLoraTurnOff();                                // delay: 1*27 + 2000 + 1*17            = 2044
        }                                                       // delay: TOTAL                         = 6145 milliseconds

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
        last_receipt_seconds = now_seconds();
        last_print_seconds = last_receipt_seconds;
        
        localLoraTurnOff();
        serialPrint("\n\tEXTRACTED VALUE:\t");
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
            last_print_seconds = now_seconds() - REST_SLACK_SECONDS;
            serialPrintln("\nNothing received!\n");
            expecting_to_receive = 0;
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
