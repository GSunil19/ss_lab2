
/*
============================================================================
Name        : 33server.c
Author      : Gumpu Sunil
Description : Write a program to communicate between two machines using socket.
Date        : 30th Sep, 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(1);
    }

    // Prepare address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // listen on all interfaces
    address.sin_port = htons(PORT);

    // Bind
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(1);
    }

    // Listen
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(1);
    }
    printf("Server listening on port %d...\n", PORT);

    // Accept connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(1);
    }
    printf("Client connected.\n");

    // Read message from client
    read(new_socket, buffer, BUFFER_SIZE);
    printf("Received from client: %s\n", buffer);

    // Send response
    char *msg = "Hello from server";
    send(new_socket, msg, strlen(msg), 0);
    printf("Response sent to client.\n");

    close(new_socket);
    close(server_fd);

    return 0;
}
/*
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./33server
Server listening on port 8080...
Client connected.
Received from client: Hello from client
Response sent to client.

sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./33client
Connected to server.
Message sent to server.
Received from server: Hello from server


*/
