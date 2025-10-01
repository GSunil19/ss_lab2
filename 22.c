/*
============================================================================
Name        : 22.c
Author      : Gumpu Sunil
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use select system call with FIFO.
Date        : 24th Sep, 2025
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include<sys/types.h>
#include<sys/stat.h>
int main() {
    const char *fifo = "myfifo";
    char buffer[100];
    int fd;

    // Create FIFO if it does not exist
    mkfifo(fifo, 0666);

    // Open FIFO for reading
    fd = open(fifo, O_RDONLY | O_NONBLOCK);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    printf("Waiting for data on FIFO for 10 seconds...\n");

    fd_set readfds;
    struct timeval timeout;

    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);

    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    int ret = select(fd + 1, &readfds, NULL, NULL, &timeout);

    if (ret == -1) {
        perror("select");
    } else if (ret == 0) {
        printf("Timeout! No data received within 10 seconds.\n");
    } else {
        if (FD_ISSET(fd, &readfds)) {
            int n = read(fd, buffer, sizeof(buffer)-1);
            if (n > 0) {
                buffer[n] = '\0';
                printf("Received data: %s\n", buffer);
            } else {
                printf("No data read.\n");
            }
        }
    }

    close(fd);
    return 0;
}
/*

sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ gcc 22.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./a.out
Waiting for data on FIFO for 10 seconds...
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ hi this is sunil testing the program 


*/
