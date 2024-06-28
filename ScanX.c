#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>

// Function to check if a port is open
int check_port(char *hostname, int port) {
    int sockfd;
    struct sockaddr_in target;
    struct hostent *host;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return 0;
    }

    // Resolve hostname
    host = gethostbyname(hostname);
    if (host == NULL) {
        fprintf(stderr, "Error: Unknown host %s\n", hostname);
        return 0;
    }

    // Set up target address
    memset(&target, 0, sizeof(target));
    target.sin_family = AF_INET;
    target.sin_port = htons(port);
    memcpy(&target.sin_addr.s_addr, host->h_addr, host->h_length);

    // Attempt to connect
    if (connect(sockfd, (struct sockaddr *)&target, sizeof(target)) < 0) {
        close(sockfd);
        return 0;
    }

    // Connection successful
    close(sockfd);
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <hostname> <start_port> <end_port>\n", argv[0]);
        exit(1);
    }

    char *hostname = argv[1];
    int start_port = atoi(argv[2]);
    int end_port = atoi(argv[3]);

    printf("Scanning %s from port %d to %d...\n", hostname, start_port, end_port);

    for (int port = start_port; port <= end_port; port++) {
        if (check_port(hostname, port)) {
            printf("Port %d is open\n", port);
        }
    }

    return 0;
}
