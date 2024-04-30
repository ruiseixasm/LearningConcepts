#include "02-second_layer.c"

static long long int my_last_time_seconds = 0;
static int my_value;
int total_triggers = 0;

int loop()
{
    my_last_time_seconds = time(NULL);
    do
    {
        if ((time(NULL) - my_last_time_seconds) > 3)
        {
            my_value = iRandomrng(200, 400);
            if (my_value < 205)
            {
                triggerValue(my_value);
                total_triggers++;
            }
            my_last_time_seconds = time(NULL);
        }
        second_loop();
    } while (total_triggers < 20);
}