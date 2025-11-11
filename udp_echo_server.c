#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>

#define PORT 9090
#define BUF_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server, client;
    char buffer[BUF_SIZE];
    socklen_t len = sizeof(client);

    // 1. Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // 2. Server address
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    // 3. Bind socket
    bind(sockfd, (struct sockaddr *)&server, sizeof(server));

    printf("UDP Echo Server listening on port %d...\n", PORT);

    // 4. Receive and send data
    while (1) {
        memset(buffer, 0, BUF_SIZE);
        recvfrom(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *)&client, &len);
        printf("Received: %s", buffer);
        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&client, len);
    }

    // 5. Close socket
    close(sockfd);
    return 0;
}

