#pragma once
#include "sender.h"     // to have access to transmited_message as communication media simulator
#include <stdio.h>

int LoRa_available();

char LoRa_read();


// Bellow are all common functions that need to be implemented in all "receiver" hooks!

int receiveReading(char *message);

static int total_reds = 0;
static int total_greens = 0;
static int total_blues = 0;

static char red_state = 0;
static char green_state = 0;
static char blue_state = 0;

void redLightOn();

void redLightOff();

void greenLightOn();

void greenLightOff();

void blueLightOn();

void blueLightOff();
