#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> // Include this for close function

int main() {
    // Create a UDP socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    // Server address information
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345); // Port number
    serverAddr.sin_addr.s_addr = inet_addr("192.168.31.7"); // Server IP address

    // Message to send
    const char* message = "Hello UDP Server!";

    // Send the message
    ssize_t bytesSent = sendto(sockfd, message, strlen(message), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (bytesSent < 0) {
        std::cerr << "Error sending message" << std::endl;
        close(sockfd);
        return 1;
    }

    std::cout << "Message sent successfully" << std::endl;

    // Close the socket
    close(sockfd);

    return 0;
}
