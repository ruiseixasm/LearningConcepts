#pragma once
#include "dummy_reader.h"
#include <stdio.h>
#include <cstring>

// For the REMOTE device (Sender)

// TransmittedMessage used as a channel of communication!! (intended for the receiver though)
typedef struct {
    char content[64];
    int position;
} TransmitedMessage;

extern TransmitedMessage transmited_message;

void LoRa_print(const char *message_string);

// Common function to be implemented in all sender hooks
void sendMessage(int reading);
