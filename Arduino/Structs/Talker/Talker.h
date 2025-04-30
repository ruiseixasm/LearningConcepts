#pragma once
#include <Arduino.h>

class Talker {
private:
    float _duration = 0.5f;  // Example variable

    // Simple Command Structure
    struct Command {
        const char* name;      // "buzz", "print", etc.
        const char* desc;      // Description
        String (Talker::*handler)();  // Function pointer (no args)
    };

    // Static command lists
    static const Command runCommands[];
    static const Command setCommands[];  // If needed later

public:
    String execute(const char* cmd);
    
    // Command implementations
    String buzz();
    String printDuration();
};
