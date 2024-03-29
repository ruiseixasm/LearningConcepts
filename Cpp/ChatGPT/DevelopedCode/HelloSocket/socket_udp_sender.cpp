#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sockfd;
    struct sockaddr_in server_addr;

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        std::cerr << "Failed to create socket\n";
        return 1;
    }

    // Server address parameters
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);  // Destination port
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Destination IP address

    // Message to send
    const char* message = "Hello UDP Server!";
    int message_len = strlen(message);

    // Send message to server
    if (sendto(sockfd, message, message_len, 0, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Failed to send message\n";
        close(sockfd);
        return 1;
    }

    std::cout << "Message sent successfully\n";

    close(sockfd);
    return 0;
}
