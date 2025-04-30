#include "Talker.h"

Talker talker;

void setup() {
    Serial.begin(9600);
    
    // Call commands directly
    Serial.println(talker.execute("buzz"));
    Serial.println(talker.execute("print"));
}

void loop() {}
