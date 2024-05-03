#include "setup.h"

// DUMMY
// DUMMY
// DUMMY
// DUMMY
// DUMMY
// DUMMY
// DUMMY
// DUMMY
// DUMMY
// DUMMY
// DUMMY
// DUMMY

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
    
    localLoraTurnOn();
    transmited_message.position = -1;
    last_serial_seconds = now_seconds();
    printf("\n\tSTARTED\n\n");
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

char *numberToText(char *text, int number)
{
    sprintf(text, "%d", number);
    return text;
}

int textToNumber(const char *text)
{
    return atoi(text);
}

int serialRead(char *text)
{
    if (time(NULL) - last_serial_seconds > 50 && !iRandom(4))
    {
        if (iRandom(4))
            if (iRandom(2))
                strcpy(text, "YGM4444");
            else
                strcpy(text, "3333");
        else
            if (iRandom(4))
                strcpy(text, "ON");
            else
                strcpy(text, "OFF");
            
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
    if (local_lora_power > 0 && transmited_message.position != -1)
    {
        strcpy(message, transmited_message.content);
        transmited_message.position = -1;
        return 1;
    }
    else
        transmited_message.position = -1;
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
    if (remote_lora_power > 0 && iRandom(4)) // 1 in 4 chances of the message being lost in transmission!
    {
        strcpy(transmited_message.content, message);
        transmited_message.position = 0;
    }
    else
        transmited_message.position = -1;
}

void localLoraPrint(const char *message)
{
    loraPrint(message);
}

void remoteLoraPrint(const char *message)
{
    loraPrint(message);
}

void loraTurnOn()
{
    delay(LORA_DELAY);  // Small delay to let lora module start
    printf("LoRa connected!\n");
}

void loraTurnOff()
{
    // Doesn't nothing else than turning pin LOW
}

void localLoraTurnOn()
{
    if (!local_lora_power && !local_lora_power++)
    {
        printf("Turning ON LOCAL LoRa...\n");
        loraTurnOn();
    }
}

void remoteLoraTurnOn()
{
    if (!remote_lora_power && !remote_lora_power++)
    {
        printf("Turning ON REMOTE LoRa...\n");
        loraTurnOn();
    }
}

void localLoraTurnOff()
{
    if (local_lora_power && local_lora_power--)
    {
        loraTurnOff();
        printf("LOCAL LoRa turned OFF!\n");
    }
}

void remoteLoraTurnOff()
{
    if (remote_lora_power && remote_lora_power--)
    {
        loraTurnOff();
        printf("REMOTE LoRa turned OFF!\n");
    }
}

void redLightOn()
{
    if (!red_state && !red_state++)
        printf("Red ON      - %d times\n", ++total_reds);
}

void redLightOff()
{
    if (red_state && red_state--)
        printf("Red OFF     - %d times\n", total_reds);
}

void greenLightOn()
{
    if (!green_state && !green_state++)
        printf("Green ON    - %d times\n", ++total_greens);
}

void greenLightOff()
{
    if (green_state && green_state--)
        printf("Green OFF   - %d times\n", total_greens);
}

void blueLightOn()
{
    if (!blue_state && !blue_state++)
        printf("Blue ON     - %d times\a\n", ++total_blues);    // You've Got Mail
}

void blueLightOff()
{
    if (blue_state && blue_state--)
        printf("Blue OFF    - %d times\n", total_blues);
}

int buttonsRead()
{
    static unsigned long last_button_seconds = now_seconds() - 20;
    static int pressed_buttons;
    
    if (time(NULL) - last_button_seconds > 50 && !iRandom(4))
    {
        if (iRandom(4))
            if (iRandom(2))
                pressed_buttons = 0b01;
            else
                pressed_buttons = 0b10;
        else
            pressed_buttons = 0b11;
            
        last_button_seconds = time(NULL);
        return pressed_buttons;
    }
    
    return 0;
}

// ARDUINO
// ARDUINO
// ARDUINO
// ARDUINO
// ARDUINO
// ARDUINO
// ARDUINO
// ARDUINO
// ARDUINO
// ARDUINO
// ARDUINO

#else   // Arduino specifics

int serialRead(char *text)
{
    int i = 0;
    for (; i < 15 && Serial.available() > 0; i++) {
        text[i] = (char)Serial.read();
        if (text[i] == '\n' || text[i] == '\t' || text[i] == '\r')
            break;
        delay(2); // Waits for next byte to fill the buffer. 1 baud = 1 byte per second.
    }
    text[i] = '\0';
    return i;
}

char *numberToText(char *text, int number)
{
    itoa(number, text, 10);
    return text;
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

void loraTurnOn()
{
    char red_on = red_state;
    char green_on = green_state;
    digitalWrite(powerPin, HIGH);
    delay(LORA_DELAY);  // Small delay to let lora module start
    while (!LoRa.begin(LORA_HZ))
    {
        Serial.println("Starting LoRa failed!");
        Serial.println("Trying again latter...");
        digitalWrite(powerPin, LOW);
        redLightOn();
        greenLightOn();
        delay((unsigned long)5 * 60 * 1000);
        digitalWrite(powerPin, HIGH);
        delay(LORA_DELAY);  // Small delay to let lora module start
    }
    Serial.println("LoRa connected!");
    if (!red_on)
        redLightOff();
    if (!green_on)
        greenLightOff();
}

void loraTurnOff()
{
    digitalWrite(powerPin, LOW);
}

#endif

// LOCAL
// LOCAL
// LOCAL
// LOCAL
// LOCAL
// LOCAL
// LOCAL
// LOCAL
// LOCAL
// LOCAL
// LOCAL

#if     SETUP == LOCAL

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
    pinMode(powerPin, OUTPUT);
    digitalWrite(powerPin, LOW);

    Serial.begin(COM_BAUD);
    while (!Serial);
    Serial.print("Serial com connected at: ");
    Serial.println(COM_BAUD);
    
    redLightOn();
    greenLightOn();
    blueLightOn();
    greenLightOff();
    blueLightOff();
    
    localLoraTurnOn();

    Serial.println("STARTED");
}

int ledLightIntensity()
{
    return -1;  // Local receiver reads no light
}

int localLoraRead(char *message)
{
    if (!loraRead(message))
        return 0;
    // Received a packet, print RSSI of packet
    Serial.print("Received packet '");
    Serial.print(message);
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
    return 1;
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

void localLoraTurnOn()
{
    if (!local_lora_power && !local_lora_power++)
    {
        Serial.println("Turning ON LOCAL LoRa...");
        loraTurnOn();
    }
}

void remoteLoraTurnOn()
{
    // Does nothing because it's local
}

void localLoraTurnOff()
{
    if (local_lora_power && local_lora_power--)
    {
        loraTurnOff();
        Serial.println("LOCAL LoRa turned OFF!");
    }
}

void remoteLoraTurnOff()
{
    // Does nothing because it's local
}

void redLightOn()
{
    if (!red_state && !red_state++)
    {
        Serial.print("Red ON      - ");
        Serial.print(++total_reds);
        Serial.println(" times");
        digitalWrite(redPin, HIGH);
    }
}

void redLightOff()
{
    if (red_state && red_state--)
    {
        Serial.print("Red ON      - ");
        Serial.print(total_reds);
        Serial.println(" times");
        digitalWrite(redPin, LOW);
    }
}

void greenLightOn()
{
    if (!green_state && !green_state++)
    {
        Serial.print("Green ON      - ");
        Serial.print(++total_greens);
        Serial.println(" times");
        digitalWrite(greenPin, HIGH);
    }
}

void greenLightOff()
{
    if (green_state && green_state--)
    {
        Serial.print("Green OFF      - ");
        Serial.print(total_greens);
        Serial.println(" times");
        digitalWrite(greenPin, LOW);
    }
}

void blueLightOn()
{
    if (!blue_state && !blue_state++)
    {
        Serial.print("Blue ON      - ");
        Serial.print(++total_blues);
        Serial.println(" times");
        digitalWrite(bluePin, HIGH);
        triggerBuzzer();
    }
}

void blueLightOff()
{
    if (blue_state && blue_state--)
    {
        Serial.print("Blue OFF      - ");
        Serial.print(total_blues);
        Serial.println(" times");
        digitalWrite(bluePin, LOW);
    }
}

void triggerBuzzer()
{
    Serial.println("Buzzer ON");
    digitalWrite(buzzerPin, HIGH);
    delay(500);
    Serial.println("Buzzer OFF");
    digitalWrite(buzzerPin, LOW);
}

int buttonsRead()
{
    return 0;   // Local has no buttons
}

// REMOTE
// REMOTE
// REMOTE
// REMOTE
// REMOTE
// REMOTE
// REMOTE
// REMOTE
// REMOTE
// REMOTE
// REMOTE
// REMOTE
// REMOTE

#elif   SETUP == REMOTE

void setupSetup()
{
    Serial.println("Configured as SENDER! (REMOTE)");
    
    pinMode(lightPin, OUTPUT);          // set pin to the light
    digitalWrite(lightPin, LOW);        // Turn off the light
    pinMode(powerPin, OUTPUT);
    digitalWrite(powerPin, LOW);
    
    pinMode(blueButton, INPUT);
    pinMode(greenButton, INPUT);
    
    Serial.begin(COM_BAUD);
    while (!Serial);
    Serial.print("Serial com connected at: ");
    Serial.println(COM_BAUD);
    
    Serial.println("STARTED");
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

void localLoraTurnOn()
{
    // Does nothing because it's remote
}

void remoteLoraTurnOn()
{
    if (!remote_lora_power && !remote_lora_power++)
    {
        Serial.println("Turning ON REMOTE LoRa...");
        loraTurnOn();
    }
}

void localLoraTurnOff()
{
    // Does nothing because it's remote
}

void remoteLoraTurnOff()
{
    if (remote_lora_power && remote_lora_power--)
    {
        loraTurnOff();
        Serial.println("REMOTE LoRa turned OFF!");
    }
}

void redLightOn() {}
void redLightOff() {}
void greenLightOn() {}
void greenLightOff() {}
void blueLightOn() {}
void blueLightOff() {}
void triggerBuzzer() {}

int buttonsRead()
{
    int pressed_buttons = digitalRead(greenButton) << 1 | digitalRead(blueButton);
    
    if (pressed_buttons)
    {
        unsigned long last_pressed_millis = millis();
        for (int still_pressed_buttons = pressed_buttons;
                still_pressed_buttons;
                still_pressed_buttons = digitalRead(greenButton) << 1 | digitalRead(blueButton))
        {
            if (still_pressed_buttons != pressed_buttons)
            {
                last_pressed_millis = millis();
                pressed_buttons = still_pressed_buttons;
            }
            if (millis() - last_pressed_millis > 50)
                return pressed_buttons;
        }
    }
    
    return 0;
}

#endif
