/*
============================================================================
Name        : 1c.c
Author      : Gumpu Sunil
Description : Write a separate program (for each time domain) to set a interval timer in 
              10sec and 10micro second
              a. ITIMER_PROF
Date        : 24th Sep, 2025
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void handler(int sig) {
    printf("ITIMER_PROF expired\n");
}

int main() {
    struct itimerval timer;
    signal(SIGPROF, handler);
    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;
    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;
    setitimer(ITIMER_PROF, &timer, NULL);
    while (1);
} 

/*
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ gcc 1c.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./a.out
ITIMER_PROF expired


*/
