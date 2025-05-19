#include <UIPEthernet.h>
#include <UIPUdp.h>  // If using UDP

#define UDP_TX_PACKET_MAX_SIZE 512

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 31, 100);
IPAddress subnet(255, 255, 255, 0);
IPAddress target(192, 168, 31, 22);
unsigned int UDP_PORT = 5005;

EthernetUDP Udp;

void setup() {
    Serial.begin(9600);
    Ethernet.begin(mac, ip, subnet);
    Udp.begin(UDP_PORT);
    Serial.println("UDP Listener Ready");
}

void loop() {
    int packetSize = Udp.parsePacket();
    if (packetSize > 0) {
        char packet[UDP_TX_PACKET_MAX_SIZE];
        int len = Udp.read(packet, min(packetSize, UDP_TX_PACKET_MAX_SIZE - 1));
        packet[len] = '\0';
        Serial.print("Received: ");
        Serial.println(packet);
    }

    static unsigned long lastSend = 0;
    if (millis() - lastSend > 20000) {
        lastSend = millis();
        if (random(2) % 2 == 0) {
            Udp.beginPacket(IPAddress(255,255,255,255), UDP_PORT);
            Udp.write("Broadcasted Hello!");
            Udp.endPacket();
            Serial.println("Broadcast Sent");
        } else {
            Udp.beginPacket(target, UDP_PORT);
            Udp.write("Unicasted Hello!");
            Udp.endPacket();
            Serial.println("Unicast Sent");
        }
        // Udp.flush(); // Clear any remaining data
        // Udp.begin(UDP_PORT); // Refresh socket
    }
}
