#include <EthernetENC.h>
#include <EthernetUdp.h>

// // Linux testing commands:
// echo "BROADCAST 255" | nc -ubv 255.255.255.255 5005
// echo "BROADCAST 192" | nc -ubv 192.168.31.255 5005
// echo "UNICAST" | nc -ubv 192.168.31.100 5005


// Network Settings
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 31, 100);       // Arduino IP
IPAddress subnet(255, 255, 255, 0);   // Network mask
IPAddress gateway(192, 168, 31, 77);    // Router IP (if needed)
const unsigned int UDP_PORT = 5005;
IPAddress target(192, 168, 31, 22);                // Target PC IP
IPAddress broadcast(255, 255, 255, 255); // Broadcast address

EthernetUDP udp;
unsigned long lastSendTime = 0;
const unsigned long INTERVAL = 5000; // 5 seconds

void setup() {
    Serial.begin(9600);
    
    // Initialize Ethernet with static IP
    Ethernet.begin(mac, ip, gateway, subnet);

    // Start UDP
    if (udp.begin(UDP_PORT)) {
        Serial.print("\n\nUDP active on ");
        Serial.println(Ethernet.localIP());
    } else {
        Serial.println("UDP failed!");
    }
}

void loop() {
    // Send "Hello" every 5 seconds
    if (millis() - lastSendTime >= INTERVAL) {
        if (random(2) % 2 == 0) {
            udp.beginPacket(target, UDP_PORT);
            Serial.println("Direct hello");
            udp.write("Direct hello");
        } else {
            udp.beginPacket(broadcast, UDP_PORT);
            Serial.println("Broadcasted hello");
            udp.write("Broadcasted hello");
        }
        udp.endPacket();
        lastSendTime = millis();
    }

    // This doesn't work: echo "BROADCAST 192" | nc -ubv 192.168.31.255 5005
    
    // Check for incoming packets
    int packetSize = udp.parsePacket();
    if (packetSize > 0) {
        char packet[128];
        udp.read(packet, sizeof(packet));
        Serial.print("From ");
        Serial.print(udp.remoteIP());
        Serial.print(": ");
        Serial.println(packet);
    }
}
