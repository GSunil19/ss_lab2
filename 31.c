
/*
============================================================================
Name        : 31.c
Author      : Gumpu Sunil
Description : Write a program to create a semaphore and initialize value to the semaphore.
a. create a binary semaphore
b. create a counting semaphore
Date        : 30th Sep, 2025
============================================================================
*/



#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main() {
    key_t key_bin, key_count;
    int semid_bin, semid_count;

    // Generate keys
    key_bin = ftok(".", 'B');   // Binary semaphore
    key_count = ftok(".", 'C'); // Counting semaphore

    if (key_bin == -1 || key_count == -1) {
        perror("ftok");
        exit(1);
    }

    // Create binary semaphore (1 semaphore)
    semid_bin = semget(key_bin, 1, 0666 | IPC_CREAT);
    if (semid_bin == -1) {
        perror("semget binary");
        exit(1);
    }

    // Initialize binary semaphore to 1
    if (semctl(semid_bin, 0, SETVAL, 1) == -1) {
        perror("semctl binary");
        exit(1);
    }

    printf("Binary semaphore created. semid = %d, initial value = 1\n", semid_bin);

    // Create counting semaphore (1 semaphore)
    semid_count = semget(key_count, 1, 0666 | IPC_CREAT);
    if (semid_count == -1) {
        perror("semget counting");
        exit(1);
    }

    // Initialize counting semaphore to 5 (example)
    if (semctl(semid_count, 0, SETVAL, 5) == -1) {
        perror("semctl counting");
        exit(1);
    }

    printf("Counting semaphore created. semid = %d, initial value = 5\n", semid_count);

    return 0;
}
/*

sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ gcc 31.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./a.ouit
bash: ./a.ouit: No such file or directory
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./a.out
Binary semaphore created. semid = 0, initial value = 1
Counting semaphore created. semid = 1, initial value = 5


*/
