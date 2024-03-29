#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char message[] = "Hello, TCP Server!";

    // Create TCP socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Failed to create socket\n";
        return 1;
    }

    // Server address parameters
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);  // Server port
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Server IP address

    // Connect to server
    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Connection failed\n";
        close(sockfd);
        return 1;
    }

    // Send message to server
    if (send(sockfd, message, strlen(message), 0) < 0) {
        std::cerr << "Failed to send message\n";
        close(sockfd);
        return 1;
    }

    std::cout << "Message sent to server: " << message << std::endl;

    close(sockfd);
    return 0;
}
