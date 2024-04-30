#pragma once
#include <stdio.h>

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

int receiveReading()
{
    for (int i = 0; LoRa_available(); i++)
    {
        message_received[i] = LoRa_read();
    }
    if (*message_received)
        printf("Message received:\t%s\n\n", message_received);
}


static int total_reds = 0;
static int total_greens = 0;
static int total_blues = 0;

static char red_state = 0;
static char green_state = 0;
static char blue_state = 0;

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
