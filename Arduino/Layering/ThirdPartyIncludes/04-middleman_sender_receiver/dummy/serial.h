#pragma once
#include <cstring>
#include "reader.h"     // to have access to the random functions


static unsigned long last_serial_seconds      = 0;

int readSerial(char *serial_read);

void numberToText(char *text, int number);
