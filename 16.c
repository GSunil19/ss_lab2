#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int p2c[2], c2p[2];
    char parent_msg[] = "Hello from parent!";
    char child_msg[] = "Hello from child!";
    char buf[100];

    if (pipe(p2c) == -1 || pipe(c2p) == -1) {
        perror("pipe");
        exit(1);
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }
    else if (pid > 0) {
        close(p2c[0]);
        close(c2p[1]);
        if (write(p2c[1], parent_msg, strlen(parent_msg) + 1) == -1) {
            perror("write parent");
            exit(1);
        }
        close(p2c[1]);

        ssize_t n = read(c2p[0], buf, sizeof(buf));
        if (n == -1) {
            perror("read parent");
            exit(1);
        }
        printf("Parent received: %s\n", buf);
        close(c2p[0]);
        wait(NULL);
    }
    else {
        close(p2c[1]);
        close(c2p[0]);
        ssize_t n = read(p2c[0], buf, sizeof(buf));
        if (n == -1) {
            perror("read child");
            exit(1);
        }
        printf("Child received: %s\n", buf);
        close(p2c[0]);

        if (write(c2p[1], child_msg, strlen(child_msg) + 1) == -1) {
            perror("write child");
            exit(1);
        }
        close(c2p[1]);
    }
    return 0;
}