/*
============================================================================
Name        : 19e.c
Author      : Gumpu Sunil
Description : Create a FIFO file by
a. mknod command
b. mkfifo command
c. use strace command to find out, which command (mknod or mkfifo) is better.
c. mknod system call
d. mkfifo library function
Date        : 24th Sep, 2025
============================================================================
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    if (mkfifo("myfifo_mkfifo", 0666) == -1) {
        perror("mkfifo");
        return 1;
    }
    printf("FIFO created using mkfifo() library function\n");
    return 0;
}
/*

sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ gcc 19e.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./a.out
FIFO created using mkfifo() library function

*/
