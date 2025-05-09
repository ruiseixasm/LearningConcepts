#include <EtherCard.h>

// Network settings
byte mymac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};    // MAC address
byte myip[] = {192, 168, 31, 100};                      // Arduino IP
const uint16_t PORT = 5005;                             // UDP port

// Ethernet buffer
byte Ethernet::buffer[500];  // This is the crucial missing piece!

void setup() {
    Serial.begin(9600);
    Serial.println("\n");

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
    
    // 1. DOESN'T WORK :(

    const char* data_single = "1. Single Address!";
    const byte single_ip[]  = {192, 168, 31, 22};       // Single destination IP
    delay(2000); // Send every 2 seconds
    Serial.println(data_single);
    ether.sendUdp(
        data_single,            // Payload
        strlen(data_single),    // Length
        PORT,                   // Source port
        single_ip,              // Destination IP
        PORT                    // Destination port
    );
    
    // 2. DOESN'T WORK :(

    const char* data_network = "2. Network Address!";
    const byte network_ip[] = {192, 168, 31, 255};      // Network destination IP (broadcast)
    delay(2000); // Send every 2 seconds
    Serial.println(data_network);
    ether.sendUdp(
        data_network,           // Payload
        strlen(data_network),   // Length
        PORT,                   // Source port
        network_ip,             // Destination IP
        PORT                    // Destination port
    );
    
    // 3. IT WORKS :)

    const char* data_global = "3. Global Address!";
    const byte global_ip[]  = {255, 255, 255, 255};     // Global destination IP (broadcast)
    delay(2000); // Send every 2 seconds
    Serial.println(data_global);
    ether.sendUdp(
        data_global,            // Payload
        strlen(data_global),    // Length
        PORT,                   // Source port
        global_ip,              // Destination IP
        PORT                    // Destination port
    );
}
