#include <LowPower.h>   // “Low-Power” by Rocket Scream Electronics

#define COM_BAUD    (unsigned long)9600

void ledBlink()
{
    digitalWrite(LED_BUILTIN, HIGH);
    delay(250);
    digitalWrite(LED_BUILTIN, LOW);
}

period_t millisToPeriod(unsigned long duration) // period_t it's an enum from the library
{
    if (duration >= 8*1000)
        return SLEEP_8S;    // 9    // maximum value possible
    if (duration >= 4*1000)
        return SLEEP_4S;    // 8
    if (duration >= 2*1000)
        return SLEEP_2S;    // 7
    if (duration >= 1*1000)
        return SLEEP_1S;    // 6
    if (duration >= 500)
        return SLEEP_500MS; // 5
    if (duration >= 250)
        return SLEEP_250MS; // 4
    if (duration >= 120)
        return SLEEP_120MS; // 3
    if (duration >= 60)
        return SLEEP_60MS;  // 2
    if (duration >= 30)
        return SLEEP_30MS;  // 1
    
    return SLEEP_15MS;      // 0    // minimum value possible
}

size_t sleepForSeconds(unsigned long sleep_seconds)
{                                               //  0  1  2  3  4  5  6  7  8  9  10
    const unsigned long seconds_powered_down[11] = {1, 1, 1, 1, 1, 1, 1, 2, 4, 8, 0};
    period_t power_down_period;
    size_t total_sleeps = 0;
    
    while (sleep_seconds)
    {
        power_down_period = millisToPeriod(sleep_seconds*1000);
        sleep_seconds -= seconds_powered_down[power_down_period];
        total_sleeps++;
        
        // Arduino Power-down mode:
        LowPower.powerDown(power_down_period, ADC_OFF, BOD_OFF);
    }
    return total_sleeps;
}

size_t sleepForSeconds_8s(unsigned long sleep_seconds)
{
    unsigned long called_at = millis();
    // Arduino Power-down mode:
    for (size_t i = sleep_seconds / 8; i; i--)
        LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);

    //delay(sleep_seconds%8 * 1000 - (millis() - called_at));
    return (size_t)sleep_seconds / 8;
}

size_t g_total_sleeps = 0;

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    Serial.begin(COM_BAUD);
    while (!Serial)
    {
        delay(2000);
        Serial.begin(COM_BAUD);
    }
    Serial.print("Serial com connected at: ");
    Serial.println(COM_BAUD);
}

void loop()
{
    ledBlink();
    g_total_sleeps = sleepForSeconds_8s(60);
    Serial.print("\nWaked up at: ");
    Serial.print(millis());
    Serial.println("ms");
    Serial.print("Did a total of ");
    Serial.print(g_total_sleeps);
    Serial.println(" sleeps");
}
