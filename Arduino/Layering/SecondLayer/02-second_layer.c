// LOGIC LAYER (LOGICAL)
#pragma once
#include "03-third_layer.c"
	
#if ENVIRONMENT == LOCAL
    #define REST_READ_SECONDS   0
    #include "01-hooks_local/local_reader.c"
    #include "01-hooks_local/local_sender.c"
    #include "01-hooks_local/local_actor.c"
#elif ENVIRONMENT == REMOTE
    #define REST_READ_SECONDS   60 * 60 * 24 / 3
    #include "01-hooks_remote/remote_reader.c"
    #include "01-hooks_remote/remote_sender.c"
    #include "01-hooks_remote/remote_actor.c"
#else             // DUMMY
    #define REST_READ_SECONDS   3
    #include "01-hooks_dummy/dummy_reader.c"
    #include "01-hooks_dummy/dummy_sender.c"
    #include "01-hooks_dummy/dummy_actor.c"
#endif

static long long int last_time_seconds = 0, this_time_seconds;
int reading;
char message[64];

void loop()
{
    this_time_seconds = time(NULL);
    if (this_time_seconds - last_time_seconds > REST_READ_SECONDS)
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