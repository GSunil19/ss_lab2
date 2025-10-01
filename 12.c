
/*
============================================================================
Name        : 12.c
Author      : Gumpu Sunil
Description : Write a program to create an orphan process. Use kill system call to send SIGKILL signal to
the parent process from the child process.
Date        : 27th Sep, 2025
============================================================================
*/


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } 
    else if (pid == 0) {
        // Child process
        printf("Child process: PID = %d, Parent PID = %d\n", getpid(), getppid());
        sleep(2); // wait a bit
        printf("Child sending SIGKILL to parent...\n");
        kill(getppid(), SIGKILL);
        sleep(2); // give parent time to terminate
        printf("Child's new parent PID = %d (orphan)\n", getppid());
    } 
    else {
        // Parent process
        printf("Parent process: PID = %d\n", getpid());
        while (1) {
            printf("Parent is running...\n");
            sleep(1);
        }
    }

    return 0;
}
/*
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./a.out
Parent process: PID = 6668
Parent is running...
Child process: PID = 6669, Parent PID = 6668
Parent is running...
Child sending SIGKILL to parent...
Killed
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ Child's new parent PID = 2116 (orphan)

*/
