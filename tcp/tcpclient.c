#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 9090

int main() {
    int client_fd;
    struct sockaddr_in server_addr;
    char message[1024] = "Hello, Server!";
    char buffer[1024];

    // Step 1: Create socket
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Step 2: Server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Step 3: Connect
    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        return 1;
    }

    // Step 4: Send message
    write(client_fd, message, strlen(message));

    // Step 5: Receive echo
    memset(buffer, 0, sizeof(buffer));
    read(client_fd, buffer, sizeof(buffer));
    printf("Received from server: %s\n", buffer);

    close(client_fd);
    return 0;
}
