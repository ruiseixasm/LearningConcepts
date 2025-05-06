#include <UIPEthernet.h>
#include <EthernetUdp.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 31, 99);
EthernetUDP Udp;
unsigned int localPort = 5005;

void setup() {
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  Udp.begin(localPort);
  Serial.println("UDP Listener Ready");
}

void loop() {
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    char packet[UDP_TX_PACKET_MAX_SIZE];
    Udp.read(packet, UDP_TX_PACKET_MAX_SIZE);
    Serial.print("Received: ");
    Serial.println(packet);
  }

  static unsigned long lastSend = 0;
  if (millis() - lastSend > 5000) {
    lastSend = millis();
    Udp.beginPacket(IPAddress(192,168,31,255), 5005);
    Udp.write("Hello from Nano!");
    Udp.endPacket();
    Serial.println("Broadcast Sent");
  }
}
