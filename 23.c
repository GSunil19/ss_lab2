

/*
============================================================================
Name        : 23.c
Author      : Gumpu Sunil
Description : Write a program to print the maximum number of files can be opened within a process and size of a pipe (circular buffer).
Date        : 29th Sep, 2025
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <fcntl.h>

#include<linux/fs.h>

#ifndef F_GETPIPE_SZ
#define F_GETPIPE_SZ 1032
#endif
int main() {
    struct rlimit rl;
    int pipefd[2];

    // Get max number of files per process
    if (getrlimit(RLIMIT_NOFILE, &rl) == -1) {
        perror("getrlimit");
        exit(1);
    }
    printf("Maximum number of files a process can open:\n");
    printf("Soft limit: %ld\n", rl.rlim_cur);
    printf("Hard limit: %ld\n\n", rl.rlim_max);

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    // Get pipe size (circular buffer size)
    int pipe_size = fcntl(pipefd[0], F_GETPIPE_SZ);
    if (pipe_size == -1) {
        perror("fcntl F_GETPIPE_SZ");
        exit(1);
    }
    printf("Pipe (circular buffer) size: %d bytes\n", pipe_size);

    // Close pipe
    close(pipefd[0]);
    close(pipefd[1]);

    return 0;
}
/*
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ gcc 23.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./a.out
Maximum number of files a process can open:
Soft limit: 1024
Hard limit: 1048576

Pipe (circular buffer) size: 65536 bytes


*/
