

/*
============================================================================
Name        : 8f.c
Author      : Gumpu Sunil
Description :  Write a separate program using signal system call to catch the following signals. f. SIGVTALRM (use setitimer system call)
Date        : 24th Sep, 2025
============================================================================
*/


#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void handler(int sig) {
    printf("Caught SIGVTALRM\n");
}

int main() {
    struct itimerval timer;
    signal(SIGVTALRM, handler);
    timer.it_value.tv_sec = 1;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 1;
    timer.it_interval.tv_usec = 0;
    setitimer(ITIMER_VIRTUAL, &timer, NULL);
    while (1); // busy loop to consume CPU
    return 0;
}
/*



sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ gcc 8f.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./a.out
Caught SIGVTALRM
Caught SIGVTALRM


*/
