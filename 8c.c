
/*
============================================================================
Name        : 8c.c
Author      : Gumpu Sunil
Description : Write a separate program using signal system call to catch the following signals.
C. SIGPE
Date        : 26th Sep, 2025
============================================================================
*/



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Starting SIGFPE demonstration...\n");
    
    int numerator = 100;
    int denominator = 0; // The divisor that will cause the exception

    printf("Attempting to divide %d by %d...\n", numerator, denominator);
    
    // The following line will attempt integer division by zero.
    // On most systems, this causes a SIGFPE signal to be sent to the process.
    int result = numerator / denominator; 

    // This line will typically not be reached because the signal terminates the program
    // immediately after the division attempt.
    printf("Result of division: %d\n", result); 

    printf("Program finished normally (should not happen).\n");
    return 0;
}
/*

sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ gcc 8c.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./a.out
Starting SIGFPE demonstration...
Attempting to divide 100 by 0...
Floating point exception (core dumped)

*/
