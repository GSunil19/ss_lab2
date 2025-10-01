
/*
============================================================================
Name        : 28.c
Author      : Gumpu Sunil
Description : Write a program to change the exiting message queue permission. (use msqid_ds structure)
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
    struct msqid_ds buf;

    // Generate key (same as existing message queue)
    key = ftok(".", 'A'); 
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Get existing message queue
    msqid = msgget(key, 0666);
    if (msqid == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Message queue accessed. msqid = %d\n", msqid);

    // Get current attributes
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

sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ gcc 28.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./a.out
Message queue accessed. msqid = 1
Current permission: 666
Permission changed successfully to: 644
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K350
*/

