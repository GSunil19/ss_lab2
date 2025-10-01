
/*
============================================================================
Name        : 11.c
Author      : Gumpu Sunil
Description : Write a program to ignore a SIGINT signal then reset the default action of the SIGINT signal -
use sigaction system call.
Date        : 27th Sep, 2025
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    struct sigaction sa;

    // Ignore SIGINT
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);

    printf("SIGINT is ignored for 5 seconds. Try pressing Ctrl+C...\n");
    sleep(5);

    // Reset SIGINT to default action
    sa.sa_handler = SIG_DFL;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);

    printf("SIGINT reset to default. Press Ctrl+C now...\n");
    sleep(5);

    printf("Program finished normally.\n");
    return 0;
}


/*

sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ gcc 11.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./a.out
SIGINT is ignored for 5 seconds. Try pressing Ctrl+C...
^CSIGINT reset to default. Press Ctrl+C now...
^C

*/
