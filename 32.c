/*
============================================================================
Name        : 32.c
Author      : Gumpu Sunil
Description : Write a program to implement semaphore to protect any critical section.
a. rewrite the ticket number creation program using semaphore
b. protect shared memory from concurrent write access
c. protect multiple pseudo resources ( may be two) using counting semaphore
d. remove the created semaphore
Date        : 30th Sep, 2025
============================================================================
*/


#define _POSIX_C_SOURCE 200809L
#define _DEFAULT_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <time.h>
#include <string.h>

// Named IPC resources
#define BINARY_SEM_NAME "/ticket_lock"
#define COUNTING_SEM_NAME "/resource_count"
#define SHM_NAME "/ticket_shm"
#define NUM_PROCESSES 5
#define MAX_TICKETS 3

// Shared data structure
typedef struct {
    int ticket_counter;
    char shared_message[128];
} SharedData;

// Function to handle cleanup of semaphores (Task D)
void cleanup_semaphores() {
    printf("\n[Parent] Removing semaphores (Task D: sem_unlink)...\n");
    sem_unlink(BINARY_SEM_NAME);
    sem_unlink(COUNTING_SEM_NAME);
}

// Function to simulate resource usage using counting semaphore (Task C)
void use_resource(sem_t *counting_sem, int process_id) {
    int resource_count;

    printf("--- Process %d: Waiting for counting resource...\n", process_id);
    if (sem_wait(counting_sem) == -1) return; // Wait (blocks if count is 0)
    
    sem_getvalue(counting_sem, &resource_count);
    printf("--- Process %d: ACQUIRED resource access. Remaining slots: %d. Using resource for 0.5s...\n", process_id, resource_count);
    
    // Simulate usage (0 to 499 milliseconds)
    usleep((rand() % 500) * 1000); 

    printf("--- Process %d: Releasing counting resource.\n", process_id);
    sem_post(counting_sem); // Release (increments count)
}

// Function containing critical section logic protected by binary semaphore (Task A & B)
void handle_critical_section(sem_t *binary_sem, SharedData *shared_data, int process_id) {
    
    // Wait on the binary semaphore (acquires lock)
    printf("Process %d: Waiting to enter ticket creation CS...\n", process_id);
    if (sem_wait(binary_sem) == -1) return;

    printf("\n==== Process %d: ENTERING CRITICAL SECTION (Ticket Lock Acquired) ====\n", process_id);

    if (shared_data->ticket_counter < MAX_TICKETS) {
        // a. Ticket number creation (Critical Section)
        shared_data->ticket_counter++; 
        printf("TICKET CREATED: New Ticket Number: %d\n", shared_data->ticket_counter);
        
        // b. Protecting shared memory access
        snprintf(shared_data->shared_message, sizeof(shared_data->shared_message), 
                 "Ticket %d created by process %d", 
                 shared_data->ticket_counter, process_id);
        printf("SHARED MEMORY WRITE: Message updated.\n");

    } else {
        printf("TICKET CREATION SKIPPED: Maximum tickets reached.\n");
    }
    
    printf("==== Process %d: EXITING CRITICAL SECTION (Ticket Lock Released) ====\n\n", process_id);
    
    // Release the binary semaphore (releases lock)
    sem_post(binary_sem);
}


int main() {
    sem_t *binary_sem = SEM_FAILED;
    sem_t *counting_sem = SEM_FAILED;
    SharedData *shared_data = NULL;
    int shm_fd;

    srand(time(NULL) * getpid());

    // 1. Setup Shared Memory
    shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) { perror("shm_open error"); return 1; }
    ftruncate(shm_fd, sizeof(SharedData));
    shared_data = (SharedData *)mmap(NULL, sizeof(SharedData), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shared_data == MAP_FAILED) { perror("mmap error"); shm_unlink(SHM_NAME); return 1; }
    shared_data->ticket_counter = 0;
    
    // 2. Setup Binary Semaphore (Initial value 1 for mutual exclusion)
    binary_sem = sem_open(BINARY_SEM_NAME, O_CREAT, 0666, 1);
    
    // 3. Setup Counting Semaphore (Initial value 2 for 2 resources - Task C)
    counting_sem = sem_open(COUNTING_SEM_NAME, O_CREAT, 0666, 2);

    if (binary_sem == SEM_FAILED || counting_sem == SEM_FAILED) {
        perror("Semaphore open error");
        goto cleanup;
    }

    printf("[Parent] Starting %d child processes...\n", NUM_PROCESSES);

    // 4. Fork Child Processes
    for (int i = 0; i < NUM_PROCESSES; i++) {
        pid_t pid = fork();
        
        if (pid == 0) { // Child Process
            int my_id = getpid();
            srand(time(NULL) ^ my_id); 

            // Execute critical sections (Tasks A & B)
            handle_critical_section(binary_sem, shared_data, my_id);
            
            // Use counting resource (Task C)
            use_resource(counting_sem, my_id);
            
            // Child cleanup
            sem_close(binary_sem);
            sem_close(counting_sem);
            munmap(shared_data, sizeof(SharedData));
            exit(0);
        } else if (pid < 0) {
            perror("fork error");
            goto cleanup;
        }
    }

    // 5. Parent Waits for Children
    for (int i = 0; i < NUM_PROCESSES; i++) {
        wait(NULL);
    }
    printf("\n[Parent] All child processes finished.\n");
    
    // Print final state
    printf("\n[Parent] FINAL TICKET COUNT: %d\n", shared_data->ticket_counter);
    printf("[Parent] FINAL SHARED MESSAGE: '%s'\n", shared_data->shared_message);

cleanup:
    // 6. Final Cleanup
    if (binary_sem != SEM_FAILED) sem_close(binary_sem);
    if (counting_sem != SEM_FAILED) sem_close(counting_sem);

    cleanup_semaphores(); // Task D
    if (shared_data != MAP_FAILED) munmap(shared_data, sizeof(SharedData));
    shm_unlink(SHM_NAME);

    return 0;
}


/*

sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ nano 32.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ gcc 32.c -o 32 -lrt
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./a.out
Binary semaphore created. semid = 0, initial value = 1
Counting semaphore created. semid = 1, initial value = 5


*/
