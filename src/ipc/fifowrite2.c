//
// Created by YoungTr on 2022/3/31.
//

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>


int main(void) {
    const char *fifo_name = "/tmp/my_fifo";
    int pipe_fd;
    int data_fd;

    int res = 0;
    int byte_sent = 0;
    char buffer[PIPE_BUF + 1];

    if (access(fifo_name, F_OK) == -1) {
        // 管道文件不存在
        // 创建命名管道;
        res = mkfifo(fifo_name, 0777);
        if (res != 0) {
            fprintf(stderr, "Could not create fifo %s\n", fifo_name);
            exit(EXIT_FAILURE);
        }
    }

    printf("Process %d opening FIFO O_WRONLY\n", getpid());

    pipe_fd = open(fifo_name, O_WRONLY);
    data_fd = open("Data.txt", O_RDWR);

    printf("Process %d result %d\n", getpid(), pipe_fd);

    if (pipe_fd != -1) {
        int byte_read = 0;
        // 向数据文件读取数据
        byte_read = read(data_fd, buffer, PIPE_BUF);
        buffer[byte_read] = '\0';
        while (byte_read > 0) {
            // 向FIFO文件写数据
            res = write(pipe_fd, buffer, byte_read);
            if (res == -1) {
                fprintf(stderr, "Write error on pipe\n");
                exit(EXIT_FAILURE);
            }
            // 累加写的字节数，并继续读取数据
            byte_sent += res;
            byte_read = read(data_fd, buffer, PIPE_BUF);
            buffer[byte_read] = '\0';
        }
        close(pipe_fd);
        close(data_fd);

    } else {
        exit(EXIT_FAILURE);
    }
    printf("Process %d finished\n", getpid());
    exit(EXIT_SUCCESS);
}
