/*
============================================================================
Name        : 8g.c
Author      : Gumpu Sunil
Description :  Write a separate program using signal system call to catch the following signals. g. SIGPROF (use setitimer system call)
Date        : 24th Sep, 2025
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void handler(int sig) {
    printf("Caught SIGPROF\n");
}

int main() {
    struct itimerval timer;
    signal(SIGPROF, handler);
    timer.it_value.tv_sec = 1;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 1;
    timer.it_interval.tv_usec = 0;
    setitimer(ITIMER_PROF, &timer, NULL);
    while (1); // consume CPU to trigger
    return 0;
}
/*
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ gcc 8g.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./a.out
Caught SIGPROF
Caught SIGPROF
*/
