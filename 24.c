
/*
============================================================================
Name        : 24.c
Author      : Gumpu Sunil
Description : Write a program to create a message queue and print the key and message queue id.
Date        : 24th Sep, 2025
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    key_t key;
    int msqid;

    // Generate a key (here using ftok)
    key = ftok(".", 'A'); // "." = current directory, 'A' = project identifier
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Create message queue
    msqid = msgget(key, 0666 | IPC_CREAT);
    if (msqid == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Message queue created successfully.\n");
    printf("Key: %d\n", key);
    printf("Message Queue ID: %d\n", msqid);

    return 0;
}
/*
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ gcc 24.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./a.out
Message queue created successfully.
Key: 1090992444
Message Queue ID: 1


*/
