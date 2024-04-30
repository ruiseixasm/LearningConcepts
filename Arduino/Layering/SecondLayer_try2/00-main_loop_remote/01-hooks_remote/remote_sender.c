#pragma once
#include <SPI.h>
#include <LoRa.h>



// Common function to be implemented in all sender hooks
void sendMessage(int reading) {
    char message_to_send[] = "YGM\0\0\0\0";
    if (reading < 1000)
        strcat(message_to_send, "0");
        
    message_to_send += String(reading);
    Serial.print("Message sent: ");
    Serial.println(message_to_send);
    
    LoRa.beginPacket();
    LoRa.print(message_to_send);
    LoRa.endPacket();
}
