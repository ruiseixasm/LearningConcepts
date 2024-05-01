#include "lora_sender.h"



void loraSetup(unsigned long frequency)
{
    
    if (!LoRa.begin(frequency)) {
        Serial.println("Starting LoRa failed!");
        while (1);
    }
}

void messageSend (const char *message)
{
    
    
    
}
