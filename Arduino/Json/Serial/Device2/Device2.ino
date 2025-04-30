#include <ArduinoJson.h>

void setup() {
  Serial.begin(115200);
}

void loop() {
  // 1. Wait for newline-terminated request (original format)
  if (Serial.available()) {
    String request = Serial.readStringUntil('\n');
    
    // 2. Parse request (unchanged from your original)
    StaticJsonDocument<200> req_doc;
    deserializeJson(req_doc, request);
    float temp = req_doc["temp"];

    // 3. Create response (same newline-terminated format)
    StaticJsonDocument<200> res_doc;
    res_doc["temp"] = temp;
    res_doc["timestamp"] = millis();
    
    // 4. Send response (identical format to request)
    serializeJson(res_doc, Serial);
    Serial.println(); // Same newline terminator
  }
}
