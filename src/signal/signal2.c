

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static void sig_ptr(int signum) {
    printf("catch signal %d\n", signum);
    sleep(5);
    printf("catch signal done\n");

}

int main(void) {

    struct sigaction act;
    act.sa_flags = 0;
    sigfillset(&act.sa_mask);
    act.sa_handler = sig_ptr;


    sigaction(SIGUSR1, &act, NULL);
    sigaction(SIGUSR2, &act, NULL);

    printf("My PID is %d\n", getpid());

    while (1) {
        printf("Loop\n");
        sleep(5);
    }

    return 0;
}
