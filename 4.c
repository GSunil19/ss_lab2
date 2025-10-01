
/*
============================================================================
Name        : 4.c
Author      : Gumpu Sunil
Description : Write a program to measure how much time is taken to execute 100 getppid ( )
system call. Use time stamp counter.
Date        : 24th Sep, 2025
============================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <x86intrin.h>

int main() {
    unsigned long long start, end;
    int i;

    start = __rdtsc();   // Read time-stamp counter
    for (i = 0; i < 100; i++) {
        getppid();
    }
    end = __rdtsc();

    printf("Cycles taken for 100 getppid() calls: %llu\n", end - start);
    printf("Average cycles per call: %llu\n", (end - start) / 100);

    return 0;
}
/*
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ gcc 4.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./a.out
Cycles taken for 100 getppid() calls: 156680
Average cycles per call: 1566


*/
