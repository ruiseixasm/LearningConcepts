// UDP chat program using  ENC28J60  tested on UNO and Nano
// **** change IP addresses and ports to suit requirements *****

#include <EthernetENC.h>  // for ENC28J60
#include <EthernetUdp.h>  // for UDP

// *****   IP of this machine and remote machine *********
IPAddress localIP(192, 168, 31, 177);
IPAddress remoteIP(192, 168, 31, 176);

// Enter a MAC address
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

unsigned int localPort = 10000;   // local port to listen on
unsigned int remotePort = 10000;  // remote port to transmit too

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial)
    ;
  Serial.println("\nEthernet UDP chat program");
  // Check for Ethernet hardware present

  // You can use Ethernet.init(pin) to configure the CS pin
  Ethernet.init(10);  // Most Arduino shields
                      //Ethernet.init(5);   // MKR ETH Shield
                      //Ethernet.init(0);   // Teensy 2.0
                      //Ethernet.init(20);  // Teensy++ 2.0
                      //Ethernet.init(15);  // ESP8266 with Adafruit FeatherWing Ethernet
                      //Ethernet.init(33);  // ESP32 with Adafruit FeatherWing Ethernet
  //displayMACaddress(mac);
  mac[5] = localIP[3];  // change default MAC address
  displayMACaddress(mac);
  // start the Ethernet
  Ethernet.begin(mac, localIP);
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) delay(1);  // do nothing, no point running without Ethernet hardware
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }
  Udp.begin(localPort);  // start UDP
  Serial.print("Ethernet UDP started ");
  displayIPaddress(localIP, localPort);
  //Serial.println(UDP_TX_PACKET_MAX_SIZE);
}

void loop() {
  Udp.begin(localPort);
  // if Serial text entered transmit as a datagram
  if (Serial.available()) {
    Udp.begin(localPort);
    char text[20] = { 0 };
    Serial.readBytesUntil('\n', text, 24);
    Serial.print("Transmitting to ");
    displayIPaddress(remoteIP, remotePort);
    Serial.println(text);
    Udp.beginPacket(remoteIP, remotePort);  // transmit datagram
    Udp.print(text);
    Udp.endPacket();
  }
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    displayIPaddress(Udp.remoteIP(), Udp.remotePort());
    // read the packet into packetBuffer
    char packetBuffer[100] = { 0 };      // buffer to hold incoming packet,
    Udp.read(packetBuffer, packetSize);  //UDP_TX_PACKET_MAX_SIZE);     // receive datagram
    Serial.print("Contents: ");
    Serial.println(packetBuffer);
    // if (strcmp(packetBuffer, "OK") != 0) {
    // send a reply to the IP address and port that sent us the packet we received
    //   Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    // Udp.write("OK");
    //  Udp.endPacket();
    //}
  }
  delay(10);
}

// print IPAdress and port
void displayIPaddress(const IPAddress address, unsigned int port) {
  Serial.print(" IP ");
  for (int i = 0; i < 4; i++) {
    Serial.print(address[i], DEC);
    if (i < 3) Serial.print(".");
  }
  Serial.print(" port ");
  Serial.println(port);
}

void displayMACaddress(byte address[]) {
  Serial.print("MAC address ");
  for (int i = 0; i < 6; i++) {
    Serial.print("0x");    
    Serial.print(address[i], HEX);
    if (i < 5) Serial.print(".");
  }
  Serial.println();
}
