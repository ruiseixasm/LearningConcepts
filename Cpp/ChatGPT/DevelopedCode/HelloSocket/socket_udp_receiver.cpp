#include <iostream>
#include <arpa/inet.h>
#include <cstring> // Include for memset
#include <unistd.h>

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[1024];

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        std::cerr << "Failed to create socket\n";
        return 1;
    }

    // Server address parameters
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);  // Listening port
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);  // Accept connections from any IP address

    // Bind socket to address
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Failed to bind socket\n";
        close(sockfd);
        return 1;
    }

    // Receive message from client
    int recv_len;
    if ((recv_len = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&client_addr, &client_len)) < 0) {
        std::cerr << "Failed to receive message\n";
        close(sockfd);
        return 1;
    }

    // Null-terminate received message
    buffer[recv_len] = '\0';

    std::cout << "Received message from " << inet_ntoa(client_addr.sin_addr) << ": " << buffer << std::endl;

    close(sockfd);
    return 0;
}
