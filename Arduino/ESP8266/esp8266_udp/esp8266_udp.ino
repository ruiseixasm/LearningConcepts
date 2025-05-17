#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "secrets/wifi_credentials.h"

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

// Configuration
#define USE_DHCP

const unsigned int PORT = 5005;             // UDP port
IPAddress remoteIP(192, 168, 31, 22);       // Target IP
IPAddress broadcastIP(255, 255, 255, 255);  // Broadcast IP

WiFiUDP udp;
unsigned long lastSendTime = 0;
const unsigned long sendInterval = 5000;    // Send every 5 seconds

void setup() {
    Serial.begin(9600);
    WiFi.begin(ssid, password);

    // Configure IP based on macro
    #ifdef USE_DHCP
        IPAddress staticIP(192, 168, 31, 100);
        IPAddress gateway(192, 168, 31, 77);
        IPAddress subnet(255, 255, 255, 0);
        WiFi.config(staticIP, gateway, subnet);
    #endif

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.print("\n\nIP: ");
    Serial.println(WiFi.localIP());
    
    if (!udp.begin(PORT)) {
        Serial.println("Failed to start UDP");
        while(1);
    }
}

void loop() {
    // 1. Send UDP packet at intervals
    if (millis() - lastSendTime >= sendInterval) {
        if (random(2) % 2 == 0) {
            Serial.println("Direct hello");
            udp.beginPacket(remoteIP, PORT);
            udp.write("Direct hello");
        } else {
            Serial.println("Broadcasted hello");
            udp.beginPacket(broadcastIP, PORT);
            udp.write("Broadcasted hello");
        }
        udp.endPacket();
        lastSendTime = millis();
    }
    // 2. Check for incoming packets
    int packetSize = udp.parsePacket();
    if (packetSize > 0) {
        char incoming[128];
        int len = udp.read(incoming, sizeof(incoming));
        incoming[len] = '\0';   // Null-terminate
        Serial.print("From ");
        Serial.print(udp.remoteIP());
        Serial.print(": ");
        Serial.println(incoming);
    }
}
