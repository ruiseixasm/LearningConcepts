#include <ArduinoJson.h>

// Buzzer pin
#define buzzer_pin 3

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);  // End of processing
  pinMode(buzzer_pin, OUTPUT);
  digitalWrite(buzzer_pin, LOW);
}

void loop() {
    // 1. Wait for newline-terminated request (original format)
    if (Serial.available()) {

        String request = Serial.readStringUntil('\n');
        if (request.length() > 0) {  // Proper empty check
            
            digitalWrite(buzzer_pin, HIGH);
            delay(50);
            digitalWrite(buzzer_pin, LOW);

            // Visual feedback
            digitalWrite(LED_BUILTIN, HIGH);
            
            // Parse request
            StaticJsonDocument<200> req_doc;
            if (deserializeJson(req_doc, request) == DeserializationError::Ok) {
                float temp = req_doc["temp"];
                
                // Create response
                StaticJsonDocument<200> res_doc;
                res_doc["temp"] = temp;
                res_doc["timestamp"] = millis();
                
                // Send response
                serializeJson(res_doc, Serial);
                Serial.println();  // Terminator matching request format
                delay(5000);
            }
            digitalWrite(LED_BUILTIN, LOW);  // End of processing
        }
    }
}
