#include "Talker.h"

// Define the commands (stored in RAM)
const Talker::Command Talker::runCommands[] = {
    {"buzz",  "Triggers buzzing",  &Talker::buzz},
    {"print", "Prints duration",   &Talker::printDuration}
};

// Execute a command
String Talker::execute(const char* cmd) {
    for (const Command& c : runCommands) {
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

String Talker::printDuration() {
    return "Duration: " + String(_duration);
}
