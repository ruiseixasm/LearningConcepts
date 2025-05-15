#include <EthernetENC.h>
#include <Arduino.h>

// Enter a MAC address for your controller
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// Initialize EthernetENC library
EthernetServer server(8080);  // Port 8080

void setup() {
  Serial.begin(115200);
  
  // Start Ethernet connection
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    while (1); // Halt if connection fails
  }

  // Start the server
  server.begin();
  
  Serial.print("Server IP: ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  // Wait for a client to connect
  EthernetClient client = server.available();
  
  if (client) {
    Serial.println("New client connected!");
    
    // Read data from the client
    while (client.connected()) {
      if (client.available()) {
        String received = client.readStringUntil('\n');  // Read until newline
        Serial.print("Received: ");
        Serial.println(received);  // Print to Serial Monitor

        // Send a response back
        client.println("ECHO: " + received);  // Send back with "ECHO: " prefix
        break;
      }
    }
    
    // Close the connection
    client.stop();
    Serial.println("Client disconnected");
  }
}
