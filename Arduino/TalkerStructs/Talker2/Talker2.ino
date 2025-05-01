#include "Talker.h"

Talker talker;

void setup() {
    Serial.begin(9600);
    
    // Call commands directly
    Serial.println(talker.run("buzz"));
    Serial.println(talker.get("duration"));
    Serial.println(talker.set("duration", "0.3"));
    Serial.println(talker.get("duration"));
}

void loop() {}
