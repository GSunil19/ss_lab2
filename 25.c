/*
============================================================================
Name        : 25.c
Author      : Gumpu Sunil
Description : Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
a. access permission
b. uid, gid
c. time of last message sent and received
d. time of last change in the message queue
d. size of the queue
f. number of messages in the queue
g. maximum number of bytes allowed
h. pid of the msgsnd and msgrcv
Date        : 24th Sep, 2025
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

int main() {
    key_t key;
    int msqid;
    struct msqid_ds buf;

    // Generate key (or use known key)
    key = ftok(".", 'A');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Get message queue ID
    msqid = msgget(key, 0666);
    if (msqid == -1) {
        perror("msgget");
        exit(1);
    }

    // Get message queue info
    if (msgctl(msqid, IPC_STAT, &buf) == -1) {
        perror("msgctl");
        exit(1);
    }

    printf("Message Queue Information:\n");
    printf("--------------------------\n");
    printf("Access Permissions: %o\n", buf.msg_perm.mode & 0777);
    printf("Owner UID: %d\n", buf.msg_perm.uid);
    printf("Owner GID: %d\n", buf.msg_perm.gid);
    printf("Time of last msgsnd: %s", ctime(&buf.msg_stime));
    printf("Time of last msgrcv: %s", ctime(&buf.msg_rtime));
    printf("Time of last change: %s", ctime(&buf.msg_ctime));
    printf("Current size (bytes): %ld\n", buf.__msg_cbytes);
    printf("Number of messages in queue: %ld\n", buf.msg_qnum);
    printf("Maximum bytes allowed: %ld\n", buf.msg_qbytes);
    printf("PID of last msgsnd: %d\n", buf.msg_lspid);
    printf("PID of last msgrcv: %d\n", buf.msg_lrpid);

    return 0;
}
/*


sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ nano 25.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ gcc 25.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./a.out
Message Queue Information:
--------------------------
Access Permissions: 666
Owner UID: 1000
Owner GID: 1000
Time of last msgsnd: Thu Jan  1 05:30:00 1970
Time of last msgrcv: Thu Jan  1 05:30:00 1970
Time of last change: Wed Oct  1 21:12:31 2025
Current size (bytes): 0
Number of messages in queue: 0
Maximum bytes allowed: 16384
PID of last msgsnd: 0
PID of last msgrcv: 0


*/
