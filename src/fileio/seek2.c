//
// Created by YoungTr on 2022/3/10.
//

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main() {
    int fd;

    if ((fd = creat("file.hole", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
        printf("Crate error\n");

    if (write(fd, buf1, 10) != 10)
        printf("buf1 write error\n");
    /* offset now = 10 */

    if (lseek(fd, 16384, SEEK_SET) == -1)
        printf("lseek error\n");
    /* offset now = 16384 */

    if (write(fd, buf2, 10) != 10)
        printf("buf2 write error\n");
    /* offset now = 16394 */

    exit(0);

}