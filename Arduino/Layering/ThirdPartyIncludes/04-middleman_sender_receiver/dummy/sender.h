#pragma once
#include "reader.h"     // to have access to the random functions
#include <stdio.h>
#include <cstring>

// For the REMOTE device (Sender)

// TransmittedMessage used as a channel of communication!! (intended for the receiver though)
typedef struct {
    char content[16];
    int position;
} TransmitedMessage;

extern TransmitedMessage transmited_message;

void senderSetup();
void senderLoop();

void LoRa_print(const char *message_string);

// Common function to be implemented in all sender hooks
void sendMessage(const char *message_to_send);
