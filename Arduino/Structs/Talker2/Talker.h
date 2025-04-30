#pragma once
#include <Arduino.h>

class Talker {
private:
    float _duration = 0.5f;  // Example variable

    struct Run {
        const char* name;      // "buzz", "print", etc.
        const char* desc;      // Description
        String (Talker::*handler)();  // Function pointer (no args)
    };

    struct Set {
        const char* name;      // "buzz", "print", etc.
        const char* desc;      // Description
        String (Talker::*handler)(String);  // Function pointer (String)
    };

    struct Get {
        const char* name;      // "buzz", "print", etc.
        const char* desc;      // Description
        String (Talker::*handler)();  // Function pointer (no args)
    };

    // Static command lists
    static const Run runCommands[];
    static const Set setCommands[];
    static const Get getCommands[];

public:
    String run(const char* cmd);
    String set(const char* cmd, String value);
    String get(const char* cmd);
    
    // Command implementations
    String buzz();
    String setDuration(String duration);
    String getDuration();
};
