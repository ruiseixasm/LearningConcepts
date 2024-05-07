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

size_t readSerialUntil(const char *characters, char *buffer, size_t length)
{
    return serialRead(buffer);
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

size_t sleepForSeconds_8s(unsigned long sleep_seconds)
{
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

void arduinoSetup()
{
    Serial.begin(COM_BAUD);
    while (!Serial)
    {
        delay(2000);
        Serial.begin(COM_BAUD);
    }
    Serial.print("Serial com connected at: ");
    Serial.println(COM_BAUD);
}

int serialRead(char *text)
{
    int i = 0;
    if (Serial.available() > 0)
    {
        unsigned long last_read_millis = millis();
        
        while (millis() - last_read_millis < 3 && i < 15)
        {
            if (Serial.available() > 0)
            {
                text[i] = (char)Serial.read();
                if (text[i] == '\n' || text[i] == '\t' || text[i] == '\r')
                    break;
                last_read_millis = millis();
                i++;
            }
        }
    }
    text[i] = '\0';
    return i;
}

size_t readSerialUntil(const char *characters, char *buffer, size_t length)
{
    size_t i = 0;
    if (Serial.available() > 0)
    {
        unsigned long last_read_millis;
        do
        {
            if (Serial.available() > 0)
            {
                buffer[i] = (char)Serial.read();
                if (strchr(characters, buffer[i]))
                    break;
                last_read_millis = millis();
                i++;
            }
        } while (millis() - last_read_millis < 3 && i < length - 1);
    }
    buffer[i] = '\0';
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
    // try to parse packet
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
        for (; LoRa.available() && i < 15; i++) {
            message[i] = (char)LoRa.read();
            if (message[i] == '\n' || message[i] == '\t' || message[i] == '\r')
                break;
        }
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

int loraTurnOn()
{
    static char red_on;
    static char green_on;
    if (!(red_state == 1 && green_state == 1))
    {
        red_on = red_state;
        green_on = green_state;
    }
    digitalWrite(powerPin, HIGH);
    delay(LORA_DELAY);  // Small delay to let lora module start
    int connections_tries = 5;
    while (!LoRa.begin(LORA_HZ) && connections_tries-- > 0)
    {
        Serial.print("Starting LoRa failed! (");
        Serial.print(connections_tries + 1);
        Serial.println(")");
        Serial.println("Trying again shortly...");
        redLightOn();
        greenLightOn();
        delay(LORA_DELAY*4);  // Small delay to let lora module start
    }
    if (connections_tries > 0)
    {
        // Set Lora parameters
    #if SETUP == REMOTE
        LoRa.setTxPower(17, PA_OUTPUT_PA_BOOST_PIN);    // Supported values are between 2 and 17 for PA_OUTPUT_PA_BOOST_PIN
    #endif
        LoRa.setSpreadingFactor(12);        // ranges from 6-12,default 7 see API docs
        LoRa.setSignalBandwidth(62.5E3);    // 62.5 kHz
        LoRa.setCodingRate4(5);             //min 5 - max 8
        //setPreambleLength(long length);
        //setSyncWord(int sw);
        //LoRa.enableCrc();
        //LoRa.disableCrc();
        //enableInvertIQ();
        //disableInvertIQ()
  
        Serial.println("LoRa connected!");
        if (!red_on)
            redLightOff();
        if (!green_on)
            greenLightOff();
        delay(LORA_DELAY);  // Small delay to let lora module warm up...
        return 1;
    }
    else
    {
        delay(LORA_DELAY);  // Small delay before abrupt turn power off
        digitalWrite(powerPin, LOW);
        Serial.println("LoRa failled to connect!");
        return 0;
    }
}

void loraTurnOff()
{
    delay(LORA_DELAY);  // Small delay to let lora module start
    digitalWrite(powerPin, LOW);
    Serial.println("LoRa turned OFF!");
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
    pinMode(redPin, OUTPUT);
    digitalWrite(redPin, LOW);
    pinMode(greenPin, OUTPUT);
    digitalWrite(greenPin, LOW);
    pinMode(bluePin, OUTPUT);
    digitalWrite(bluePin, LOW);
    pinMode(powerPin, OUTPUT);
    digitalWrite(powerPin, LOW);
    pinMode(buzzerPin, OUTPUT);
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);

    arduinoSetup();

    Serial.println("Configured as RECEIVER! (LOCAL)\n");
    
    redLightOn();
    greenLightOn();
    blueLightOn();
    greenLightOff();
    blueLightOff();
    
    // Set pint 2 concerning DIO0 as floating (like disconnected)
    //pinMode(lora_dio0, INPUT);    
    
    localLoraTurnOn();

    Serial.println("STARTED");
}

int ledLightIntensity()
{
    return -1;  // Local receiver reads no light
}

int localLoraRead(char *message)
{
    if (local_lora_power && loraRead(message))
    {
        // Received a packet, print RSSI of packet
        Serial.print("Received packet '");
        Serial.print(message);
        Serial.print("' with RSSI ");
        Serial.println(LoRa.packetRssi());
        return 1;
    }
    return 0;
}

void localLoraPrint(const char *message)
{
    if (local_lora_power)
    {
        loraPrint(message);
        Serial.print("Sent packet '");
        Serial.print(message);
        Serial.println("'");
    }
}

int remoteLoraRead(char *message)
{
    return 0;   // Does nothing because it's local
}

void remoteLoraPrint(const char *message)
{
    // Does nothing because it's local
}

void localLoraTurnOn()
{
    if (!local_lora_power)
    {
        Serial.println("Turning ON LOCAL LoRa...");
        local_lora_power = (char)loraTurnOn();
    }
}

void remoteLoraTurnOn()
{
    // Does nothing because it's local
}

void localLoraTurnOff()
{
    if (local_lora_power && local_lora_power--)
        Serial.println("Turning OFF LOCAL LoRa...");
    loraTurnOff();
}

void remoteLoraTurnOff()
{
    // Does nothing because it's local
}

void redLightOn()
{
    if (!red_state && !red_state++)
    {
        Serial.print("Red ON        - ");
        Serial.print(++total_reds);
        Serial.println(" times");
        digitalWrite(redPin, HIGH);
    }
}

void redLightOff()
{
    if (red_state && red_state--)
    {
        Serial.print("Red OFF       - ");
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
        Serial.print("Green OFF     - ");
        Serial.print(total_greens);
        Serial.println(" times");
        digitalWrite(greenPin, LOW);
    }
}

void blueLightOn()
{
    if (!blue_state && !blue_state++)
    {
        Serial.print("Blue ON       - ");
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
    delay(BUZZER_DUR);
    Serial.println("Buzzer OFF");
    digitalWrite(buzzerPin, LOW);
}

int buttonsRead()
{
    return 0;   // Local has no buttons
}

size_t sleepForSeconds_8s(unsigned long sleep_seconds)
{
    return 0;
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
    pinMode(powerPin, OUTPUT);
    digitalWrite(powerPin, LOW);
    pinMode(lightPin, OUTPUT);          // set pin to the light
    digitalWrite(lightPin, LOW);        // Turn off the light
    
    int pins_to_turn_low[] = {0, 1, 3, 4, 5, 6, 7, 8};
    int pins_to_low_size = sizeof(pins_to_turn_low)/sizeof(pins_to_turn_low[0]);
    for (int pin_low = 0; pin_low < pins_to_low_size; pin_low++)
    {
        pinMode(pins_to_turn_low[pin_low], OUTPUT);
        digitalWrite(pins_to_turn_low[pin_low], LOW);
    }
    char *a_pins_to_turn_low[] = {"A1", "A2", "A3", "A4", "A5", "A6", "A7"};
    int a_pins_to_low_size = sizeof(pins_to_turn_low)/sizeof(pins_to_turn_low[0]);
    for (int pin_low = 0; pin_low < pins_to_low_size; pin_low++)
    {
        pinMode(a_pins_to_turn_low[pin_low], OUTPUT);
        digitalWrite(a_pins_to_turn_low[pin_low], LOW);
    }
    
    pinMode(blueButton, INPUT);     // INPUT_PULLDOWN doesn't exist, only INPUT_PULLUP!
    pinMode(greenButton, INPUT);
    
    arduinoSetup();
    
    Serial.println("Configured as SENDER! (REMOTE)\n");
    
    // Set pint 2 concerning DIO0 as floating (like disconnected)
    //pinMode(lora_dio0, INPUT);    
    
    Serial.println("STARTED");

    // To know that the script started succesfully
    pinMode(13, OUTPUT);          // set onboard pin to the light
    digitalWrite(13, HIGH);
    delay(2000);
    digitalWrite(13, LOW);
    
}

int ledLightIntensity()
{
    digitalWrite(lightPin, HIGH);
    delay(10);  // allows liht warm up
    // read the analog in value:
    int sensorValue = analogRead(analogInPin);
    // Turn off the light
    digitalWrite(lightPin, LOW);
    // print the results to the Serial Monitor:
    Serial.print("Sensor value = ");
    Serial.println(sensorValue);
    return sensorValue; // Returns final reading
}

int localLoraRead(char *message)
{
    return 0;   // Does nothing because it's remote
}

void localLoraPrint(const char *message)
{
    // Does nothing because it's remote
}

int remoteLoraRead(char *message)
{
    if (remote_lora_power)
        return loraRead(message);
    return 0;
}

void remoteLoraPrint(const char *message)
{
    if (remote_lora_power)
    {
        loraPrint(message);
        Serial.print("Sent packet '");
        Serial.print(message);
        Serial.println("'");
    }
}

void localLoraTurnOn()
{
    // Does nothing because it's remote
}

void remoteLoraTurnOn()
{
    if (!remote_lora_power)
    {
        Serial.println("Turning ON REMOTE LoRa...");
        remote_lora_power = (char)loraTurnOn();
    }
}

void localLoraTurnOff()
{
    // Does nothing because it's remote
}

void remoteLoraTurnOff()
{
    if (remote_lora_power && remote_lora_power--)
        Serial.println("Turning OFF REMOTE LoRa...");
    loraTurnOff();
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
    static int last_pressed_buttons = 0;
    unsigned long last_pressed_millis = millis();
    for (int pressed_buttons = digitalRead(greenButton) << 1 | digitalRead(blueButton);
            pressed_buttons != last_pressed_buttons;
            pressed_buttons = digitalRead(greenButton) << 1 | digitalRead(blueButton))
        if (millis() - last_pressed_millis > 100)
            return last_pressed_buttons = pressed_buttons;
    
    return 0;
}

size_t sleepForSeconds_8s(unsigned long sleep_seconds)
{
    // Makes sure all Serial buffer is fushed (serial leds became off)
    Serial.flush();
    
    // in 450 runs of 8s sleep, 3600 seconds, gained 403 seconds
    // IGNORE - Extra correction due to delay of 2 in 300 seconds, same as lost 24 in 3600 seconds (to subtract)
    const double correction_factor = 3600.0/(3600 + 403);

    size_t sleep_cycles_8s = (size_t)(correction_factor * sleep_seconds / 8);

    // Arduino Power-down mode:
    for (size_t i = sleep_cycles_8s; i; i--)
        LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);

    return sleep_cycles_8s;
}

#endif
