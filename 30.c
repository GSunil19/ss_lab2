
/*
============================================================================
Name        : 30.c
Author      : Gumpu Sunil
Description : Write a program to create a shared memory.
a. write some data to the shared memory
b. attach with O_RDONLY and check whether you are able to overwrite.
c. detach the shared memory
d. remove the shared memory
Date        : 30th Sep, 2025
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <errno.h>

#define SHM_SIZE 1024 // 1 KB shared memory

int main() {
    key_t key;
    int shmid;
    char *shm_ptr;

    // Generate a key
    key = ftok(".", 'S');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Create shared memory
    shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }
    printf("Shared memory created. shmid = %d\n", shmid);

    // Attach shared memory (read-write)
    shm_ptr = (char *) shmat(shmid, NULL, 0);
    if (shm_ptr == (char *) -1) {
        perror("shmat read-write");
        exit(1);
    }

    // Write some data
    strcpy(shm_ptr, "Hello, Shared Memory!");
    printf("Data written to shared memory: %s\n", shm_ptr);

    // Attach shared memory read-only
    char *shm_ro = (char *) shmat(shmid, NULL, SHM_RDONLY);
    if (shm_ro == (char *) -1) {
        perror("shmat read-only");
        exit(1);
    }

    printf("Read-only attached data: %s\n", shm_ro);

    // Attempt to overwrite (should fail, may cause segmentation fault)
    printf("Attempting to overwrite read-only memory...\n");
    errno = 0;
    if (shm_ro != NULL) {
        shm_ro[0] = 'h'; // This should fail
        if (errno != 0)
            perror("Overwrite failed as expected");
        else
            printf("Overwrite succeeded (unexpected)\n");
    }

    // Detach shared memory
    if (shmdt(shm_ptr) == -1) {
        perror("shmdt rw");
    }
    if (shmdt(shm_ro) == -1) {
        perror("shmdt ro");
    }

    // Remove shared memory
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl IPC_RMID");
        exit(1);
    }
    printf("Shared memory removed successfully.\n");

    return 0;
}
/*

sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ gcc 30.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./a.out
Shared memory created. shmid = 0
Data written to shared memory: Hello, Shared Memory!
Read-only attached data: Hello, Shared Memory!
Attempting to overwrite read-only memory...
Segmentation fault (core dumped)

*/
