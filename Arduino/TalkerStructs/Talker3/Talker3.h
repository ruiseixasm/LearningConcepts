#pragma once
#include <Arduino.h>

class Talker {
private:
    float _duration = 0.5f;  // Example variable

    struct Run {
        const char* name;      // "buzz", "print", etc.
        const char* desc;      // Description
        const char* (Talker::*handler)();  // Function pointer (no args)
    };

    struct Set {
        const char* name;      // "buzz", "print", etc.
        const char* desc;      // Description
        const char* (Talker::*handler)(const char*);  // Function pointer (const char*)
    };

    struct Get {
        const char* name;      // "buzz", "print", etc.
        const char* desc;      // Description
        const char* (Talker::*handler)();  // Function pointer (no args)
    };

    // Static command lists
    static const Run runCommands[];
    static const Set setCommands[];
    static const Get getCommands[];

public:
    const char* run(const char* cmd);
    const char* set(const char* cmd, const char* value);
    const char* get(const char* cmd);
    
    // Command implementations
    const char* buzz();
    const char* setDuration(const char* duration);
    const char* getDuration();
};
