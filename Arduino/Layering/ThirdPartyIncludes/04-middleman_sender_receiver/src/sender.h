#pragma once
#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>


void senderSetup(unsigned long frequency);

// Common function to be implemented in all sender hooks
void sendMessage(int reading);
