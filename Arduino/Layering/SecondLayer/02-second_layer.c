// LOGIC LAYER (LOGICAL)
#pragma once
#include "03-third_layer.c"
	
#if ENVIRONMENT == LOCAL
    #include "01-local_reader.c"
    #include "01-local_sender.c"
    #include "01-local_actor.c"
#elif ENVIRONMENT == REMOTE
    #include "01-remote_reader.c"
    #include "01-remote_sender.c"
    #include "01-remote_actor.c"
#else             // DUMMY
    #include "01-dummy_reader.c"
    #include "01-dummy_sender.c"
    #include "01-dummy_actor.c"
#endif

static long long int last_time_seconds = 0, this_time_seconds;
int reading;
char message[64];

void loop()
{
    this_time_seconds = time(NULL);
    if (this_time_seconds - last_time_seconds > 3)
    {
        reading = getReading();
        sprintf(message, "%d \t- %ld", reading, this_time_seconds);
        sendMessage(message);
        if (reading < 30 || reading > 250)
        {
            setRed();
        }
        else
        {
            setGreen();
        }
        last_time_seconds = this_time_seconds;
    }

}

void triggerValue(int value)
{
    doAction(value);
}

int timeToStop()
{

}