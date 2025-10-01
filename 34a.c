/*
============================================================================
Name        : 34a.c
Author      : Gumpu Sunil
Description : Write a program to create a concurrent server.
a. use fork
b. use pthread_create
Date        : 24th Sep, 2025
============================================================================
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 6000
#define BUFFER_SIZE 1024

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) { perror("socket"); exit(1); }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) { perror("bind"); exit(1); }
    if (listen(server_fd, 5) < 0) { perror("listen"); exit(1); }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        if (client_fd < 0) { perror("accept"); continue; }

        if (fork() == 0) { // child process
            close(server_fd); // child doesn't need listener
            read(client_fd, buffer, BUFFER_SIZE);
            printf("Received: %s\n", buffer);
            char *msg = "Hello from server (fork)";
            write(client_fd, msg, strlen(msg));
            close(client_fd);
            exit(0);
        } else {
            close(client_fd); // parent closes client socket
        }
    }

    close(server_fd);
    return 0;
}
/*

sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ gcc fork_server.c -o fork_server
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ gcc client.c -o client
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./fork_server
Fork server listening on port 6000...
Received: Hello server
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./client
Connected to server.
Client: Hello server
Server: Hello from fork server
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ gcc thread_server.c -o thread_server -pthread
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./thread_server
Thread server listening on port 6000...
Received: Hi thread server
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./client
Connected to server.
Client: Hi thread server
Server: Hello from thread server

*/
