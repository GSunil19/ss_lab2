

/*
============================================================================
Name        : 21a.c
Author      : Gumpu Sunil
Description : Write two programs so that both can communicate by FIFO -Use two way communications.
Date        : 24th Sep, 2025
============================================================================
*/

// program1.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    char buffer[100];
    int fd1, fd2;

    // Open FIFOs
    fd1 = open("fifo1", O_WRONLY); // write to Program2
    fd2 = open("fifo2", O_RDONLY); // read from Program2

    if (fd1 == -1 || fd2 == -1) {
        perror("open");
        exit(1);
    }

    // Send message to Program2
    char *msg1 = "Hello from Program1";
    write(fd1, msg1, strlen(msg1)+1);

    // Read message from Program2
    read(fd2, buffer, sizeof(buffer));
    printf("Program1 received: %s\n", buffer);

    close(fd1);
    close(fd2);

    return 0;
}


/*
unil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ gcc 21a.c -o 21a
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ gcc 21b.c -o 21b
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./21a
Program1 received: Hello from Program2

sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./21b
Program2 received: Hello from Program1

*/
