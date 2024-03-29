#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

int main() {
    int sockfd, newsockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[1024];

    // Create TCP socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
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

    // To resolve this issue, you can either wait for some time before running the receiver
    //     again to allow the operating system to release the port, or you can set the
    //     SO_REUSEADDR option on the socket to allow reusing the same address and port
    //     immediately after the socket is closed.

    // int reuse = 1;
    // if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
    //     std::cerr << "Failed to set SO_REUSEADDR option\n";
    //     close(sockfd);
    //     return 1;
    // }


    // Listen for incoming connections
    if (listen(sockfd, 5) < 0) {
        std::cerr << "Failed to listen for connections\n";
        close(sockfd);
        return 1;
    }

    std::cout << "Waiting for incoming connections...\n";

    // Accept incoming connection
    if ((newsockfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_len)) < 0) {
        std::cerr << "Failed to accept connection\n";
        close(sockfd);
        return 1;
    }

    // Receive message from client
    int recv_len;
    if ((recv_len = recv(newsockfd, buffer, sizeof(buffer), 0)) < 0) {
        std::cerr << "Failed to receive message\n";
        close(newsockfd);
        close(sockfd);
        return 1;
    }

    // Null-terminate received message
    buffer[recv_len] = '\0';

    std::cout << "Received message from client: " << buffer << std::endl;

    close(newsockfd);
    close(sockfd);
    return 0;
}
