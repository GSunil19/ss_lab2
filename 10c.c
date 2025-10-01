

/*
============================================================================
Name        : 10c.c
Author      : Gumpu Sunil
Description : Write a separate program using sigaction system call to catch the following signals.
a. SIGFPE
Date        : 27th Sep, 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void fpe_handler(int signum) {
    if (signum == SIGFPE) {
        printf("\nSIGFPE caught by sigaction(). Terminating.\n");
        exit(1);
    }
}

int main() {
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = fpe_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    
    if (sigaction(SIGFPE, &sa, NULL) == -1) {
        perror("sigaction error");
        return 1;
    }

    printf("Handler registered. Attempting division by zero...\n");
    
    // Using variables prevents the compile-time warning
    volatile int numerator = 1;
    volatile int denominator = 0;

    int a = numerator / denominator; 
    
    printf("Unreachable code. Result: %d\n", a);
    return 0;
}

/*
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ gcc 10c.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./a.out
Handler registered. Attempting division by zero...

SIGFPE caught by sigaction(). Terminating.

*/
