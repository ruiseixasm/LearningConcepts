#include "JsonTalkie.hpp"


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


// Define the commands (stored in RAM)
const Talker Manifesto::talker = {
    'Buzzer', 'This device does a 500ms buzz!'
};

const Run Manifesto::runCommands[] = {
    {"buzz", "Triggers buzzing", buzz}
};
const size_t Manifesto::runSize = sizeof(Manifesto::runCommands) / sizeof(Run);

const Set Manifesto::setCommands[] = {
    {"duration", "Sets duration", setDuration}
};
const size_t Manifesto::setSize = sizeof(Manifesto::setCommands) / sizeof(Set);

const Get Manifesto::getCommands[] = {
    {"duration", "Gets duration", getDuration}
};
const size_t Manifesto::getSize = sizeof(Manifesto::getCommands) / sizeof(Get);

// Alternative: Direct lambda assignment (C++11)
bool (*Manifesto::echo)(StaticJsonDocument<256>*, const char*) = 
    [](StaticJsonDocument<256>* msg, const char* res) {
        Serial.println((*msg)["response"].as<String>()); // The magic fix
        return true;
    };

// JsonTalkie json_talkie(&manifesto)


void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);


}

void loop() {
    
}
