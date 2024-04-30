#pragma once

int getReading()
{
    int average_measures = 0;
    const int measures = 20;
    for (int i = 0; i < measures; i++)
    {
        average_measures += iRandomrng(0, 1024);    // 1024 is excluded
    }
    return average_measures / measures; // Normal distribution
}
