

/*
============================================================================
Name        : 8d.c
Author      : Gumpu Sunil
Description : Write a separate program using signal system call to catch the following signals.
d. SIGALRM (use alarm system call)
Date        : 26th Sep, 2025
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
    printf("Caught SIGALRM (from alarm)\n");
}

int main() {
    signal(SIGALRM, handler);
    alarm(3); // triggers after 3 seconds
    pause();
    return 0;
}
/*
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ gcc 8d.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./a.out
Caught SIGALRM (from alarm)

*/
