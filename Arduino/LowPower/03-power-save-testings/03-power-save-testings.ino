#include <LowPower.h>   // “Low-Power” by Rocket Scream Electronics

#define COM_BAUD    (unsigned long)9600

void ledBlink(unsigned long duty_duration)
{
    digitalWrite(LED_BUILTIN, HIGH);
    delay(duty_duration);
    digitalWrite(LED_BUILTIN, LOW);
    delay(duty_duration);
}


void setup()
{
    int pins_to_turn_low[] = {0, 1, 3, 4, 5, 6, 7, 8};
    int pins_to_low_size = sizeof(pins_to_turn_low)/sizeof(pins_to_turn_low[0]);
    for (int pin_low = 0; pin_low < pins_to_low_size; pin_low++)
    {
        pinMode(pins_to_turn_low[pin_low], OUTPUT);
        digitalWrite(pins_to_turn_low[pin_low], LOW);
    }
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(COM_BAUD);
    while (!Serial)
    {
        delay(2000);
        Serial.begin(COM_BAUD);
    }
    Serial.print("Serial com connected at: ");
    Serial.println(COM_BAUD);

    ledBlink(500);
}

// https://www.electrosoftcloud.com/en/reduce-power-consumption-on-arduino/
// https://techexplorations.com/blog/arduino/power-saving-techniques-arduino-uno/

//  Arduino Power modes:
//    * Idle
//    * ADC noise reduction
//    * Power-down
//    * Power-save
//    * Standby
//    * Extended standby

#define SERIAL      true
#define MILLIS      true

void loop()
{
    const size_t periods_to_run[] = {9};
    const size_t periods_size = sizeof(periods_to_run) / sizeof(periods_to_run[0]);
    const size_t sleep_types_to_run[] = {0, 1, 2, 3, 4, 5};
    const size_t sleep_types_size = sizeof(sleep_types_to_run) / sizeof(sleep_types_to_run[0]);
    
    const unsigned long duties_durations[] = {10, 20, 30, 40, 50, 60};
    const unsigned long cycles_8s = 2; // 15 is exactly 2 minutes (120 seconds)
                                       //  0                    1                    2                    3   
    const unsigned long sleep_repeats[] = {cycles_8s*8000/15, cycles_8s*8000/30, cycles_8s*8000/60, cycles_8s*8000/120,
                                       //  4             5  
                                           cycles_8s*32, cycles_8s*16,
                                       //  6            7            8            9            10 (forever)
                                           cycles_8s*8, cycles_8s*4, cycles_8s*2, cycles_8s*1};
    const unsigned long duties_size = sizeof(duties_durations) / sizeof(duties_durations[0]);

    size_t i;
    for (size_t sleep_type = 0; sleep_type < sleep_types_size; sleep_type++)
    {
        i = sleep_types_to_run[sleep_type];
        #if SERIAL
            Serial.print("Sleep type: ");
            Serial.print(i);
            Serial.print("\tSleep duration: ");
            Serial.println(cycles_8s*8);
            Serial.flush();
        #endif
        for (size_t sleep_type = 0; sleep_type < i + 1; sleep_type++)
            ledBlink(500);
        size_t j;
        for (size_t period = 0; period < periods_size; period++)
        {
            j = periods_to_run[period];
            for (size_t blinks = 0; blinks < j + 1; blinks++)
                ledBlink(100);
            #if SERIAL
                Serial.print("\tPeriod type [START]: ");
                Serial.println(j);
                Serial.flush();
            #endif
            switch(i)
            {
                case 0: // Idle mode                    // 10 mA
                    for (size_t repeat = 0; repeat < sleep_repeats[j]; repeat++)
                    {
                        LowPower.idle(j, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF,
                                         SPI_OFF, USART0_OFF, TWI_OFF);
                    # if MILLIS
                        Serial.println(millis()/1000);
                        Serial.flush();
                    # endif
                    }
                    break;
                case 1: // ADC noise reduction          // 9 mA
                    for (size_t repeat = 0; repeat < sleep_repeats[j]; repeat++)
                    {
                        LowPower.adcNoiseReduction(j, ADC_OFF, TIMER2_OFF);
                    # if MILLIS
                        Serial.println(millis()/1000);
                        Serial.flush();
                    # endif
                    }
                    break;
                case 2: // Power-down mode              // 4 mA
                    for (size_t repeat = 0; repeat < sleep_repeats[j]; repeat++)
                    {
                        LowPower.powerDown(j, ADC_OFF, BOD_OFF);
                    # if MILLIS
                        Serial.println(millis()/1000);
                        Serial.flush();
                    # endif
                    }
                    break;
                case 3: // Power-save mode              // 4 mA
                    for (size_t repeat = 0; repeat < sleep_repeats[j]; repeat++)
                    {
                        LowPower.powerSave(j, ADC_OFF, BOD_OFF, TIMER2_OFF);
                    # if MILLIS
                        Serial.println(millis()/1000);
                        Serial.flush();
                    # endif
                    }
                    break;
                case 4: // Standby mode                 // 5 mA
                    for (size_t repeat = 0; repeat < sleep_repeats[j]; repeat++)
                    {
                        LowPower.powerStandby(j, ADC_OFF, BOD_OFF);
                    # if MILLIS
                        Serial.println(millis()/1000);
                        Serial.flush();
                    # endif
                    }
                    break;
                case 5: // Extended standby mode        // 5 mA
                    for (size_t repeat = 0; repeat < sleep_repeats[j]; repeat++)
                    {
                        LowPower.powerExtStandby(j, ADC_OFF, BOD_OFF, TIMER2_OFF);
                    # if MILLIS
                        Serial.println(millis()/1000);
                        Serial.flush();
                    # endif
                    }
                    break;
            }
            #if SERIAL
                Serial.print("\tPeriod type [FINISH]: ");
                Serial.println(j);
                Serial.flush();
            #endif
        }
    }
}

//enum period_t
//{
//    SLEEP_15MS,
//    SLEEP_30MS,
//    SLEEP_60MS,
//    SLEEP_120MS,
//    SLEEP_250MS,
//    SLEEP_500MS,
//    SLEEP_1S,
//    SLEEP_2S,
//    SLEEP_4S,
//    SLEEP_8S,
//    SLEEP_FOREVER
//};
