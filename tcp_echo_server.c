#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>

#define PORT 10055 // Example: if PRN is 55, then 10000 + 55 = 10055
#define BUF_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    char buffer[BUF_SIZE];
    int addrlen = sizeof(address);

    // 1. Create TCP socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // 2. Prepare server address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // 3. Bind the socket to the port
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    // 4. Listen for incoming connections
    listen(server_fd, 3);
    printf("TCP Echo Server listening on port %d...\n", PORT);

    // 5. Accept a client connection
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

    // 6. Receive and echo back messages
    while (1) {
        memset(buffer, 0, BUF_SIZE);
        int bytes = read(new_socket, buffer, BUF_SIZE);
        if (bytes <= 0) break; // exit if client disconnects
        printf("Received: %s", buffer);
        send(new_socket, buffer, bytes, 0);  // Echo back to client
    }

    // 7. Close sockets
    close(new_socket);
    close(server_fd);
    return 0;
}

