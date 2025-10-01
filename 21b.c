/*
============================================================================
Name        : 21b.c
Author      : Gumpu Sunil
Description : Write two programs so that both can communicate by FIFO -Use two way communications.
Date        : 24th Sep, 2025
============================================================================
*/


// program2.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    char buffer[100];
    int fd1, fd2;

    // Open FIFOs
    fd1 = open("fifo1", O_RDONLY); // read from Program1
    fd2 = open("fifo2", O_WRONLY); // write to Program1

    if (fd1 == -1 || fd2 == -1) {
        perror("open");
        exit(1);
    }

    // Read message from Program1
    read(fd1, buffer, sizeof(buffer));
    printf("Program2 received: %s\n", buffer);

    // Send message back
    char *msg2 = "Hello from Program2";
    write(fd2, msg2, strlen(msg2)+1);

    close(fd1);
    close(fd2);

    return 0;
}
