#include <EthernetENC.h>
#include <EthernetUdp.h>

// Network Settings
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 31, 100);       // Arduino IP
IPAddress subnet(255, 255, 255, 0);    // Network mask
IPAddress gateway(192, 168, 31, 77);   // Router IP
const unsigned int UDP_PORT = 5005;
IPAddress target(192, 168, 31, 22);    // Target PC IP
IPAddress subnetBroadcast(192, 168, 31, 255); // Subnet broadcast

EthernetUDP udp;
unsigned long lastSendTime = 0;
const unsigned long INTERVAL = 5000; // 5 seconds

void setup() {
    Serial.begin(9600);
    while (!Serial); // Wait for serial port to connect
    
    // Initialize Ethernet with static IP
    Ethernet.init(5); // SS pin for ENC28J60 (adjust if needed)
    
    Serial.println("Starting Ethernet...");
    Ethernet.begin(mac, ip, gateway, subnet);

    // Verify Ethernet hardware
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
        Serial.println("Ethernet shield not found!");
        while (true);
    }
    if (Ethernet.linkStatus() == LinkOFF) {
        Serial.println("Ethernet cable is not connected.");
    }

    // Start UDP
    if (udp.begin(UDP_PORT)) {
        Serial.print("\nUDP active on ");
        Serial.print(Ethernet.localIP());
        Serial.print(" port ");
        Serial.println(UDP_PORT);
    } else {
        Serial.println("UDP failed to start!");
    }

    // Print network info
    Serial.print("Subnet: ");
    Serial.println(Ethernet.subnetMask());
    Serial.print("Gateway: ");
    Serial.println(Ethernet.gatewayIP());
    Serial.print("Subnet broadcast: ");
    Serial.println(subnetBroadcast);
    Serial.println("Ready for communication...");
}

void loop() {
    // Handle incoming packets FIRST (priority)
    int packetSize = udp.parsePacket();
    if (packetSize > 0) {
        char packet[128];
        int len = udp.read(packet, sizeof(packet) - 1); // Leave room for null terminator
        if (len > 0) {
            packet[len] = '\0'; // Null terminate
            Serial.print("Received ");
            Serial.print(len);
            Serial.print(" bytes from ");
            Serial.print(udp.remoteIP());
            Serial.print(":");
            Serial.print(udp.remotePort());
            Serial.print(" -> ");
            Serial.println(packet);
        }
    }

    // Send messages periodically
    if (millis() - lastSendTime >= INTERVAL) {
        if (random(2) % 2 == 0) {
            Serial.println("Sending direct message");
            if (udp.beginPacket(target, UDP_PORT)) {
                udp.write("Direct hello");
                if (!udp.endPacket()) {
                    Serial.println("Direct send failed!");
                }
            } else {
                Serial.println("Failed to begin direct packet!");
            }
        } else {
            Serial.println("Sending broadcast message");
            if (udp.beginPacket(subnetBroadcast, UDP_PORT)) {
                udp.write("Broadcasted hello");
                if (!udp.endPacket()) {
                    Serial.println("Broadcast send failed!");
                }
            } else {
                Serial.println("Failed to begin broadcast packet!");
            }
        }
        lastSendTime = millis();
    }

    // Small delay to prevent flooding the serial monitor
    delay(10);
}
