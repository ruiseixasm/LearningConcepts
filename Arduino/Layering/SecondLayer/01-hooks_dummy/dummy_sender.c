#pragma once
#include <stdio.h>

// For the REMOTE device (Sender)

// TransmittedMessage used as a chab«nnel of communication!!
typedef struct {
    char content[64];
    int position;
} TransmitedMessage;

TransmitedMessage transmited_message;

void LoRa_print(const char *message_string)
{
    strcpy(transmited_message.content, message_string);
    transmited_message.position = 0;
}

void send_message(int reading) {
    char message_to_send[] = "YGM\0\0\0\0";
    char reading_string[5] = {0};
    if (reading < 1000)
        strcat(message_to_send, "0");
    //itoa(reading, reading_string, 10);
    sprintf(reading_string, "%d", reading);
    strcat(message_to_send, reading_string);
    printf("Message sent:\t%s\n", message_to_send);
    if (iRandom(4)) // 1 in 4 chances of the message being lost in transmission!
        LoRa_print(message_to_send);
}
