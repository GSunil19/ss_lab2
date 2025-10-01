

/*
============================================================================
Name        : 26.c
Author      : Gumpu Sunil
Description : Write a program to send messages to the message queue. Check $ipcs -q
Date        : 24th Sep, 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_TEXT 100

struct message {
    long mtype;
    char mtext[MAX_TEXT];
};

int main() {
    key_t key;
    int msqid;
    struct message msg;

    // Generate key
    key = ftok(".", 'A');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Get or create message queue
    msqid = msgget(key, 0666 | IPC_CREAT);
    if (msqid == -1) {
        perror("msgget");
        exit(1);
    }

    // Prepare message
    msg.mtype = 1;  // message type > 0
    strcpy(msg.mtext, "Hello, this is a test message.");

    // Send message
    if (msgsnd(msqid, &msg, sizeof(msg.mtext), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }

    printf("Message sent successfully.\n");

    return 0;
}
/*

sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ nano 26.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ gcc 26.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./a.out
Message sent successfully.
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x000004d2 0          sunil      644        0            0           
0x4107393c 1          sunil      666        100          1           



*/
