//
// Created by YoungTr on 2022/3/31.
//


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <string.h>

int main() {
    const char *fifo_name = "/tmp/my_fifo";
    int pipe_fd;
    int data_fd;
    int res;
    char buffer[PIPE_BUF + 1];
    int byte_read;
    int byte_write;

    // 清空缓冲数组
    memset(buffer, '\0', sizeof(buffer));
    printf("Process %d opening FIFO O_RDONLY\n", getpid());
    //以只读阻塞方式打开管道文件，注意与fifowrite.c文件中的FIFO同名
    pipe_fd = open(fifo_name, O_RDONLY);
    // 以只写的方式创建保存数据的文件
    data_fd = open("DataFromFIFO.txt", O_WRONLY | O_CREAT, 0644);
    printf("Process %d result %d\n", getpid(), pipe_fd);

    if (pipe_fd != -1) {
        do {
            res = read(pipe_fd, buffer, PIPE_BUF);
            byte_write = write(data_fd, buffer, res);
            byte_read += res;
        } while (res > 0);
        close(pipe_fd);
        close(data_fd);
    } else {
        exit(EXIT_FAILURE);
    }

    printf("Process %d finished, %d bytes read\n", getpid(), byte_read);
    exit(EXIT_SUCCESS);

}