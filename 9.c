
/*
============================================================================
Name        : 9.c
Author      : Gumpu Sunil
Description : Write a program to ignore a SIGINT signal then reset the default action of the SIGINT
signal - Use signal system call.
Date        : 24th Sep, 2025
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    printf("Ignoring SIGINT for 5 seconds. Try pressing Ctrl+C...\n");
    signal(SIGINT, SIG_IGN); // ignore Ctrl+C
    sleep(5);

    printf("Resetting SIGINT to default action. Press Ctrl+C now...\n");
    signal(SIGINT, SIG_DFL); // restore default action
    sleep(5); // wait to test

    printf("Program finished normally.\n");
    return 0;
}
/*
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ gcc 9.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./a.out
Ignoring SIGINT for 5 seconds. Try pressing Ctrl+C...
Resetting SIGINT to default action. Press Ctrl+C now...
^C
*/
