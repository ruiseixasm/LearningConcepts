#include "sender.h"

// For the REMOTE device (Sender)
TransmitedMessage transmited_message;

void senderSetup()
{
    *transmited_message.content = '\0';
    transmited_message.position = -1;
}

void senderLoop()
{
    
}

void LoRa_print(const char *message_string)
{
    strcpy(transmited_message.content, message_string);
    transmited_message.position = 0;
}

// Common function to be implemented in all sender hooks
void sendMessage(const char *message) {
    printf("Message sent:\t%s\n", message);
    if (iRandom(4)) // 1 in 4 chances of the message being lost in transmission!
        LoRa_print(message);
}
