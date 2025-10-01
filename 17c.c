
/*
============================================================================
Name        : 17c.c
Author      : Gumpu Sunil
Description : write a program to execute ls -l | wc.
a. use fcntl
Date        : 24th Sep, 2025
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    pipe(fd);

    if (fork() == 0) {
        // Child 1: ls -l
        fcntl(fd[1], F_DUPFD, 1); // duplicate fd[1] to stdout
        close(fd[0]);
        close(fd[1]);
        execlp("ls", "ls", "-l", NULL);
        perror("execlp");
        exit(1);
    }

    if (fork() == 0) {
        // Child 2: wc
        fcntl(fd[0], F_DUPFD, 0); // duplicate fd[0] to stdin
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
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ nano 17c.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ gcc 17c.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./a.out
total 276
-rw-rw-r-- 1 sunil sunil   580 Oct  1 19:52 10a.c
-rw-rw-r-- 1 sunil sunil   696 Oct  1 19:53 10b.c
-rw-rw-r-- 1 sunil sunil  1076 Oct  1 19:56 10c.c
-rw-rw-r-- 1 sunil sunil   880 Oct  1 19:57 11.c
-rw-rw-r-- 1 sunil sunil  1132 Oct  1 20:32 12.c
-rwxrwxr-x 1 sunil sunil 16168 Oct  1 20:42 13receiver
-rw-rw-r-- 1 sunil sunil  1037 Oct  1 20:46 13receiver.c
-rwxrwxr-x 1 sunil sunil 16128 Oct  1 20:42 13sender

*/
