//
// Created by YoungTr on 2022/3/16.
//

#include <unistd.h>
#include <printf.h>
#include <stdlib.h>

int globval = 6;
char buf[] = "a write to stdout\n";

int main(void) {
    int var;    // automatic variable on the stack
    pid_t pid;

    var = 88;

    if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1)
        printf("write error");
    printf("before fork\n"); // we don't flush stdout

    pid = fork();
    if (pid < 0)
        printf("fork error");
    else if (pid == 0) {
        globval++;  // child process
        var++;
    } else {
        sleep(2);   // parent process
    }

    printf("pid = %ld, glob = %d, var = %d\n", (long) getpid(), globval, var);
    exit(0);
}
