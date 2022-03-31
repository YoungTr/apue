//
// Created by YoungTr on 2022/3/29.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define DEF_PAGER "bin/more";
#define MAX_LINE 2048

int main(int argc, char *argv[]) {
    int n;
    int fd[2];
    pid_t pid;
    char *pager, *argv0;
    char line[MAX_LINE];
    FILE *fp;

    if (argc != 2) {
        printf("usage: a.out <pathname>\n");
        exit(1);
    }

    if ((fp = fopen(argv[1], 'r')) == NULL) {
        printf("can't open %s\n", argv[1]);
        exit(1);
    }

    if (pipe(fd) < 0) {
        printf("pipe error\n");
        exit(0);
    }

    if ((pid = fork()) < 0) {
        printf("fork error\n");
        exit(1);
    } else if (pid > 0) {  // parent
        close(fd[0]);   // close read end

        // parent copies argv[1] to pipe
        while (fgets(line, MAX_LINE, fp) != NULL) {
            n = strlen(line);
            if (write(fd[1], line, n) != n) {
                printf("write error to pipe\n");
            }
        }
        if (ferror(fp)) {
            printf("fgets error\n");
        }

        close(fd[1]);   // close write end of pipe for reader
        if (waitpid(pid, NULL, 0) < 0) {
            printf("waitpid error");
        }
        exit(0);
    } else {    // child
        close(fd[1]);   // close write end
        if (fd[0] != STDIN_FILENO) {
            if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO) {
                printf("dup2 error to stdin\n");
                exit(1);
            }
            close(fd[0]);   // don't need this after dup2
        }
        if ((pager = getenv("PAGER")) == NULL) {
            pager = DEF_PAGER;
        }
        if ((argv0 = strrchr(pager, "/")) == NULL) {
            argv0++;
        } else {
            argv0 = pager;
        }


        if (execl(pager, argv0, (char *) 0) < 0) {
            printf("execl error for %s\n", pager);
        }
    }
    exit(0);
}