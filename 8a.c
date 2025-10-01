

/*
============================================================================
Name        : 8a.c
Author      : Gumpu Sunil
Description : Write a separate program using signal system call to catch the following signals.
a. SIGSEGV
Date        : 25th Sep, 2025
============================================================================
*/


#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void handler(int sig) {
    printf("Caught SIGSEGV (Segmentation Fault)\n");
    exit(1);
}

int main() {
    signal(SIGSEGV, handler);
    int *p = NULL;
    *p = 42; // Cause segmentation fault
    return 0;
}
/*
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ gcc 8a.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./a.out
Caught SIGSEGV (Segmentation Fault)


*/
