#include <LowPower.h>   // “Low-Power” by Rocket Scream Electronics

#define COM_BAUD    (unsigned long)9600

void ledBlink(){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
}

void setup(){
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(COM_BAUD);
    while (!Serial)
    {
        delay(2000);
        Serial.begin(COM_BAUD);
    }
    Serial.print("Serial com connected at: ");
    Serial.println(COM_BAUD);
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

void loop(){
    for (int count = 0; count < 1; count++)
        ledBlink();
    // Arduino Idle mode
//    LowPower.idle(SLEEP_8S, // SLEEP_15MS, SLEEP_30MS, SLEEP_60MS
//                            // SLEEP_120MS, SLEEP_250MS, SLEEP_500MS
//                            // SLEEP_1S, SLEEP_2S, SLEEP_4S, SLEEP_8S
//                            // SLEEP_FOREVER
//                  ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF,
//                  SPI_OFF, USART0_OFF, TWI_OFF);

    // Arduino Power-down mode:
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
    Serial.print("Wake up at: ");
    Serial.print(millis());
    Serial.println("ms");
}
