
/*
============================================================================
Name        : 10b.c
Author      : Gumpu Sunil
Description : Write a separate program using sigaction system call to catch the following signals.
a. SIGINT
Date        : 27th Sep, 2025
============================================================================
*/


#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
    printf("Caught SIGINT (Ctrl+C)\n");
}

int main() {
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);

    while (1) {
        printf("Running... Press Ctrl+C\n");
        sleep(2);
    }

    return 0;
}
/*


sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ nano 10a.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ gcc 10b.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./a.out
Running... Press Ctrl+C
Running... Press Ctrl+C
^CCaught SIGINT (Ctrl+C)


*/
