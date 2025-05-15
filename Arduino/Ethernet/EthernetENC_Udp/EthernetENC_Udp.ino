#include <EthernetENC.h>
#include <EthernetUdp.h>

// Network Settings
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 31, 100);       // Arduino IP
IPAddress subnet(255, 255, 255, 0);   // Network mask
IPAddress gateway(192, 168, 31, 77);    // Router IP (if needed)
const unsigned int UDP_PORT = 5005;

EthernetUDP udp;

void setup() {
    Serial.begin(9600);
    
    // Initialize Ethernet with static IP
    Ethernet.begin(mac, ip, gateway, subnet);
    
    // Start UDP
    if (udp.begin(UDP_PORT)) {
        Serial.print("UDP active on ");
        Serial.println(Ethernet.localIP());
    } else {
        Serial.println("UDP failed!");
    }
}

void loop() {
    // Check for incoming packets
    int packetSize = udp.parsePacket();
    if (packetSize) {
        char packet[64];
        udp.read(packet, sizeof(packet));
        Serial.print("From ");
        Serial.print(udp.remoteIP());
        Serial.print(": ");
        Serial.println(packet);
    }

    // Send to specific IP (replace with target IP)
    if (Serial.available()) {
        IPAddress target(192, 168, 31, 172);  // Direct target IP
        String message = Serial.readStringUntil('\n');
        
        udp.beginPacket(target, UDP_PORT);
        udp.write(message.c_str());
        udp.endPacket();
        
        Serial.print("Sent to ");
        Serial.print(target);
        Serial.print(": ");
        Serial.println(message);
    }
}
