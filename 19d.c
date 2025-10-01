

/*
============================================================================
Name        : 19d.c
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
    if (mknod("myfifo_mknod", S_IFIFO | 0666, 0) == -1) {
        perror("mknod");
        return 1;
    }
    printf("FIFO created using mknod system call\n");
    return 0;
}
/*

sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ gcc 19d.c
sunil@sunil-VivoBook-ASUSLaptop-K3502ZA-K3502ZA:~/Desktop/ss_lab2$ ./a.out
FIFO created using mknod system call

*/
