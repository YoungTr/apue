//
// Created by YoungTr on 2022/3/31.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>


#define ARRAY_SIZE 40000
#define MALLOC_SIZE 100000
#define SHM_SIZE 100000
#define SHM_MODE 0600 // user read/write

char array[ARRAY_SIZE];

int main(void) {
    int shmid;
    char *ptr, *shmptr;
    printf("array[] from %p to %p\n", (void *) &array[0], (void *) &array[ARRAY_SIZE]);
    printf("stack around %p\n", (void *) ptr);

    if ((ptr = malloc(MALLOC_SIZE)) == NULL)
        printf("malloc error\n");

    printf("malloced from %p to %p\n", (void *) ptr, (void *) ptr + MALLOC_SIZE);

    if ((shmid = shmget(IPC_PRIVATE, SHM_SIZE, SHM_MODE)) < 0)
        printf("shmget error\n");

    if ((shmptr = shmat(shmid, 0, 0)) == (void *) -1)
        printf("shmat error");

    printf("shared memory attached from %p to %p\n", (void *) shmptr, (void *) shmptr + SHM_SIZE);

    if (shmctl(shmid, IPC_RMID, 0) < 0)
        printf("shmctl error\n");

    exit(EXIT_SUCCESS);


}
