//
// Created by YoungTr on 2022/4/1.
//

#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "shmdata.h"

int main(void) {
    int running = 1;    // 程序是否继续运行
    void *shm = NULL;

    struct shared_use_st *shared;

    int shmid;  // 共享内存标识
    // 创建共享内存
    shmid = shmget((key_t) 1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
    if (shmid == -1) {
        fprintf(stderr, "shmget failed\n");
        exit(EXIT_FAILURE);
    }

    shm = shmat(shmid, 0, 0);
    if (shm == (void *) -1) {
        fprintf(stderr, "shmat failed\n");
        exit(EXIT_FAILURE);
    }

    printf("\nMemory attached at %X\n", (int) shm);
    // 设置共享内存
    shared = (struct shared_use_st *) shm;
    shared->written = 0;
    while (running) {
        if (shared->written != 0) {
            printf("You wrote: %s", shared->text);
            sleep(rand() % 3);
            // 读取完数据，设置written使共享内存段可写
            shared->written = 0;
            // 输入end，退出循环
            if (strncmp(shared->text, "end", 3) == 0)
                running = 0;
        } else
            // 有其他进程在写数据，不能读取
            sleep(1);
    }

    // 把共享内存从当前进程中分离
    if (shmdt(shm) == -1) {
        fprintf(stderr, "shmdt failed\n");
        exit(EXIT_FAILURE);
    }

    // 删除共享内存
    if (shmctl(shmid, IPC_RMID, 0) == -1) {
        fprintf(stderr, "shmctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);

}