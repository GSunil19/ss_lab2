/*
============================================================================
Name        : 13reciever.c
Author      : Gumpu Sunil
Description : Write two programs: first program is waiting to catch SIGSTOP signal, the second program
will send the signal (using kill system call). Find out whether the first program is able to catch
the signal or not.
Date        : 24th Sep, 2025
============================================================================
*/


#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
    printf("Caught signal %d\n", sig);
}

int main() {
    printf("Receiver running, PID = %d\n", getpid());

    // Try to catch SIGSTOP
    signal(SIGSTOP, handler);

    while (1) {
        printf("Waiting...\n");
        sleep(2);
    }
    return 0;
}
/*
gcc: error: unrecognized command-line option ‘-13sender’
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ gcc 13sender.c -o 13sender
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./13receiver
Receiver running, PID = 7085
Waiting...
Waiting...
Waiting...
Waiting...
Waiting...
Waiting...
Waiting...
Waiting...
Waiting...
Waiting...
Waiting...
Waiting...
Waiting...
Waiting...
Waiting...
Waiting...
Waiting...
Waiting...

[14]+  Stopped                 ./13receiver

sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./13sender 7085
Sending SIGSTOP to process 7085
Signal sent successfully
[1]+  Exit 1                  ./13sender

*/
