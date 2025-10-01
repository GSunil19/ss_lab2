/*
============================================================================
Name        : 20.c
Author      : Gumpu Sunil
Description : Write two programs so that both can communicate by FIFO -Use one way communication.
Date        : 28h Sep, 2025
============================================================================
*/


#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

int main() {
    key_t key = 1234; // Key for the message queue
    int msqid;
    struct msqid_ds buf;

    // Create or get message queue
    msqid = msgget(key, 0666 | IPC_CREAT);
    if (msqid == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Message queue created or accessed. msqid = %d\n", msqid);

    // Get current message queue attributes
    if (msgctl(msqid, IPC_STAT, &buf) == -1) {
        perror("msgctl IPC_STAT");
        exit(1);
    }

    printf("Current permission: %o\n", buf.msg_perm.mode & 0777);

    // Change permission to 0644
    buf.msg_perm.mode = 0644;

    if (msgctl(msqid, IPC_SET, &buf) == -1) {
        perror("msgctl IPC_SET");
        exit(1);
    }

    printf("Permission changed successfully to: %o\n", buf.msg_perm.mode & 0777);

    return 0;
}
/*

sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ gcc 20.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./a.out
Message queue created or accessed. msqid = 0
Current permission: 666
Permission changed successfully to: 644



*/
