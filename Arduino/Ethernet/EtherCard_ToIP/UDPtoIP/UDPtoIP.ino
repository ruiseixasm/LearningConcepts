#include <EtherCard.h>

// Network settings
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};      // MAC address
byte my_ip[] = {192, 168, 31, 100};                     // Arduino IP
byte gw_ip[] = {192, 168, 31, 77};                      // IP of the main router, gateway
byte dns_ip[] = {192, 168, 31, 77};                     // DNS address is the same as the gateway router
byte mask[] = {255, 255, 255, 0};                       // NEEDED FOR NETWORK BROADCAST
const uint16_t PORT = 5005;                             // UDP port

// Ethernet buffer
byte Ethernet::buffer[500];  // This is the crucial missing piece!

void setup() {
    Serial.begin(9600);
    Serial.println("\n");

    // Initialize Ethernet (CS pin = 10 for Uno)
    if (!ether.begin(sizeof(Ethernet::buffer), mac, 10)) {
        Serial.println("Failed to initialize ENC28J60!");
        while(1);
    }
    
    // // Set static IP (disable DHCP)
    // ether.staticSetup(my_ip, gw_ip, dns_ip, mask);
        
    // DHCP Configuration
    Serial.println("Requesting DHCP lease...");
    if (!ether.dhcpSetup()) {
        Serial.println("DHCP failed!");
        while(1);
    }

    // Print network configuration
    Serial.println("DHCP assigned configuration:");
    Serial.print("IP: "); ether.printIp(ether.myip); Serial.println();
    Serial.print("GW: "); ether.printIp(ether.gwip); Serial.println();
    Serial.print("DNS: "); ether.printIp(ether.dnsip); Serial.println();
    Serial.print("NETMASK: "); ether.printIp(ether.netmask); Serial.println();

    // Makes sure it allows broadcast
    ether.enableBroadcast();
    
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
    
    // 2. IT WORKS :)

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
