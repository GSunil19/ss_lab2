/*
============================================================================
Name        : 17a.c
Author      : Gumpu Sunil
Description : . Write a program to execute ls -l | wc.
a. use dup
Date        : 24th Sep, 2025
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include<sys/wait.h>
int main() {
    int fd[2];
    pipe(fd);

    if (fork() == 0) {
        // Child 1: ls -l
        close(fd[0]); // close read end
        close(1);
        dup(fd[1]);  // redirect stdout to pipe write end
        execlp("ls", "ls", "-l", NULL);
        perror("execlp");
        exit(1);
    }

    if (fork() == 0) {
        // Child 2: wc
        close(fd[1]); // close write end
        close(0);
        dup(fd[0]);   // redirect stdin to pipe read end
        execlp("wc", "wc", NULL);
        perror("execlp");
        exit(1);
    }

    // Parent
    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);

    return 0;
}
/*
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ gcc 17a.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./a.out
     42     371    2051

*/
