#include <WiFi.h>
#include <WiFiUdp.h>
#include "secrets/wifi_credentials.h"

// To upload a sketch to an ESP32 when the "......." appear, press the button BOOT


const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

// Configuration
// #define USE_DHCP  // Comment out to use static IP

const unsigned int PORT = 5005;
IPAddress remoteIP(192, 168, 31, 22);       // Target device IP
IPAddress broadcastIP(192, 168, 31, 255);   // Correct broadcast for subnet

WiFiUDP udp;
unsigned long lastSendTime = 0;
const unsigned long sendInterval = 5000;

void setup() {
    Serial.begin(9600);
    WiFi.begin(ssid, password);

    // Configure IP (static only when USE_DHCP is undefined)
    #ifndef USE_DHCP
    IPAddress staticIP(192, 168, 31, 100);
    IPAddress gateway(192, 168, 31, 77);
    IPAddress subnet(255, 255, 255, 0);
    WiFi.config(staticIP, gateway, subnet);
    #endif

    Serial.print("\n\nConnecting");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.print("\nIP: ");
    Serial.println(WiFi.localIP());
    Serial.print("Broadcast: ");
    Serial.println(WiFi.localIP() | ~WiFi.subnetMask());

    udp.begin(PORT);
}

void loop() {
    // Send UDP packets
    if (millis() - lastSendTime >= sendInterval) {
        if (random(2) % 2 == 0) {
            Serial.println("Direct hello");
            udp.beginPacket(remoteIP, PORT);
            udp.print("Direct hello");  // Changed from write() to print()
        } else {
            Serial.println("Broadcasted hello");
            udp.beginPacket(broadcastIP, PORT);
            udp.print("Broadcast hello");  // Changed from write() to print()
        }
        udp.endPacket();
        lastSendTime = millis();
    }

    // Receive packets
    int packetSize = udp.parsePacket();
    if (packetSize > 0) {
        char incoming[128];
        int len = udp.read(incoming, sizeof(incoming) - 1);
        incoming[len] = '\0';
        
        Serial.print(packetSize);
        Serial.print("B from ");
        Serial.print(udp.remoteIP());
        Serial.print(":");
        Serial.print(udp.remotePort());
        Serial.print(" -> ");
        Serial.println(incoming);
    }
}
