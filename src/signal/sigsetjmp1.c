//
// Created by YoungTr on 2022/3/22.
//

#include<stdio.h>
#include<stdlib.h>
#include<setjmp.h>
#include<unistd.h>
#include<signal.h>
typedef void (*sigfun)(int);
sigjmp_buf jmp;

void sig_alrm(int signo)
{
    printf("sig alrm\n");
    siglongjmp(jmp,1);
}
inline void err_sys(char *str)
{
    printf("%s\n",str);
    exit(-1);
}

int main()
{
    sigset_t oset;
    sigprocmask(0,NULL,&oset);
    if(sigismember(&oset,SIGALRM)) printf("SIGALRM in oset\n");
    sigfun prefun=signal(SIGALRM,sig_alrm);
    if(prefun==SIG_ERR) err_sys("signal(SIGALRM) error");
    if(sigsetjmp(jmp,1)!=0){
        sigprocmask(0,NULL,&oset);
        if(sigismember(&oset,SIGALRM)) printf("SIGALRM in oset\n");
        err_sys("timeout");
    }
    int a=alarm(3);
    printf("%d\n",a);
    sleep(4);
    alarm(0);
    signal(SIGALRM,prefun);
    return 0;
}