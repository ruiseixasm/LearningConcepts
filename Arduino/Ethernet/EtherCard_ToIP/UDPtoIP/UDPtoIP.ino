#include <EtherCard.h>

// Network settings
byte mymac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED}; // MAC address
byte myip[] = {192, 168, 1, 100};                     // Arduino IP
byte destip[] = {192, 168, 1, 22};                    // Destination IP
const uint16_t PORT = 1234;                            // UDP port

// Ethernet buffer
byte Ethernet::buffer[500];  // This is the crucial missing piece!

void setup() {
  Serial.begin(9600);
  
  // Initialize Ethernet (CS pin = 10 for Uno)
  if (!ether.begin(sizeof(Ethernet::buffer), mymac, 10)) {
    Serial.println("Failed to initialize ENC28J60!");
    while(1);
  }
  
  // Set static IP (disable DHCP)
  ether.staticSetup(myip);
  
  Serial.println("Ethernet initialized");
}

void loop() {
  // Your data to send
  const char* data = "Hello UDP!";
  
  // Send UDP packet (no error checking)
  ether.sendUdp(
    data,                    // Payload
    strlen(data),            // Length
    PORT,                    // Source port
    destip,                  // Destination IP
    PORT                     // Destination port
  );
  
  delay(2000); // Send every 2 seconds
}
