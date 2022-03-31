//
// Created by YoungTr on 2022/3/29.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    int n;
    int fd[2];

    pid_t pid;
    char line[2048];

    if (pipe(fd) < 0)
        printf("pipe error\n");
    if ((pid = fork()) < 0)
        printf("fork error\n");
    else if (pid > 0) {
        // parent
        close(fd[0]);   // close read
        write(fd[1], "hello world\n", 12);
    } else {
        // child
        close(fd[1]);   // close write
        n = read(fd[0], line, 2048);
        write(STDOUT_FILENO, line, n);
    }

    exit(0);
}