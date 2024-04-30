#pragma once
#include <cstdlib> // for std::srand
#include <ctime>   // for std::time
#include <stdio.h>      // to enable debugging messages

static bool seed_set = false;

void setSeed();

int iRandom(int module);

int iRandomrng(int start, int end);

// Common function to be implemented in all reader hooks!
int getReading();
