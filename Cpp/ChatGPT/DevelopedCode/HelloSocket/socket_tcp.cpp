#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    // Create a TCP socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    // Server address information
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(80); // Port number
    serverAddr.sin_addr.s_addr = inet_addr("192.168.31.7"); // Server IP address

    // Connect to the server
    if (connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Error connecting to server" << std::endl;
        close(sockfd);
        return 1;
    }

    // Message to send
    const char* message = "Hello TCP Server!";

    // Send the message
    ssize_t bytesSent = send(sockfd, message, strlen(message), 0);
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
