

/*
============================================================================
Name        : 7.c
Author      : Gumpu Sunil
Description : Write a simple program to print the created thread ids.
Date        : 25th Sep, 2025
============================================================================
*/

#include <stdio.h>
#include <pthread.h>

void* thread_func(void* arg) {
    printf("Thread created with ID: %lu\n", (unsigned long)pthread_self());
    return NULL;
}

int main() {
    pthread_t threads[3];

    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, thread_func, NULL);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Main thread ID: %lu\n", (unsigned long)pthread_self());
    return 0;
}
/*
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ nano 7.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ gcc 7.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./a.out
Thread created with ID: 128180006414016
Thread created with ID: 128180014806720
Thread created with ID: 128179998021312
Main thread ID: 128180018014016

*/
