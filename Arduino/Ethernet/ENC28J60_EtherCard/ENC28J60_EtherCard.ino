#include <EtherCard.h>

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
#define BUFFER_SIZE 350
byte Ethernet::buffer[BUFFER_SIZE];

const uint16_t UDP_PORT = 5005;
const char* testMessage = "Hello from Nano!";

// ----- UDP Callback -----
bool udpCallback(uint8_t* data, uint16_t len, uint16_t srcPort, uint8_t* srcIp) {
  Serial.print("Received UDP packet from ");
  for (byte i = 0; i < 4; i++) {
    Serial.print(srcIp[i]);
    if (i < 3) Serial.print('.');
  }
  Serial.print(":");
  Serial.print(srcPort);
  Serial.print(" -> ");
  for (uint16_t i = 0; i < len; ++i) {
    Serial.write(data[i]);
  }
  Serial.println();
  return true;
}

// ----- Setup -----
void setup() {
  Serial.begin(9600);
  delay(1000);

  if (!ether.begin(BUFFER_SIZE, myMac, 10)) {
    Serial.println("Failed to access ENC28J60");
    while (1);
  }

  if (!ether.staticSetup(myIp, 0, 0, netmask)) {
    Serial.println("Failed to configure static IP");
    while (1);
  }

  ether.enableBroadcast();  // Enable broadcast reception
  ether.udpServerListenOnPort(&udpCallback, UDP_PORT);

  Serial.println("Setup complete. Sending broadcast every 5 seconds.");
}

// ----- Loop -----
void loop() {
  ether.packetLoop(ether.packetReceive());

  static unsigned long lastSend = 0;
  if (millis() - lastSend > 5000) {
    lastSend = millis();
    ether.sendUdp((char*)testMessage, strlen(testMessage), UDP_PORT, broadcastIP, UDP_PORT);
    Serial.println("UDP broadcast sent");
  }
}
