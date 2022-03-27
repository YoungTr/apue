### 线程创建

可以调用 pthread_create 函数创建线程。

```c
#include <pthread.h>

int pthread_create(pthread_t *restrict thread,
                   const pthread_attr_t *restrict attr,
                   void *(*start_routine)(void *),
                   void *restrict arg);
```

新创建的函数从 start_routine 函数的地址开始运行，新创建的线程可以访问进程的地址空间，并且继承调用线程的浮点环境和信号屏蔽字，但是该线程的挂起信号集会被清除。

```c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

pthread_t ntid;

void printids(const char *s) {
    pid_t pid;
    pthread_t tid;

    pid = getpid();
    tid = pthread_self();
    printf("%s pid %lu tid %lu (0x%lx)\n", s, (unsigned long) pid, (unsigned long) tid, (unsigned long) tid);
}

void *thr_fn(void *arg) {
    printids("new thread: ");
    return ((void *) 0);
}

int main(void) {
    int err;

    err = pthread_create(&ntid, NULL, thr_fn, NULL);
    if (err != 0) {
        printf("can't create thread");
        exit(1);
    }
    printids("main thread: ");
    sleep(1);
    exit(0);
}
```

### 线程终止

单个线程可以通过 3 种方式退出，因此可以在不终止整个进程的情况下，停止它的控制流。

1. 线程可以简单地从启动例程中返回，返回值是线程的退出码
2. 线程可以被同一进程中的其他线程取消。
3. 线程调用 pthread_exit 。

```c
#include <pthread.h>

void pthread_exit(void *rval_ptr);
```

rval_ptr 参数是一个无类型指针，与传给启动例程的单个参数类似。进程中其他线程也可以通过调用 pthread_join 函数访问到这个指针。



```c
#include <pthread.h>

int pthread_join(pthread_t thread, void **rval_ptr);
```



pthread_join()函数，以阻塞的方式等待thread指定的线程结束。当函数返回时，被等待线程的资源被收回。如果线程已经结束，那么该函数会立即返回。并且thread指定的线程必须是joinable的。



```c
//
// Created by YoungTr on 2022/3/27.
//

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *thr_fn1(void *arg) {
    printf("thread 1 returning\n");
    return ((void *) 1);
}

void *thr_fn2(void *arg) {
    printf("thread 2 returning\n");
    pthread_exit((void *) 2);
}

int main(void) {
    int err;
    pthread_t tid1, tid2;
    void *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (err != 0) {
        printf("can't create thread 1\n");
    }

    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (err != 0) {
        printf("can't create thread 2\n");
    }

    err = pthread_join(tid1, &tret);
    if (err != 0) {
        printf("can't join with thread 1");
    }
    printf("thread 1 exit code %ld\n", (long) tret);

    err = pthread_join(tid2, &tret);
    if (err != 0) {
        printf("can't join with thread 2\n");
    }

    printf("thread 2 exit code %ld\n", (long) tret);
    exit(0);

}
// thread 1 returning
// thread 2 returning
// thread 1 exit code 1
// thread 2 exit code 2
```

当一个线程通过 pthread_exit 退出或者简单地从启动例程中返回时，进程中的其他线程可以通过调用 pthread_join 函数获得该线程的退出状态。



