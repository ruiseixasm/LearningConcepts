#include "sender.h"


void senderSetup(unsigned long frequency)
{
#if     ENVIRONMENT == LOCAL
    Serial.println("Configured as RECEIVER! (LOCAL)");
    
#else //ENVIRONMENT == REMOTE
    Serial.println("Configured as SENDER! (REMOTE)");
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
    

    char convert[5];
    itoa(reading, convert, 10);
    strcat(message_to_send, convert);
    
    LoRa.beginPacket();
    LoRa.print(message_to_send);
    LoRa.endPacket();
    
    Serial.print("Message sent: ");
    Serial.println(message_to_send);
    
#endif
}
