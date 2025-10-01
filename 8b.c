

/*
============================================================================
Name        : 8b.c
Author      : Gumpu Sunil
Description : Write a separate program using signal system call to catch the following signals.
b. SIGINT
Date        : 26th Sep, 2025
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
    printf("Caught SIGINT (Ctrl+C)\n");
}

int main() {
    signal(SIGINT, handler);
    while (1) {
        printf("Running... Press Ctrl+C\n");
        sleep(2);
    }
    return 0;
}

/*
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ nano 8b.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ gcc 8b.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./a.out
Running... Press Ctrl+C
Running... Press Ctrl+C
^CCaught SIGINT (Ctrl+C)
Running... Press Ctrl+C
^CCaught SIGINT (Ctrl+C)
Running... Press Ctrl+C
Running... Press Ctrl+C

*/
