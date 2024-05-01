#pragma once
#include <Arduino.h>

static int sensorValue = 0; // value read from the pot
const int lightPin = 8;     // LED pint
const int analogInPin = A0; // (14) Analog input pin that the potentiometer is attached to

void readerSetup();

// Common function to be implemented in all reader hooks!
int getReading();
