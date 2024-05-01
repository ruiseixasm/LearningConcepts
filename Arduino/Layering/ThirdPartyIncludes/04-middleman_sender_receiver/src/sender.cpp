#include "sender.h"


void senderSetup(unsigned long frequency)
{
#if     ENVIRONMENT == LOCAL
    // sets nothing
    
#else //ENVIRONMENT == REMOTE
    if (!LoRa.begin(frequency)) {
        Serial.println("Starting LoRa failed!");
        while (1);
    }
    Serial.println("LoRa connected!");
    
#endif
}


// Common function to be implemented in all sender hooks
void sendMessage(int reading)
{
#if     ENVIRONMENT == LOCAL
    // sends nothing!
    
#else //ENVIRONMENT == REMOTE
    char message_to_send[] = "YGM\0\0\0\0";
    if (reading < 1000)
        strcat(message_to_send, "0");
        
    message_to_send += String(reading);
    
    LoRa.beginPacket();
    LoRa.print(message_to_send);
    LoRa.endPacket();
    
    Serial.print("Message sent: ");
    Serial.println(message_to_send);
    
#endif
}
