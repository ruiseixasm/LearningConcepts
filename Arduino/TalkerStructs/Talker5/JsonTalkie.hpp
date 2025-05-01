#ifndef TASK_SYSTEM_HPP
#define TASK_SYSTEM_HPP

#include <Arduino.h>
#include <ArduinoJson.h>

struct Talker {
    const char* name;      // Name of the Device (Talker)
    const char* desc;      // Description of the Device
};

struct Run {
    const char* name;      // "buzz", "print", etc.
    const char* desc;      // Description
    const char* (*function)();  // Function pointer (no args)
};

struct Set {
    const char* name;      // "buzz", "print", etc.
    const char* desc;      // Description
    const char* (*function)(const char*);  // Function pointer (const char*)
};

struct Get {
    const char* name;      // "buzz", "print", etc.
    const char* desc;      // Description
    const char* (*function)();  // Function pointer (no args)
};

// Place this ABOVE your Talker class definition
char* floatToStr(float val, uint8_t decimals = 2) {
    static char buffer[16]; // Holds "-327.00" (large enough for most cases)
    dtostrf(val, 0, decimals, buffer); // Works on ALL Arduino boards
    return buffer;
}

// Structure Definition
struct Manifesto {

    // constexpr means "compile-time constant"
    // Plain const doesn't guarantee compile-time initialization
    // Device variables

    // Feature	constexpr	const
    // Initialization timing	Compile-time	Runtime (or link-time)
    // Type requirements	Must be literal type	Any type
    // Storage	Typically flash/PROGMEM	Typically RAM
    // Arduino AVR	Needs special handling	Just works

    // static const Talker talker;     // Declaration only
    static const Run runCommands[];     // Declaration only
    static const size_t runSize;       // Declaration only
    static const Set setCommands[];
    static const size_t setSize;       // Declaration only
    static const Get getCommands[];
    static const size_t getSize;       // Declaration only
    // const bool (*echo)(StaticJsonDocument<256> *message, const char* response); // 256 bytes


};

// // Triggering methods definitions
// const struct* talk() {
//     return &talker;
// }

const char* run(const char* cmd) {
    for (int index = 0; index < Manifesto::runSize; ++index) {
        if (strcmp(cmd, Manifesto::runCommands[index].name) == 0) {
            return (Manifesto::runCommands[index].function)();  // Call the function
        }
    }
    return "Command not found";
}

// const char* set(const char* cmd, const char* value) {
//     for (const Set& c : setCommands) {
//         if (strcmp(cmd, c.name) == 0) {
//             return (this->*c.function)(value);  // Call the function
//         }
//     }
//     return "Command not found";
// }

// const char* get(const char* cmd) {
//     for (const Get& c : getCommands) {
//         if (strcmp(cmd, c.name) == 0) {
//             return (this->*c.function)();  // Call the function
//         }
//     }
//     return "Command not found";
// }

// Class Implementation
class JsonTalkie {
private:
    const Manifesto& manifesto;

public:
    explicit JsonTalkie(const Manifesto& manifesto) 
    : manifesto(manifesto) {}

};

#endif
