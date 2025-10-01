/*
============================================================================
Name        : 1a.c
Author      : Gumpu Sunil
Description : Write a separate program (for each time domain) to set a interval timer in 
              10sec and 10micro second
              a. ITIMER_REAL
Date        : 24th Sep, 2025
============================================================================
*/
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void handler(int sig) {
    printf("ITIMER_REAL expired\n");
}

int main() {
    struct itimerval timer;
    signal(SIGALRM, handler);
    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;
    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;
    setitimer(ITIMER_REAL, &timer, NULL);
    while (1) pause();
}
/*
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ nano 1a.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ gcc 1a.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./a.out
ITIMER_REAL expired
*/

