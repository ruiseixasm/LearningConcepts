#include "dummy_receiver.h"

int LoRa_available()
{
    return transmited_message.position != -1;
}

char LoRa_read()
{
    char message_char = transmited_message.content[transmited_message.position++];
    if (message_char == '\0')
        transmited_message.position = -1;
    return message_char;
}


// Bellow are all common functions that need to be implemented in all "receiver" hooks!

void receiveReading(char *message)
{
    for (int i = 0; LoRa_available(); i++)
    {
        message[i] = LoRa_read();
    }
    if (*message)
        printf("Message received:\t%s\n\n", message);
}

void redLightOn()
{
    if (!red_state && !red_state++)
        printf("Red ON      - %d times\n", ++total_reds);
}

void redLightOff()
{
    if (red_state && red_state--)
        printf("Red Off     - %d times\n", total_reds);
}

void greenLightOn()
{
    if (!green_state && !green_state++)
        printf("Green ON    - %d times\n", ++total_greens);
}

void greenLightOff()
{
    if (green_state && green_state--)
        printf("Green Off   - %d times\n", total_greens);
}

void blueLightOn()
{
    if (!blue_state && !blue_state++)
        printf("Blue ON     - %d times\a\n", ++total_blues);    // You've Got Mail
}

void blueLightOff()
{
    if (blue_state && blue_state--)
        printf("Blue Off    - %d times\n", total_blues);
}
