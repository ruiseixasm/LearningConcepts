#include "02-second_layer.c"

void setup() {
    pinMode(lightPin, OUTPUT);           // set pin to input
    digitalWrite(lightPin, LOW);
    // initialize serial communications at 9600 bps:
    Serial.begin(9600);
    // print the results to the Serial Monitor:
    Serial.print("STARTED");
}

static long long int my_last_time_seconds = 0, my_this_time_seconds;
static int my_value;
int total_triggers = 0;

int loop()
{
    my_last_time_seconds = time(NULL);
    do
    {
        if ((my_this_time_seconds - my_last_time_seconds) > 3)
        {
            my_value = iRandomrng(200, 400);
            if (my_value < 205)
            {
                triggerValue(my_value);
                total_triggers++;
            }
            my_last_time_seconds = my_this_time_seconds;
        }
        loop();
        my_this_time_seconds = time(NULL);
    } while (total_triggers < 20);
    printf("FINISHED\n");
}