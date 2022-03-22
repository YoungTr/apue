//
// Created by YoungTr on 2022/3/22.
//

#include<stdio.h>
#include<stdlib.h>
#include<setjmp.h>
#include<unistd.h>
#include<signal.h>


static void sigdel(int signo) {
    printf("catch signal number: %d\n", signo);
}

int main(void) {
    printf("pid: %d\n", getpid());
    jmp_buf buf;
    sigset_t newmask, oldmask, pendmask;
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGQUIT);
    signal(SIGQUIT, sigdel);
    signal(SIGUSR1, sigdel);
    //阻塞SIGQUIT
    sigprocmask(SIG_BLOCK, &newmask, &oldmask);
    if (sigsetjmp(buf, 1) != 0) {
        sigpending(&pendmask);
        if (sigismember(&pendmask, SIGQUIT)) {
            puts("block signal exist");
        } else {
            puts("block signal not exist");
        }
    }
    sleep(8);//这期间 ctrl+\ 发送SIGQUIT
    siglongjmp(buf, 1);
    return 0;
}