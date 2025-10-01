
/*
============================================================================
Name        : 17b.c
Author      : Gumpu Sunil
Description : Write a program to execute ls -l | wc.
a. use dup2
Date        : 24th Sep, 2025
============================================================================
*/


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    pipe(fd);

    if (fork() == 0) {
        // Child 1: ls -l
        dup2(fd[1], 1); // redirect stdout to pipe write end
        close(fd[0]);
        close(fd[1]);
        execlp("ls", "ls", "-l", NULL);
        perror("execlp");
        exit(1);
    }

    if (fork() == 0) {
        // Child 2: wc
        dup2(fd[0], 0); // redirect stdin to pipe read end
        close(fd[0]);
        close(fd[1]);
        execlp("wc", "wc", NULL);
        perror("execlp");
        exit(1);
    }

    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);

    return 0;
}


/*

sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ gcc 17b.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./a.out
     43     380    2101

*/
