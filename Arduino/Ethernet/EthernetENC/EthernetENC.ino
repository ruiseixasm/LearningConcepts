#include <EthernetENC.h>
#include <EthernetUdp.h>

// MAC address for ENC28J60 module (must be unique on the network)
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// Local IP for the Arduino
IPAddress localIP(192, 168, 31, 100);

// Destination IP and port
IPAddress destIP(192, 168, 31, 22);  // <-- Replace with your PC's IP
unsigned int destPort = 5005;       // <-- Replace with target UDP port

EthernetUDP Udp;

void setup() {
  Serial.begin(9600);

  // Start Ethernet with static IP
  Ethernet.begin(mac, localIP);
  delay(1000);  // Give time to initialize

  Serial.println("Ethernet initialized");
  
  Udp.begin(5005); // Local UDP port (can be arbitrary)
  
  sendUDP();
}

void loop() {
  delay(2000);
  sendUDP();
}

void sendUDP() {
  const char msg[] = "Hello, UDP!";
  Udp.beginPacket(destIP, destPort);
  Udp.write((const uint8_t*)msg, sizeof(msg));
  Udp.endPacket();

  Serial.println("UDP packet sent");
}
