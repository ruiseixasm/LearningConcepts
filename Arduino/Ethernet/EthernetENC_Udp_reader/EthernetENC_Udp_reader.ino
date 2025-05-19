#include <EthernetENC.h>
#include <EthernetUdp.h>

// Network Settings
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 31, 100);
IPAddress subnet(255, 255, 255, 0);
const unsigned int UDP_PORT = 5005;

EthernetUDP udp;

// Buffer for binary data
#define BUFFER_SIZE 512
uint8_t packetBuffer[BUFFER_SIZE];

void setup() {
  Serial.begin(9600);
  while (!Serial); // Wait for serial port
  
  // Initialize Ethernet - no SPI tweaking needed
  Ethernet.init(10); // CS pin (adjust if needed)
  
  Serial.println("Starting Ethernet...");
  Ethernet.begin(mac, ip, subnet);

  // Verify hardware
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("ENC28J60 not found!");
    while(1);
  }
  
  // Start UDP
  if (udp.begin(UDP_PORT)) {
    Serial.print("UDP listening on port ");
    Serial.println(UDP_PORT);
  } else {
    Serial.println("UDP failed!");
  }
}

void loop() {
  int packetSize = udp.parsePacket();
  if (packetSize > 0) {
    int bytesRead = udp.read(packetBuffer, min(packetSize, BUFFER_SIZE));
    
    Serial.print("Received ");
    Serial.print(bytesRead);
    Serial.print("/");
    Serial.print(packetSize);
    Serial.print(" bytes from ");
    Serial.print(udp.remoteIP());
    Serial.print(":");
    Serial.println(udp.remotePort());
    
    // Print as string if printable, hex otherwise
    bool isText = true;
    for (int i = 0; i < bytesRead; i++) {
      if (packetBuffer[i] < 32 || packetBuffer[i] > 126) {
        if (packetBuffer[i] != '\r' && packetBuffer[i] != '\n' && packetBuffer[i] != '\t') {
          isText = false;
          break;
        }
      }
    }
    
    if (isText) {
      Serial.print("Text: ");
      Serial.write(packetBuffer, bytesRead);
      Serial.println();
    } else {
      Serial.println("Binary data received");
      // Add hex dump here if needed
    }
  }
}
