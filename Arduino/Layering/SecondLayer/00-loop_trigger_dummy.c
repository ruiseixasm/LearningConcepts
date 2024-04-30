#include "02-second_layer.c"

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
    do
    {
        receiveReading();
        second_loop();
    } while (true);
    
    return 0;
}