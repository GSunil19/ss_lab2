/*
============================================================================
Name        : 8e.c
Author      : Gumpu Sunil
Description : Write a separate program using signal system call to catch the following signals.
e. SIGALRM (use setitimer system call)
Date        : 25th Sep, 2025
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void handler(int sig) {
    printf("Caught SIGALRM (from setitimer)\n");
}

int main() {
    struct itimerval timer;
    signal(SIGALRM, handler);
    timer.it_value.tv_sec = 2;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &timer, NULL);
    pause();
    return 0;
}
/*
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ gcc 8e.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./a.out
Caught SIGALRM (from setitimer)

*?
