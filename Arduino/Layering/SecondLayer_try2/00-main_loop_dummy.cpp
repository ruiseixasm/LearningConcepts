#include "02-second_layer.h"

void setup() {
    *transmited_message.content = '\0';
    transmited_message.position = -1;
    redLightOn();
    greenLightOn();
    blueLightOn();
    greenLightOff();
    blueLightOff();
    printf("STARTED\n");
}

int main()
{
    setup();
    while (true)
    {
        second_loop();
    }
    
    return 0;
}
