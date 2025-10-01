
/*
============================================================================
Name        : 18.c
Author      : Gumpu Sunil
Description : Write a program to find out total number of directories on the pwd.
execute ls -l | grep ^d | wc ? Use only dup2.
Date        : 21th Sep, 2025
============================================================================
*/


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int pipe1[2], pipe2[2];

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        exit(1);
    }

    // First child: ls -l
    if (fork() == 0) {
        dup2(pipe1[1], 1); // stdout -> pipe1 write end
        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe2[1]);
        execlp("ls", "ls", "-l", NULL);
        perror("execlp ls");
        exit(1);
    }

    // Second child: grep ^d
    if (fork() == 0) {
        dup2(pipe1[0], 0);  // stdin -> pipe1 read end
        dup2(pipe2[1], 1);  // stdout -> pipe2 write end
        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe2[1]);
        execlp("grep", "grep", "^d", NULL);
        perror("execlp grep");
        exit(1);
    }

    // Third child: wc
    if (fork() == 0) {
        dup2(pipe2[0], 0); // stdin -> pipe2 read end
        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe2[1]);
        execlp("wc", "wc", NULL);
        perror("execlp wc");
        exit(1);
    }

    // Parent closes all pipe ends
    close(pipe1[0]);
    close(pipe1[1]);
    close(pipe2[0]);
    close(pipe2[1]);

    // Wait for all children
    for (int i = 0; i < 3; i++) wait(NULL);

    return 0;
}
/*
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ gcc 18.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./a.out
      1      10      59

*/
