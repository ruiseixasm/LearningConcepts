#include "Talker.h"

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
String Talker::run(const char* cmd) {
    for (const Run& c : runCommands) {
        if (strcmp(cmd, c.name) == 0) {
            return (this->*c.handler)();  // Call the function
        }
    }
    return "Command not found";
}
String Talker::set(const char* cmd, String value) {
    for (const Set& c : setCommands) {
        if (strcmp(cmd, c.name) == 0) {
            return (this->*c.handler)(value);  // Call the function
        }
    }
    return "Command not found";
}
String Talker::get(const char* cmd) {
    for (const Get& c : getCommands) {
        if (strcmp(cmd, c.name) == 0) {
            return (this->*c.handler)();  // Call the function
        }
    }
    return "Command not found";
}

// Command implementations
String Talker::buzz() {
    delay(_duration * 1000);
    return "Buzzed for " + String(_duration) + "s";
}

String Talker::setDuration(String duration) {
    _duration = duration.toFloat();
    return "Set duration: " + String(_duration);
}

String Talker::getDuration() {
    return "Get duration: " + String(_duration);
}
