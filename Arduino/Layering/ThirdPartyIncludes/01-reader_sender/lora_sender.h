#pragma once
#include <Arduino.h>

#include <SPI.h>
#include <LoRa.h>

void loraSetup(unsigned long frequency);

void messageSend (const char *message);
