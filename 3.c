/*
============================================================================
Name        : 3.c
Author      : Gumpu Sunil
Description : Write a program to set (any one) system resource limit. Use setrlimit system call.
Date        : 25th Sep, 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>

int main() {
    struct rlimit limit;

    // Set CPU time limit to 5 seconds
    limit.rlim_cur = 5;
    limit.rlim_max = 10;
    if (setrlimit(RLIMIT_CPU, &limit) != 0) {
        perror("setrlimit");
        exit(1);
    }

    printf("CPU time limit set to 5 seconds (soft), 10 seconds (hard)\n");
    printf("Running an infinite loop to test...\n");

    while (1); // Busy loop to consume CPU time

    return 0;
}
/*
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ gcc 3.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./a.out
CPU time limit set to 5 seconds (soft), 10 seconds (hard)
Running an infinite loop to test...
CPU time limit exceeded (core dumped)

*/
