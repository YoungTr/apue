//
// Created by YoungTr on 2022/3/16.
//

#include <unistd.h>
#include <printf.h>
#include <stdlib.h>

int main(void) {
    pid_t pid;

    if ((pid = fork()) < 0) {
        printf("fork error");
    } else if (pid == 0) {   /* first child */
        if ((pid = fork()) < 0)
            printf("fork error");
        else if (pid > 0)
            // pid > 0, first child
            exit(0);    /* parent from second fork == first child */

        // pid == 0, second child
        sleep(5);
        printf("second child, parent pid = %ld\n", (long) getppid());
        exit(0);
    }

    if (waitpid(pid, NULL, 0) != pid)    /* wait for first child */
        printf("waitpid error");

    exit(0);

}