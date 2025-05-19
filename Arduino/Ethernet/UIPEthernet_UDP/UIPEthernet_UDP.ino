#include <UIPEthernet.h>  // Reliable ENC28J60 library
#include <utility/logging.h>  // For optional debug control

// Network Settings
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 31, 100);
IPAddress subnet(255, 255, 255, 0);
const unsigned int UDP_PORT = 5005;

EthernetUDP udp;

void setup() {
    Serial.begin(9600);  // Faster baud rate for debugging
    while(!Serial); // Wait for serial port
    
    // Optional debug control (uncomment if needed)
    // Log.begin(LOG_LEVEL_WARN, &Serial);
    
    // Initialize Ethernet with static IP
    Serial.println(F("Initializing Ethernet..."));
    Ethernet.begin(mac, ip, subnet);
    
    // Verify hardware
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
        Serial.println(F("ENC28J60 not found! Check:"));
        Serial.println(F("1. CS pin connection (usually pin 10)"));
        Serial.println(F("2. SPI wiring (MOSI,MISO,SCK)"));
        Serial.println(F("3. Power supply (3.3V stable)"));
        while(1);
    }
    
    // Check link status
    if (Ethernet.linkStatus() == LinkOFF) {
        Serial.println(F("Ethernet cable not connected!"));
    } else {
        Serial.println(F("Network link detected"));
    }
    
    // Start UDP
    if (udp.begin(UDP_PORT)) {
        Serial.print(F("UDP listening on "));
        Serial.print(Ethernet.localIP());
        Serial.print(F(":"));
        Serial.println(UDP_PORT);
    } else {
        Serial.println(F("UDP initialization failed!"));
    }

    Serial.println(F("\nNetwork Configuration:"));
    Serial.print(F("IP: ")); Serial.println(Ethernet.localIP());
    Serial.print(F("Subnet: ")); Serial.println(Ethernet.subnetMask());
    Serial.print(F("Gateway: ")); Serial.println(Ethernet.gatewayIP());
    Serial.println(F("Ready to receive data..."));
}

void loop() {
    // Process incoming packets first
    int packetSize = udp.parsePacket();
    if (packetSize > 0) {
        // Allocate buffer dynamically based on packet size
        char* packetBuffer = new char[packetSize + 1]; // +1 for null term
        
        // Read packet content
        int bytesRead = udp.read(packetBuffer, packetSize);
        packetBuffer[bytesRead] = '\0'; // Null-terminate
        
        // Print reception info
        Serial.print(F("\n["));
        Serial.print(millis());
        Serial.print(F("] Received "));
        Serial.print(bytesRead);
        Serial.print(F("/"));
        Serial.print(packetSize);
        Serial.print(F(" bytes from "));
        Serial.print(udp.remoteIP());
        Serial.print(F(":"));
        Serial.print(udp.remotePort());
        
        // Print content (handles both text and binary)
        if (isPrintable(packetBuffer, bytesRead)) {
            Serial.print(F("\nContent: "));
            Serial.println(packetBuffer);
        } else {
            Serial.println(F("\nBinary data:"));
            hexDump(packetBuffer, bytesRead);
        }
        
        // Free memory
        delete[] packetBuffer;
    }
}

bool isPrintable(const char* data, int len) {
    for (int i = 0; i < len; i++) {
        byte c = data[i];
        if (c < 32 || c > 126) {
            if (c != '\n' && c != '\r' && c != '\t') {
                return false;
            }
        }
    }
    return true;
}

void hexDump(const char* data, int len) {
    for (int i = 0; i < len; i++) {
        // Print hex value
        if (data[i] < 0x10) Serial.print('0');
        Serial.print(data[i], HEX);
        Serial.print(' ');
        
        // Print ASCII representation
        if ((i+1) % 16 == 0 || i == len-1) {
            // Pad for alignment
            for (int j = 0; j < 15 - (i % 16); j++) {
                Serial.print("   ");
            }
            Serial.print("| ");
            
            // Print ASCII characters
            for (int j = i - (i % 16); j <= i; j++) {
                byte c = data[j];
                if (c >= 32 && c <= 126) {
                    Serial.write(c);
                } else {
                    Serial.print('.');
                }
            }
            Serial.println();
        }
    }
    Serial.println();
}
