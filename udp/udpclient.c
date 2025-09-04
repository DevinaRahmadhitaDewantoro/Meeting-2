#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 9090

int main() {
    int sock_fd;
    struct sockaddr_in server_addr;
    char message[1024] = "Hello, Server!";
    char buffer[1024];
    socklen_t server_len = sizeof(server_addr);

    // Step 1: Create socket
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Step 2: Server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Step 3: Send message
    sendto(sock_fd, message, strlen(message), 0, (struct sockaddr *)&server_addr, server_len);

    // Step 4: Receive echo
    memset(buffer, 0, sizeof(buffer));
    recvfrom(sock_fd, buffer, sizeof(buffer), 0, (struct sockaddr *)&server_addr, &server_len);
    printf("Received from server: %s\n", buffer);

    close(sock_fd);
    return 0;
}
