#pragma once
#include "../environment_set.h"
#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>

void receiverSetup(unsigned long frequency);

// These constants won't change. They're used to give names to the pins used:
const int redPin = 7;       // RED LED pint
const int greenPin = 6;     // GREEN LED pint
const int bluePin = 5;      // BLUE LED pint    (You've Got Mail)

static char red_state = 0;
static char green_state = 0;
static char blue_state = 0;

// Bellow are all common functions that need to be implemented in all "receiver" hooks!

void receiveReading(char *message);

void redLightOn();

void redLightOff();

void greenLightOn();

void greenLightOff();

void blueLightOn();

void blueLightOff();
