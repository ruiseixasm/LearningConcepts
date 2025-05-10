#include <EtherCard.h>

// Network setup
static byte myMac[] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 };
static byte myIP[]  = { 192, 168, 31, 100 };
static byte myGW[]  = { 192, 168, 31, 77 };
static byte myMask[] = { 255, 255, 255, 0 };

const int listenPort = 5005;

// Storage for learned MAC
byte learnedMAC[6];
byte learnedIP[4];
bool hasLearnedMAC = false;

void udpCallback(uint16_t dest_port, uint8_t src_ip[4], uint16_t src_port, const char* data, uint16_t len) {
  Serial.println("Received UDP packet!");

  // Print sender IP
  Serial.print("From IP: ");
  for (byte i = 0; i < 4; i++) {
    Serial.print(src_ip[i], DEC);
    if (i < 3) Serial.print(".");
  }
  Serial.println();

  // Learn and store the MAC address
  for (byte i = 0; i < 4; i++) learnedIP[i] = src_ip[i];
  for (byte i = 0; i < 6; i++) learnedMAC[i] = ether.packetData[6 + i];  // MAC from Ethernet frame
  hasLearnedMAC = true;

  Serial.print("Learned MAC: ");
  for (byte i = 0; i < 6; i++) {
    Serial.print(learnedMAC[i], HEX);
    if (i < 5) Serial.print(":");
  }
  Serial.println();
}

void setup() {
  Serial.begin(9600);
  if (ether.begin(sizeof Ethernet::buffer, myMac) == 0) {
    Serial.println("Failed to access Ethernet controller");
    while (true);
  }

  ether.staticSetup(myIP, myGW, myGW, myMask);
  ether.udpServerListenOnPort(&udpCallback, listenPort);
  Serial.println("Listening for UDP packets...");
}

void loop() {
  ether.packetLoop(ether.packetReceive());

  // Example: use learned MAC after it has been received
  if (hasLearnedMAC) {
    // Example: send a UDP reply
    const char msg[] = "Hello back!";
    ether.copyIp(ether.hisip, learnedIP);
    for (byte i = 0; i < 6; i++) ether.hisMAC[i] = learnedMAC[i];

    ether.udpPrepare(5005);  // source port
    ether.udpTransmit((uint8_t*)msg, sizeof(msg));
    hasLearnedMAC = false;  // only reply once for demo
  }
}
