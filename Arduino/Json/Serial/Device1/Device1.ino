#include <ArduinoJson.h>

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    // Works EXACTLY like Python's readline()
    String json_str = Serial.readStringUntil('\n');
    
    StaticJsonDocument<200> doc;
    deserializeJson(doc, json_str);

    float temp = doc["temp"];
    Serial.print("Received: "); Serial.println(temp);
  }
}
