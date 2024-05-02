#include "serial.h"


int readSerial(char *serial_read)
{    
    if (time(NULL) - last_serial_seconds > 5)
    {
        if (iRandom(2))
            strcpy(serial_read, "YGM4444");
        else
            strcpy(serial_read, "3333");
            
        last_serial_seconds = time(NULL);
        return 1;
    }    
    return 0;
}


void numberToText(char *text, int number)
{
    sprintf(text, "%d", number);    
}
