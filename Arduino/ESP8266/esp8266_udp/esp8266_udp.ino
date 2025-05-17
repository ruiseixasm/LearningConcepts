#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "secrets/wifi_credentials.h"

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

const unsigned int PORT = 5005;         // UDP port
IPAddress remoteIP(192, 168, 31, 22);   // Target IP

WiFiUDP udp;
unsigned long lastSendTime = 0;
const unsigned long sendInterval = 5000;    // Send every 5 seconds

void setup() {
    Serial.begin(9600);
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.print("\nIP: ");
    Serial.println(WiFi.localIP());
    
    if (!udp.begin(PORT)) {
        Serial.println("Failed to start UDP");
        while(1);
    }
}

void loop() {
    // 1. Send UDP packet at intervals
    if (millis() - lastSendTime >= sendInterval) {
        sendUDPMessage();
        lastSendTime = millis();
    }
    // 2. Check for incoming packets
    checkUDPIncoming();
}

void sendUDPMessage() {
    udp.beginPacket(remoteIP, PORT);
    udp.write("Hello from ESP8266");
    udp.endPacket();
    
    Serial.print("Sent UDP to ");
    Serial.print(remoteIP);
    Serial.print(":");
    Serial.println(PORT);
}

void checkUDPIncoming() {
    int packetSize = udp.parsePacket();
    if (packetSize) {
        char incoming[128];
        int len = udp.read(incoming, sizeof(incoming));
        incoming[len] = 0; // Null-terminate
        
        Serial.print("Received ");
        Serial.print(len);
        Serial.print("B from ");
        Serial.print(udp.remoteIP());
        Serial.print(":");
        Serial.print(udp.remotePort());
        Serial.print(" - ");
        Serial.println(incoming);
    }
}
