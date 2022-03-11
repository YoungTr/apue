//
// Created by YoungTr on 2022/3/11.
//

#include <stdio.h>
#include <sys/fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("hello.file", O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        printf("Open error\n");
        return 0;
    }

    // 将标准输出重定向到fd
    int nfd = dup2(fd, STDOUT_FILENO);
    if (nfd < 0) {
        printf("Dup error\n");
        return 0;
    }

    char buf[5];
    ssize_t n;

    while ((n = read(STDIN_FILENO, buf, 5)) > 0) {
        if (write(STDOUT_FILENO, buf, n) != n)
            printf("Write error\n");
    }
    return 0;
}