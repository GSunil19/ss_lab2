
/*
============================================================================
Name        : 5.c
Author      : Gumpu Sunil
Description : Write a program to print the system limitation of
a. maximum length of the arguments to the exec family of functions.
b. maximum number of simultaneous process per user id.
c. number of clock ticks (jiffy) per second.
d. maximum number of open files
e. size of a page
f. total number of pages in the physical memory
g. number of currently available pages in the physical memory.
Date        : 25th Sep, 2025
============================================================================
*/


#include <stdio.h>
#include <unistd.h>

int main() {
    long arg_max = sysconf(_SC_ARG_MAX);
    long child_max = sysconf(_SC_CHILD_MAX);
    long clk_tck = sysconf(_SC_CLK_TCK);
    long open_max = sysconf(_SC_OPEN_MAX);
    long page_size = sysconf(_SC_PAGESIZE);
    long total_pages = sysconf(_SC_PHYS_PAGES);
    long avail_pages = sysconf(_SC_AVPHYS_PAGES);

    printf("a. Maximum length of arguments to exec: %ld\n", arg_max);
    printf("b. Maximum number of simultaneous processes per user: %ld\n", child_max);
    printf("c. Number of clock ticks per second: %ld\n", clk_tck);
    printf("d. Maximum number of open files: %ld\n", open_max);
    printf("e. Size of a page: %ld bytes\n", page_size);
    printf("f. Total number of pages in physical memory: %ld\n", total_pages);
    printf("g. Number of currently available pages: %ld\n", avail_pages);

    return 0;
}
/*

sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ gcc 5.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./a.out
a. Maximum length of arguments to exec: 2097152
b. Maximum number of simultaneous processes per user: 61602
c. Number of clock ticks per second: 100
d. Maximum number of open files: 1024
e. Size of a page: 4096 bytes
f. Total number of pages in physical memory: 3996541
g. Number of currently available pages: 2872045


*/
