#include <signal.h>
#include <printf.h>
#include <unistd.h>

//
// Created by YoungTr on 2022/3/19.
//
static void sig_usr(int);

int main(void) {
    if (signal(SIGUSR1, sig_usr) == SIG_ERR)
        printf("can't catch SIGUSR1");
    if (signal(SIGUSR2, sig_usr) == SIG_ERR)
        printf("can't catch SIGUSR2");
    for (;;)
        pause();
}

static void sig_usr(int signo) {
    switch (signo) {
        case SIGUSR1:
            printf("received SIGUSR1\n");
            break;
        case SIGUSR2:
            printf("received SIGUSR2\n");
            break;
        default:
            printf("received signal %d\n", signo);
    }
}