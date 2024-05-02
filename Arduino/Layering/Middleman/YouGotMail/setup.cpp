#include "setup.h"

#if     SETUP == DUMMY

// For the REMOTE device (Sender)
TransmitedMessage transmited_message;

void setupSetup()
{
    redLightOn();
    greenLightOn();
    blueLightOn();
    greenLightOff();
    blueLightOff();
    printf("STARTED\n");    
}

void setSeed()
{
    if (!seed_set)
    {
        // Seed the random number generator with the current time
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        //srand(time(NULL));  // Needed to make it trully random!
        seed_set = true;
    }
}

int iRandom(int module)
{
    setSeed();
    return std::rand() % module;
}

int iRandomrng(int start, int end)
{
    int module = abs(end - start);
    int rvalue = iRandom(module);
    return (double)rvalue * (end - start) / module + start;
}

unsigned long timeSinceEpochMilliseconds() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void delay(unsigned long milliseconds)
{
    unsigned long refe_time = timeSinceEpochMilliseconds();
    while(timeSinceEpochMilliseconds() - refe_time < milliseconds) {}
}

void numberToText(char *text, int number)
{
    sprintf(text, "%d", number);    
}

int textToNumber(const char *text)
{
    return atoi(text);
}

int serialRead(char *text)
{
    if (time(NULL) - last_serial_seconds > 5)
    {
        if (iRandom(2))
            strcpy(text, "YGM4444");
        else
            strcpy(text, "3333");
            
        last_serial_seconds = time(NULL);
        return 1;
    }    
    return 0;
}

void serialPrint(const char *text)
{
    printf("%s", text);
}

void serialPrintln(const char *text)
{
    printf("%s\n", text);
}

int ledLightIntensity()
{
    int average_measures = 0;
    const int measures = 20;
    for (int i = 0; i < measures; i++)
    {
        average_measures += iRandomrng(0, 2048);    // 1024 is excluded
    }
    return average_measures / measures; // Normal distribution
}

int loraRead(char *message)
{
    if (transmited_message.position != -1)
    {
        strcpy(message, transmited_message.content);
        transmited_message.position = -1;
        return 1;
    }
    return 0;
}

int localLoraRead(char *message)
{
    return loraRead(message);
}

int remoteLoraRead(char *message)
{
    return loraRead(message);
}

void loraPrint(const char *message)
{
    if (iRandom(4)) // 1 in 4 chances of the message being lost in transmission!
    {
        strcpy(transmited_message.content, message);
        transmited_message.position = 0;
    }
}

void localLoraPrint(const char *message)
{
    loraPrint(message);
}

void remoteLoraPrint(const char *message)
{
    loraPrint(message);
}

void redLightOn()
{
    if (!red_state && !red_state++)
        printf("Red ON      - %d times\n", ++total_reds);
}

void redLightOff()
{
    if (red_state && red_state--)
        printf("Red Off     - %d times\n", total_reds);
}

void greenLightOn()
{
    if (!green_state && !green_state++)
        printf("Green ON    - %d times\n", ++total_greens);
}

void greenLightOff()
{
    if (green_state && green_state--)
        printf("Green Off   - %d times\n", total_greens);
}

void blueLightOn()
{
    if (!blue_state && !blue_state++)
        printf("Blue ON     - %d times\a\n", ++total_blues);    // You've Got Mail
}

void blueLightOff()
{
    if (blue_state && blue_state--)
        printf("Blue Off    - %d times\n", total_blues);
}


#else   // Arduino specifics

int serialRead(char *serial_read)
{    
    
    return 0;
}

void numberToText(char *text, int number)
{
      
}

int textToNumber(const char *text)
{
    return 0;
}

int serialRead(char *message)
{
    return 0;
}

void serialPrint(const char *message)
{
    
}

void serialPrintln(const char *message)
{
    
}

int loraRead(char *message)
{
    
}

void loraPrint(const char *message)
{
    
}


#endif




#if     SETUP == LOCAL


void setupSetup()
{
    
    
}


void redLightOn()
{
    
}

void redLightOff()
{
    
}

void greenLightOn()
{
    
}

void greenLightOff()
{
    
}

void blueLightOn()
{
    
}

void blueLightOff()
{
    
}



#elif   SETUP == REMOTE

void setupSetup()
{
    
}

void redLightOn() {}
void redLightOff() {}
void greenLightOn() {}
void greenLightOff() {}
void blueLightOn() {}
void blueLightOff() {}


#endif



