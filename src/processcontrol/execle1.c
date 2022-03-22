//
// Created by YoungTr on 2022/3/16.
//

#include <stddef.h>
#include <unistd.h>
#include <printf.h>
#include <sys/wait.h>
#include <stdlib.h>

char *en_init[] = {"USER=unknown", "PATH=/temp", NULL};

int main(void) {
    pid_t pid;

    if ((pid = fork()) < 0) {
        printf("fork error");
    } else if (pid == 0) {
        if (execle("/CLionProjects/apue/src/processcontrol/echoall", "echoall", "myarg1",
                   "MY ARG2", NULL, en_init) < 0) {
            printf("execle error");
        }
    }

    if (waitpid(pid, NULL, 0) < 0) {
        printf("wait error");
    }

    exit(0);
}
