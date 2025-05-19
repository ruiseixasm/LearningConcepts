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
    
    // This DO work despite being able to ping it!

    // Send "Hello" every 5 seconds
    if (millis() - lastSendTime >= INTERVAL) {
        if (random(2) % 2 == 0) {
            Serial.println("Direct hello");
            udp.beginPacket(target, UDP_PORT);
            udp.write("Direct hello");
        } else {
            Serial.println("Broadcasted hello");
            udp.beginPacket(broadcast, UDP_PORT);
            udp.write("Broadcasted hello");
        }
        udp.endPacket();
        lastSendTime = millis();
    }

    // // WORK
    // echo "BROADCAST 255" | nc -ubv 255.255.255.255 5005
    // echo "UNICAST" | nc -ubv 192.168.31.100 5005
    // // DOESN'T WORK
    // echo "BROADCAST 192" | nc -ubv 192.168.31.255 5005
    
    // Check for incoming packets (ASCII text packages)
    int packetSize = udp.parsePacket();
    if (packetSize > 0) {
        char packet[512];
        int len = udp.read(packet, sizeof(packet));
        packet[len] = '\0';
        Serial.print("From ");
        Serial.print(udp.remoteIP());
        Serial.print(": ");
        Serial.println(packet);
    }

    // # Send binary packet (0x00 to 0xFF)
    // echo -ne '\x00\x01\x02\x03\xFF' | nc -ubv 255.255.255.255 5005
    // # Send mixed binary/text
    // echo -ne 'TEXT\x00\x01BINARY\xFF' | nc -ubv 192.168.31.100 5005
    
    // Check for incoming packets (Binary packages)
    packetSize = udp.parsePacket();
    if (packetSize > 0) {
        // Buffer for raw binary data
        uint8_t packetBuffer[512];
        
        // Read raw bytes (no string conversion)
        int len = udp.read(packetBuffer, min(packetSize, (int)sizeof(packetBuffer)));
        
        Serial.print("Received ");
        Serial.print(len);
        Serial.print(" bytes from ");
        Serial.print(udp.remoteIP());
        Serial.print(":");
        Serial.println(udp.remotePort());
        
        // Hex dump of received data
        Serial.println("Packet content (hex):");
        for (int i = 0; i < len; i++) {
        if (packetBuffer[i] < 0x10) Serial.print('0');
        Serial.print(packetBuffer[i], HEX);
        Serial.print(' ');
        if ((i+1) % 16 == 0) Serial.println();
        }
        Serial.println("\n---");
    }
}
