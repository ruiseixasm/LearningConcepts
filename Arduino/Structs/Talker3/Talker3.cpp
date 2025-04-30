#include "Talker3.h"

// Define the commands (stored in RAM)
const Talker::Run Talker::runCommands[] = {
    {"buzz",  "Triggers buzzing",  &Talker::buzz}
};
const Talker::Set Talker::setCommands[] = {
    {"duration", "Sets duration",   &Talker::setDuration}
};
const Talker::Get Talker::getCommands[] = {
    {"duration", "Gets duration",   &Talker::getDuration}
};

// Execute a command
const char* Talker::run(const char* cmd) {
    for (const Run& c : runCommands) {
        if (strcmp(cmd, c.name) == 0) {
            return (this->*c.handler)();  // Call the function
        }
    }
    return "Command not found";
}
const char* Talker::set(const char* cmd, const char* value) {
    for (const Set& c : setCommands) {
        if (strcmp(cmd, c.name) == 0) {
            return (this->*c.handler)(value);  // Call the function
        }
    }
    return "Command not found";
}
const char* Talker::get(const char* cmd) {
    for (const Get& c : getCommands) {
        if (strcmp(cmd, c.name) == 0) {
            return (this->*c.handler)();  // Call the function
        }
    }
    return "Command not found";
}

// Command implementations
const char* Talker::buzz() {
    static char buffer[32];  // Reusable buffer
    snprintf(buffer, sizeof(buffer), "Buzzed for %.1fs", _duration);
    delay(_duration * 1000);
    return buffer;
}

// Place this ABOVE your Talker class definition
char* floatToStr(float val, uint8_t decimals = 2) {
    static char buffer[16]; // Holds "-327.00" (large enough for most cases)
    dtostrf(val, 0, decimals, buffer); // Works on ALL Arduino boards
    return buffer;
}

const char* Talker::setDuration(const char* duration) {
    _duration = String(duration).toFloat();
    static char buffer[32];  // Reusable buffer
    snprintf(buffer, sizeof(buffer), "Set duration: %ss", floatToStr(_duration));
    return buffer;
}

const char* Talker::getDuration() {
    static char buffer[32];  // Reusable buffer
    snprintf(buffer, sizeof(buffer), "Get duration: %ds", _duration);
    return buffer;
}
