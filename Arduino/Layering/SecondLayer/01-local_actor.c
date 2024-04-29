#pragma once
#include <stdio.h>

static int total_reds = 0;
static int total_greens = 0;

void setRed()
{
    printf("Turn RED   - %d times\a\n", ++total_reds);
}

void setGreen()
{
    printf("Turn GREEN - %d times\n", ++total_greens);
}

void doAction(int value)
{
    if (value < 150 || value > 250)
    {
        setRed();
    }
    else
    {
        setGreen();
    }
}
