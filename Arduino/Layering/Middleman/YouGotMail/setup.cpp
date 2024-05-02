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

int serialRead(char *text)
{
    int i = 0;
    for (; i < 16 && Serial.available() > 0; i++) {
        text[i] = (char)Serial.read();
    }
    text[i] = '\0';
    return i;
}

void numberToText(char *text, int number)
{
    itoa(number, text, 10);
}

int textToNumber(const char *text)
{
    return atoi(text);
}

void serialPrint(const char *text)
{
    Serial.print(text);
}

void serialPrintln(const char *text)
{
    Serial.println(text);
}

int loraRead(char *message)
{
    int i = 0;
    for (; i < 16 && LoRa.available(); i++)
    {
        message[i] = (char)LoRa.read();
    }
    message[i] = '\0';
    return i;
}

void loraPrint(const char *message)
{
    LoRa.beginPacket();
    LoRa.print(message);
    LoRa.endPacket();
}


#endif




#if     SETUP == LOCAL

// These constants won't change. They're used to give names to the pins used:
const int redPin    = 7;    // RED LED pin
const int greenPin  = 6;    // GREEN LED pin
const int bluePin   = 5;    // BLUE LED pin     (You've Got Mail)
const int buzzerPin = 4;    // Buzzer pin       (You've Got Mail)

void setupSetup()
{
    Serial.println("Configured as RECEIVER! (LOCAL)");
    
    pinMode(redPin, OUTPUT);
    digitalWrite(redPin, LOW);
    pinMode(greenPin, OUTPUT);
    digitalWrite(greenPin, LOW);
    pinMode(bluePin, OUTPUT);
    digitalWrite(bluePin, LOW);
    pinMode(buzzerPin, OUTPUT);
    digitalWrite(buzzerPin, LOW);
    
    Serial.begin(COM_BAUD);
    while (!Serial);
    Serial.print("Serial com connected at: ");
    Serial.println(COM_BAUD);
    
    if (!LoRa.begin(LORA_HZ)) {
        Serial.println("Starting LoRa failed!");
        while (1);
    }
    Serial.println("LoRa connected!");
}

int ledLightIntensity()
{
    return -1;  // Local receiver reads no light
}

int localLoraRead(char *message)
{
    return loraRead(message);
}

void localLoraPrint(const char *message)
{
    loraPrint(message);
}

int remoteLoraRead(char *message)
{
    // Does nothing because it's local
}

void remoteLoraPrint(const char *message)
{
    // Does nothing because it's local
}


void redLightOn()
{
    digitalWrite(redPin, HIGH);
}

void redLightOff()
{
    digitalWrite(redPin, LOW);
}

void greenLightOn()
{
    digitalWrite(greenPin, HIGH);
}

void greenLightOff()
{
    digitalWrite(greenPin, LOW);
}

void blueLightOn()
{
    digitalWrite(bluePin, HIGH);
    triggerBuzzer();
}

void blueLightOff()
{
    digitalWrite(bluePin, LOW);
}

void triggerBuzzer()
{
    digitalWrite(buzzerPin, HIGH);
    delay(500);
    digitalWrite(buzzerPin, LOW);
}



#elif   SETUP == REMOTE

static int sensorValue = 0; // value read from the pot
const int lightPin = 8;     // LED pint
const int analogInPin = A0; // (14) Analog input pin that the potentiometer is attached to

void setupSetup()
{
    Serial.println("Configured as SENDER! (REMOTE)");
    
    pinMode(lightPin, OUTPUT);          // set pin to the light
    digitalWrite(lightPin, LOW);        // Turn off the light
    
    Serial.begin(COM_BAUD);
    while (!Serial);
    Serial.print("Serial com connected at: ");
    Serial.println(COM_BAUD);
    
    if (!LoRa.begin(LORA_HZ)) {
        Serial.println("Starting LoRa failed!");
        while (1);
    }
    Serial.println("LoRa connected!");
    
}

int ledLightIntensity()
{
    return 0;
}

int localLoraRead(char *message)
{
    // Does nothing because it's remote
}

void localLoraPrint(const char *message)
{
    // Does nothing because it's remote
}

int remoteLoraRead(char *message)
{
    return loraRead(message);
}

void remoteLoraPrint(const char *message)
{
    loraPrint(message);
}


void redLightOn() {}
void redLightOff() {}
void greenLightOn() {}
void greenLightOff() {}
void blueLightOn() {}
void blueLightOff() {}
void triggerBuzzer() {}

#endif



