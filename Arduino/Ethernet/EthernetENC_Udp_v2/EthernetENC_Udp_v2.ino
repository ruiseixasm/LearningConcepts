#include <EthernetENC.h>
#include <EthernetUdp.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 31, 100);
const unsigned int UDP_PORT = 5005;

EthernetUDP udp;

void setup() {
  Serial.begin(9600);
  
  // Start Ethernet with ENC28J60
  Ethernet.begin(mac, ip);
  
  // Start UDP - no special settings needed for EthernetENC
  udp.begin(UDP_PORT);
  
  Serial.print("Listening on ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  // Send test message every 5 seconds
  static unsigned long lastSend = 0;
  if (millis() - lastSend >= 5000) {
    udp.beginPacket("255.255.255.255", UDP_PORT); // Broadcast
    udp.write("Test");
    udp.endPacket();
    lastSend = millis();
    Serial.println("Sent broadcast");
  }

  // Check for incoming packets
  int len = udp.parsePacket();
  if (len > 0) {
    char buf[128];
    udp.read(buf, sizeof(buf));
    Serial.print("Received from ");
    Serial.print(udp.remoteIP());
    Serial.print(": ");
    Serial.println(buf);
  }
}
