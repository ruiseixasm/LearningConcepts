#include "JsonTalkie.hpp"


Manifesto manifesto;
JsonTalkie json_talkie(&manifesto)


float _duration = 0.5f;  // Example variable

// Command implementations
const char* buzz() {
    static char buffer[32];  // Reusable buffer
    snprintf(buffer, sizeof(buffer), "Buzzed for %.1fs", _duration);
    delay(_duration * 1000);
    return buffer;
}

const char* setDuration(const char* duration) {
    _duration = String(duration).toFloat();
    static char buffer[32];  // Reusable buffer
    snprintf(buffer, sizeof(buffer), "Set duration: %ss", floatToStr(_duration));
    return buffer;
}

const char* getDuration() {
    static char buffer[32];  // Reusable buffer
    snprintf(buffer, sizeof(buffer), "Get duration: %ds", _duration);
    return buffer;
}


void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    manifesto.runCommands = {
        {"buzz", "Triggers buzzing", &buzz}
    }
    manifesto.setCommands = {
        {"duration", "Sets duration", &setDuration}
    }
    manifesto.getCommands = {
        {"duration", "Gets duration", &getDuration}
    }


}

void loop() {
    
}
