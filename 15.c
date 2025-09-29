
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    int fd[2];
    char write_msg[] = "Hello from child!";
    char read_msg[100];

    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(1);
    }

    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork");
        exit(1);
    }
    else if (pid > 0)
    {
        close(fd[1]);
        ssize_t n = read(fd[0], read_msg, sizeof(read_msg));
        if (n == -1)
        {
            perror("read");
            exit(1);
        }
        printf("Parent received: %s\n", read_msg);
        close(fd[0]);
        wait(NULL);
    }
    else
    {
        close(fd[0]);
        if (write(fd[1], write_msg, strlen(write_msg) + 1) == -1)
        {
            perror("write");
            exit(1);
        }
        close(fd[1]);
    }
    return 0;
}