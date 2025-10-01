/*
============================================================================
Name        : 27.c
Author      : Gumpu Sunil
Description : Write a program to receive messages from the message queue.
a. with 0 as a flag
b. with IPC_NOWAIT as a flag
Date        : 24th Sep, 2025
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>

#define MAX_TEXT 100

struct message {
    long mtype;
    char mtext[MAX_TEXT];
};

int main() {
    key_t key;
    int msqid;
    struct message msg;

    // Generate key (same as sender)
    key = ftok(".", 'A');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Get message queue
    msqid = msgget(key, 0666);
    if (msqid == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Receiving message with blocking (flag=0)...\n");

    // Blocking receive
    if (msgrcv(msqid, &msg, sizeof(msg.mtext), 0, 0) == -1) {
        perror("msgrcv blocking");
        exit(1);
    }
    printf("Received (blocking): %s\n", msg.mtext);

    printf("\nReceiving message with non-blocking (flag=IPC_NOWAIT)...\n");

    // Non-blocking receive
    if (msgrcv(msqid, &msg, sizeof(msg.mtext), 0, IPC_NOWAIT) == -1) {
        if (errno == ENOMSG) {
            printf("No message available (non-blocking).\n");
        } else {
            perror("msgrcv non-blocking");
            exit(1);
        }
    } else {
        printf("Received (non-blocking): %s\n", msg.mtext);
    }

    return 0;
}
/*


sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ gcc 27.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./a.out
Receiving message with blocking (flag=0)...
Received (blocking): Hello, this is a test message.

Receiving message with non-blocking (flag=IPC_NOWAIT)...
No message available (non-blocking).


*/
