#include <EtherCard.h>


// Test it this way:
//     echo "TEST" | nc -u 192.168.31.255 5005


// Buzzer pin
#define buzzer_pin 3

// Command implementations
void buzz(size_t duration = 5) {
    digitalWrite(buzzer_pin, HIGH);
    delay(duration); 
    digitalWrite(buzzer_pin, LOW);
}


// Network configuration
static byte myMac[]         = { 0x74,0x69,0x69,0x2D,0x30,0x31 };
static byte myIp[]          = { 192,168,31,99 };
static byte netmask[]       = { 255,255,255,0 };
static byte broadcastIP[]   = { 192,168,31,255 }; // Use this instead of 255.255.255.255


// UDP usage: UDP packets are small; often ≤ 512 bytes, especially for local communication.
    // 🔧 Practical Minimum
    // For UDP send/receive only, with small messages (e.g., <100 bytes):
    // #define BUFFER_SIZE 350
    // This works reliably for:
        // Typical UDP payloads (<256 bytes)

        // Single-packet responses

        // Basic packetLoop() + UDP server setup
// Ethernet buffer
#define BUFFER_SIZE 500
byte Ethernet::buffer[BUFFER_SIZE];

const uint16_t UDP_PORT = 5005;
const char* testMessage = "Hello from Nano!";

// Corrected callback
static void udpCallback(uint16_t src_port, uint8_t* src_ip, uint16_t dst_port, const char* data, uint16_t len) {
    Serial.print("UDP from ");
    for (byte i = 0; i < 4; i++) {
        Serial.print(src_ip[i]);
        if (i < 3) Serial.print(".");
    }
    Serial.print(":");
    Serial.print(src_port);
    Serial.print(" -> ");
    Serial.write(data, len);
    Serial.println();
    buzz(100);
}

// // Helper function to read revision ID
// uint8_t readRevID() {
//     uint8_t revID = 0;
//     ether.enc28j60PhyWrite(PHLCON, 0x0000); // Dummy PHY write (triggers revision read)
//     revID = ether.enc28j60PhyRead(PHLCON) & 0xFF; // Lower byte contains revision
//     return revID;
// }

void setup() {
    Serial.begin(9600);
    while (!Serial);
    
    pinMode(buzzer_pin, OUTPUT);
    buzz();

    if (!ether.begin(BUFFER_SIZE, myMac, 10)) {
        Serial.println("Failed to access ENC28J60");
        while (1);
    }

    // // Read revision ID (alternative method)
    // uint8_t revID = readRevID();
    // Serial.print("ENC28J60 Rev: "); Serial.println(revID, HEX); // Should print 0x04, 0x06, etc.
        
    if (!ether.staticSetup(myIp, 0, 0, netmask)) {
        Serial.println("Failed to set static IP");
        while (1);
    }

    ether.enableBroadcast();
    ether.udpServerListenOnPort(udpCallback, UDP_PORT);
    
    Serial.println("Ready. Sending broadcasts...");
}

void loop() {
    ether.packetLoop(ether.packetReceive());

    static uint32_t lastSend = 0;
    if (millis() - lastSend >= 39000) {
        lastSend = millis();
        ether.sendUdp(testMessage, strlen(testMessage), UDP_PORT, broadcastIP, UDP_PORT);
        Serial.println("Broadcast sent");
        // buzz();
    }
}
